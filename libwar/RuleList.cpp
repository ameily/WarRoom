/*
    This file is part of the War Library (libwar)
    Url: https://github.com/ameily/WarRoom
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

#include "RuleList.h"
#include "Race.h"
#include <QDebug>

RuleList::RuleList() : m_rules()
{

}

RuleList::RuleList(const RuleList& other) : m_rules(other.m_rules)
{

}


RuleList::~RuleList()
{
    /*
    QMutableHashIterator<QString, IRule*> i(m_rules);
    IRule *dead;
    while(i.hasNext())
    {
        i.next();
        dead = i.value();
        i.remove();
        delete dead;
    }
    */
}


RuleList& RuleList::operator=(const RuleList& other)
{
    if(*this == other)
        return *this;
    
    m_rules = other.m_rules;
    return *this;
}


bool RuleList::operator==(const RuleList& other) const
{
    return m_rules == other.m_rules;
}

Rule* RuleList::addRule(const Rule& rule)
{
    if(hasRule(rule.id()))
        return 0;
    
    m_rules.insert(rule.id(), rule);
    return getRule(rule.id());
}

Rule* RuleList::resetKey(const QString& oldId, const QString& newId)
{
    if(!hasRule(oldId) || hasRule(newId))
        return 0;
    
    
    Rule rule = m_rules.take(oldId);
    rule.id(newId);
    
    return addRule(rule);
}


bool RuleList::removeRule(const Rule& rule)
{
    bool ret = true;
    if(m_rules.contains(rule.id()))
        m_rules.remove(rule.id());
    else
        ret = false;
    
    return ret;
}

bool RuleList::hasRule(const QString& id) const
{
    return m_rules.contains(id);
}


QList<Rule> RuleList::findRulesByName(const QString& name) const
{
    QList<Rule> ret;
    QHashIterator<QString, Rule> i(m_rules);
    
    while(i.hasNext())
    {
        i.next();
        if(i.value().name().contains(name, Qt::CaseInsensitive))
            ret.append(i.value());
    }
    
    return ret;
}

Rule RuleList::getRule(const QString& id) const
{
    if(m_rules.contains(id))
        return m_rules[id];
    
    return Rule();
}

Rule* RuleList::getRule(const QString& id)
{
    Rule *ret = NULL;
    if(m_rules.contains(id))
        ret = &m_rules[id];
    
    return ret;
}



QList< Rule* > RuleList::rules()
{
    QList<Rule*> ret;
    QMutableHashIterator<QString, Rule> i(m_rules);
    while(i.hasNext())
    {
        i.next();
        ret.append(&i.value());
    }
    
    return ret;
}

QList< Rule > RuleList::rules() const
{
    return m_rules.values();
}


void RuleList::fromXml(const QDomElement& ele) throw(XmlParseException)
{
    QDomNodeList list  = ele.childNodes();
    int len = list.length();
    QDomElement node;
    
    for(int i = 0; i < len; i++)
    {
        node = list.item(i).toElement();
        if(!node.isNull())
        {
            if(node.nodeName() == "rule")
            {
                Rule rule(node);
                m_rules.insert(rule.id(), rule);
            }
            else
                throw XmlParseException("invalid rule list node", node);
        }
    }
}

QDomElement& RuleList::toXml(QDomDocument& doc, QDomElement& parent) const
    throw(ValidationException)
{
    QDomElement ele;
    QHashIterator<QString, Rule> i(m_rules);
    
    while(i.hasNext())
    {
        i.next();
        ele = doc.createElement("rule");
        i.value().toXml(doc, ele);
        parent.appendChild(ele);
    }
    
    return parent;
}

const Rule* RuleList::resolveRuleReference(const QString& id)
    throw(UnresolvedReferenceException)
{
    return getRule(id);
}


/*const IRule* RuleList::resolveRuleReference(const QString& id) const
{
    return race()->resolveRuleReference(id);
}*/

/*
void RuleList::resolveReferences() throw(UnresolvedReferenceException)
{
    int len = m_unresolvedRules.length();
    const IRule *rule = NULL;
    IRule *ref;
    UnresolvedReference *unresolved;
    
    for(int i = 0; i < len; i++)
    {
        unresolved = &m_unresolvedRules[i];
        rule = race().resolveRuleReference(unresolved->id());
        if(rule != NULL)
        {
            ref = new RuleRef(*rule, unresolved->name());
            m_rules.insert(ref->id(), ref);
        }
        else
            throw UnresolvedReferenceException(*unresolved, "Rule");
    }
    
    m_unresolvedRules.clear();
}

bool RuleList::hasUnresolvedReferences() const
{
    return m_unresolvedRules.length() > 0;
}
*/

