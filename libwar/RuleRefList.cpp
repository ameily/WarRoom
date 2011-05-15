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


#include "RuleRefList.h"
#include "Race.h"
//#include <QDebug>

RuleRefList::RuleRefList() : m_ruleRefs(), m_unresolvedRules()
{
    
}

RuleRefList::RuleRefList(const RuleRefList& other) :
    m_ruleRefs(other.m_ruleRefs), m_unresolvedRules(other.m_unresolvedRules)
{

}

RuleRefList& RuleRefList::operator=(const RuleRefList& other)
{
    m_ruleRefs = other.m_ruleRefs;
    m_unresolvedRules = other.m_unresolvedRules;
}

bool RuleRefList::operator==(const RuleRefList& other) const
{
    return m_ruleRefs == other.m_ruleRefs &&
        m_unresolvedRules == other.m_unresolvedRules;
}


RuleRefList::~RuleRefList()
{

}

RuleRef* RuleRefList::addRuleRef(const RuleRef& ref)
{
    if(hasRule(ref.id()))
        return 0;
    
    m_ruleRefs.append(ref);
    return &m_ruleRefs.last();
}

bool RuleRefList::hasRule(const QString& id) const
{
    int len = m_ruleRefs.length();
    bool ret = false;
    for(int i = 0; i < len && !ret; i++)
        ret = (m_ruleRefs[i].id() == id);
    
    return ret;
}


bool RuleRefList::removeRuleRef(const RuleRef& ref)
{
    int index = m_ruleRefs.indexOf(ref);
    if(index >= 0)
        m_ruleRefs.removeAt(index);
    
    return index >= 0;
}
/*
RuleRef* RuleRefList::getRuleRef(const QString& id)
{
    int len = m_ruleRefs.length();
    for(int i = 0; i < len; i++)
    {
        if(m_ruleRefs[i].id() == id)
            return &m_ruleRefs[i];
    }
    
    return NULL;
}

RuleRef RuleRefList::getRuleRef(const QString& id) const
{
    int len = m_ruleRefs.length();
    for(int i = 0; i < len; i++)
    {
        if(m_ruleRefs[i].id() == id)
            return m_ruleRefs[i];
    }
    
    return RuleRef();
}
*/

QList< RuleRef > RuleRefList::ruleRefs() const
{
    return m_ruleRefs;
}

QList< RuleRef* > RuleRefList::ruleRefs()
{
    QList<RuleRef*> ret;
    int len = m_ruleRefs.length();
    for(int i = 0; i < len; i++)
        ret.append(&m_ruleRefs[i]);
    
    return ret;
}

void RuleRefList::fromXml(const QDomElement& ele) throw(XmlParseException)
{
    QDomNodeList list  = ele.childNodes();
    int len = list.length();
    QDomElement node;
    
    
    for(int i = 0; i < len; i++)
    {
        node = list.item(i).toElement();
        if(!node.isNull())
        {
            if(node.nodeName() == "rule_ref")
            {
                UnresolvedReference ref(node);
                m_unresolvedRules.append(ref);
            }
            else
                throw XmlParseException("invalid rule ref list node", node);
        }
    }
}

QDomElement& RuleRefList::toXml(QDomDocument& doc, QDomElement& parent) const
    throw(ValidationException)
{
    QDomElement ele;
    int len = m_ruleRefs.length();
    for(int i = 0; i < len; i++)
    {
        ele = doc.createElement("rule_ref");
        m_ruleRefs[i].toXml(doc, ele);
        parent.appendChild(ele);
    }
    
    return parent;
}


void RuleRefList::resolveReferences() throw(UnresolvedReferenceException)
{
    int len = m_unresolvedRules.length();
    UnresolvedReference *unresolved;
    const Rule *rule;
    Race& race = const_cast<Race&>(this->race());
    
    for(int i = 0; i < len; i++)
    {
        unresolved = &m_unresolvedRules[i];
        rule = race.resolveRuleReference(unresolved->id());
        if(rule != NULL)
        {
            RuleRef ref(*rule, unresolved->name());
            m_ruleRefs.append(ref);
        }
        else
            throw UnresolvedReferenceException(*unresolved, "Rule");
    }
    
    m_unresolvedRules.clear();
}


