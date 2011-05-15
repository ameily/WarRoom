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


#include "Rule.h"
#include "WarPage.h"

Rule::Rule() : m_brief(), m_description(), m_page(), m_id(), m_name()
{
    
}

Rule::Rule(const Rule& other) : m_page(other.m_page), m_brief(other.m_brief),
    m_description(other.m_description), m_id(other.m_id), m_name(other.m_name)
{

}

Rule::Rule(const QDomElement& ele) throw(XmlParseException)
{
    QDomNodeList list = ele.childNodes();
    int len = list.length();
    QDomElement current;
    QDomNode node;
    
    for(int i = 0; i < len; i++)
    {
        current = list.item(i).toElement();
        if(!current.isNull())
        {
            if(current.nodeName() == "id")
                m_id = current.text().simplified();
            else if(current.nodeName() == "name")
                m_name = current.text().simplified();
            else if(current.nodeName() == "brief")
                m_brief = current.text().simplified();
            else if(current.nodeName() == "page")
                m_page = current.text().simplified();
            else if(current.nodeName() == "description")
                m_description = WarPage::wrapWhiteSpaceTags(current);
            else
                throw XmlParseException("invalid node", current);
        }
    }
    
    if(m_id.isEmpty())
        throw XmlParseException("mission rule id node", ele);
    
    if(m_name.isEmpty())
        throw XmlParseException("missing rule name node", ele);
    
    if(m_brief.isEmpty())
        throw XmlParseException("missing rule brief node", ele);
}

Rule::~Rule()
{

}

Rule& Rule::operator=(const Rule& other)
{
    if(*this == other)
        return *this;
    
    m_brief = other.m_brief;
    m_description = other.m_description;
    m_page = other.m_page;
    m_name = other.m_name;
    m_id = other.m_id;
    
    return *this;
}

bool Rule::operator==(const Rule& other) const
{
    return (m_brief == other.m_brief) && (m_description == other.m_description)
        && (m_page == other.m_page) && (m_id == other.m_id) &&
        (m_name == other.m_name);
}

const QString& Rule::brief() const
{
    return m_brief;
}

void Rule::brief(const QString& brf)
{
    m_brief = brf;
}

const QString& Rule::description() const
{
    return m_description;
}

void Rule::description(const QString& desc)
{
    m_description = desc;
}

const QString& Rule::page() const
{
    return m_page;
}

void Rule::page(const QString& pg)
{
    m_page = pg;
}

const QString& Rule::id() const
{
    return m_id;
}

void Rule::id(const QString& rid)
{
    m_id = rid;
}

const QString& Rule::name() const
{
    return m_name;
}


void Rule::name(const QString& nm)
{
    m_name = nm;
}



QDomElement& Rule::toXml(QDomDocument& doc, QDomElement& parent) const
    throw(ValidationException)
{
    if(m_id.isEmpty())
        throw ValidationException("Rule", "id", "is null");
    
    if(m_brief.isEmpty())
        throw ValidationException("Rule", "brief", "is null");
    
    if(m_name.isEmpty())
        throw ValidationException("Rule", "name", "is null");
    
    appendElement(doc, parent, "id", m_id);
    
    appendElement(doc, parent, "name", m_name);
    
    appendElement(doc, parent, "brief", m_brief);
    
    if(!m_page.isEmpty())
        appendElement(doc, parent, "page", m_page);
    
    if(!m_description.isEmpty())
        appendElement(doc, parent, "description", m_description);
    
    return parent;
}

bool Rule::isReference() const
{
    return false;
}

bool Rule::isNull() const
{
    return m_brief.isEmpty() && m_description.isEmpty() && m_id.isEmpty() &&
        m_name.isEmpty() && m_page.isEmpty();
}

bool compareRule(Rule*const& r1, Rule*const& r2)
{
    return QString::localeAwareCompare(r1->name().toLower(),
                                       r2->name().toLower()) < 0;
}


