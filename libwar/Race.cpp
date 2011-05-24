/*
    This file is part of the War Room project
    https://github.com/ameily/WarRoom
    Copyright (C) 2011  Adam Meily <meily.adam@gmail.com>

    This program is free software; you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation; either version 2 of the License, or
    (at your option) any later version.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License along
    with this program; if not, write to the Free Software Foundation, Inc.,
    51 Franklin Street, Fifth Floor, Boston, MA 02110-1301 USA.
*/


#include "Race.h"
#include <QDebug>

Race::Race(const Game * game) : UnitList(), WargearList(), RuleSet(), m_name(),
    m_id()
{
    m_game = game;
}

Race::Race(const Race& other) : UnitList(other), WargearList(other), 
    RuleSet(other), m_name(other.m_name), m_id(other.m_id)
{
    m_game = other.m_game;
}

Race::Race(const QDomDocument& doc) throw(XmlParseException) : UnitList(),
    WargearList(), RuleSet(), m_name(), m_id()
{
    m_game = NULL;
    
    QDomElement root = doc.documentElement();
    if(root.isNull() || root.nodeName() != "race")
        throw XmlParseException("missing root race node");
    
    fromXml(root);
}



void Race::fromXml(const QDomElement& ele) throw(XmlParseException)
{
    QDomNodeList list = ele.childNodes();
    int len = list.length();
    QDomElement current;
    
    for(int i = 0; i < len; i++)
    {
        current = list.item(i).toElement();
        if(!current.isNull())
        {
            if(current.nodeName() == "id")
                m_id = current.text().simplified();
            else if(current.nodeName() == "name")
                m_name = current.text().simplified();
            else if(current.nodeName() == "game")
                m_unresolvedGame = UnresolvedReference(current);
            else if(current.nodeName() == "rule_set")
                RuleSet::fromXml(current);
            else if(current.nodeName() == "wargears")
                WargearList::fromXml(current);
            else if(current.nodeName() == "units")
                UnitList::fromXml(current);
            else
                throw XmlParseException("invalid race node", current);
        }
    }
    
    if(m_id.isEmpty())
        throw XmlParseException("missing race id node", ele);
    
    if(m_name.isEmpty())
        throw XmlParseException("missing race name node", ele);
    
    if(m_unresolvedGame.isNull())
        throw XmlParseException("missing race game reference node", ele);
}


Race::~Race()
{
    
}
/*
Race& Race::operator=(const Race& other)
{
    if(*this == other)
        return *this;
    
    RuleSet::operator=(other);
    WargearList::operator=(other);
    UnitList::operator=(other);
    
    m_name = other.m_name;
    m_id = other.m_id;
    m_game = other.m_game;
    m_unresolvedGame = other.m_unresolvedGame;
    
    return *this;
}
*/
bool Race::operator==(const Race& other) const
{
    return m_name == other.m_name && m_game == other.m_game && 
        UnitList::operator==(other) && WargearList::operator==(other) &&
        RuleSet::operator==(other) && m_id == other.m_id;
}

const Game* Race::game() const
{
    return m_game;
}

void Race::game(const Game& gm)
{
    m_game = &gm;
}

const QString& Race::name() const
{
    return m_name;
}

void Race::name(const QString& nm)
{
    m_name = nm;
}

const QString& Race::id() const
{
    return m_id;
}

void Race::id(const QString& rid)
{
    m_id = rid;
}

const Rule* Race::resolveRuleReference(const QString& id)
    throw(UnresolvedReferenceException)
{
    const Rule *ret = RuleList::getRule(id);
    if(!ret)
    {
        if(!m_game)
            throw UnresolvedReferenceException(m_unresolvedGame, "Game");
        
        ret = const_cast<Game*>(m_game)->getRule(id);
    }
    
    return ret;
}

const QString& Race::parsedGameId() const
{
    return m_unresolvedGame.id();
}


void Race::resolveReferences(const Game& game)
    throw(UnresolvedReferenceException)
{
    if(m_unresolvedGame.isNull())
        throw UnresolvedReferenceException(m_unresolvedGame, "Game");
    
    m_game = &game;
    const_cast<Game*>(m_game)->initBaseWargears(*this);
    
    m_unresolvedGame = UnresolvedReference();
    
    WargearList::resolveReferences();
    UnitList::resolveReferences();
}

QDomElement& Race::toXml(QDomDocument& doc, QDomElement& parent) const
    throw(ValidationException)
{
    if(m_game == NULL)
        throw ValidationException("Race", "game", "is null reference");
    
    if(m_id.isEmpty())
        throw ValidationException("Race", "id", "is null");
    
    if(m_name.isEmpty())
        throw ValidationException("Race", "name", "is null");
    
    QDomProcessingInstruction header = doc.createProcessingInstruction("xml", "version=\"1.0\"");   
    doc.appendChild(header);
    
    QDomElement root = doc.createElement("race");
    
    QDomElement ruleSetNode = doc.createElement("rule_set");
    RuleSet::toXml(doc, ruleSetNode);
    
    QDomElement wargearsNode = doc.createElement("wargears");
    WargearList::toXml(doc, wargearsNode);
    
    QDomElement unitsNode = doc.createElement("units");
    UnitList::toXml(doc, unitsNode);
    
    appendElement(doc, root, "id", m_id);
    appendElement(doc, root, "name", m_name);
    
    QDomElement gameNode = doc.createElement("game");
    UnresolvedReference game(m_game->id());
    game.toXml(doc, gameNode);
    root.appendChild(gameNode);
    
    root.appendChild(ruleSetNode);
    root.appendChild(wargearsNode);
    root.appendChild(unitsNode);
    
    doc.appendChild(root);
    
    return parent;
}

const Race& Race::race() const
{
    return *this;
}

