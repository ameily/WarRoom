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


#include "Game.h"
#include "Race.h"

Game::Game() : m_id(), m_name(), RuleSet(), m_baseWargears()
{
    
}

Game::Game(const Game& other) : RuleSet(other), m_id(other.m_id),
    m_name(other.m_name), m_baseWargears()
{
    
}

Game::Game(QDomDocument& doc) throw(XmlParseException) : m_id(), m_name(),
    m_baseWargears(), RuleSet()
{
    QDomElement root = doc.documentElement();
    if(root.isNull() || root.nodeName() != "game")
        throw XmlParseException("no root game node found");
    
    fromXml(root);
}


Game::~Game()
{
    
}
/*
Game& Game::operator=(const Game& other)
{
    if(*this == other)
        return *this;
    
    RuleSet::operator=(other);
    m_name = other.m_name;
    m_id = other.m_id;
    
    return *this;
}
*/
bool Game::operator==(const Game& other) const
{
    return (m_name == other.m_name) && (m_id == other.m_id) && 
        RuleSet::operator==(*this) && m_baseWargears == other.m_baseWargears;
}

const QString& Game::id() const
{
    return m_id;
}

void Game::id(const QString& gid)
{
    m_id = gid;
}

const QString& Game::name() const
{
    return m_name;
}

void Game::name(const QString& nm)
{
    m_name = nm;
}

void Game::initBaseWargears(const Race& race)
{
    QList<Rule*> rs = rules();
    int len = rs.length();
    for(int i = 0; i < len; i++)
    {
        Rule *r = rs[i];
        if(r->isAbstractWargear())
        {
            Wargear w(race);
            w.id(r->id());
            w.name(r->name());
            w.page(r->page());
            w.brief(r->brief());
            w.description(r->description());
            
            m_baseWargears.insert(w.id(), w);
        }
    }
}


QList< Wargear* > Game::baseWargears()
{
    QList<Wargear*> ret;
    QMutableHashIterator<QString, Wargear> i(m_baseWargears);
    while(i.hasNext())
    {
        i.next();
        ret.append(&i.value());
    }
    
    return ret;
}

Wargear* Game::getBaseWargear(const QString& id)
{
    if(m_baseWargears.contains(id))
        return &m_baseWargears[id];
    
    return 0;
}


void Game::fromXml(const QDomElement& ele) throw(XmlParseException)
{
    QDomNodeList list = ele.childNodes();
    int len = list.length();
    QDomElement current;
    
    for(int i = 0; i < len; i++)
    {
        current = list.item(i).toElement();
        if(!current.isNull())
        {
            if(current.nodeName() == "name")
                m_name = current.text().simplified();
            else if(current.nodeName() == "id")
                m_id = current.text().simplified();
            else if(current.nodeName() == "rule_set")
                RuleSet::fromXml(current);
            else
                throw XmlParseException("invalid node", current);
        }
    }
    
    if(m_id.isEmpty())
        throw XmlParseException("missing game id node", ele);
    
    if(m_name.isEmpty())
        throw XmlParseException("missing game name node", ele);
}


QDomElement& Game::toXml(QDomDocument& doc, QDomElement& parent) const
    throw(ValidationException)
{
    if(m_id.isEmpty())
        throw ValidationException("Game", "id", "is null");
    
    if(m_name.isEmpty())
        throw ValidationException("Game", "name", "is null");
    
    QDomProcessingInstruction header = doc.createProcessingInstruction("xml", "version=\"1.0\"");   
    doc.appendChild(header);
    
    QDomElement ruleSet = doc.createElement("rule_set");
    QDomElement root = doc.createElement("game");
    RuleSet::toXml(doc, ruleSet);
    
    appendElement(doc, root, "id", m_id);
    appendElement(doc, root, "name", m_name);
    
    root.appendChild(ruleSet);
    doc.appendChild(root);
    
    
    return parent;
}

const Race& Game::race() const
{
    return *(new Race());
}

