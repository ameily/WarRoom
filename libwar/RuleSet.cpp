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


#include "RuleSet.h"
#include "Race.h"

RuleSet::RuleSet() : RuleList(), m_book(), m_edition(),
    m_version()
{

}

RuleSet::RuleSet(const RuleSet& other) : RuleList(other), m_book(other.m_book),
    m_edition(other.m_edition), m_version(other.m_version)
{

}

RuleSet::~RuleSet()
{
    
}
/*
RuleSet& RuleSet::operator=(const RuleSet& other)
{
    if(*this == other)
        return *this;
    
    m_book = other.m_book;
    m_edition = other.m_edition;
    m_version = other.m_version;
    RuleList::operator=(other);
    return *this;
}
*/
bool RuleSet::operator==(const RuleSet& other) const
{
    return m_book == other.m_book && m_edition == other.m_edition &&
        m_version == other.m_version && RuleList::operator==(other);
        //Referenceable<RuleSet>::operator==(other);
}

const QString& RuleSet::book() const
{
    return m_book;
}

void RuleSet::book(const QString& bk)
{
    m_book = bk;
}

const QString& RuleSet::edition() const
{
    return m_edition;
}

void RuleSet::edition(const QString& ed)
{
    m_edition = ed;
}

const QString& RuleSet::version() const
{
    return m_version;
}

void RuleSet::version(const QString& ver)
{
    m_version = ver;
}

QString RuleSet::toString() const
{
    return m_book + ": " + m_edition + " edition [ver:" + m_version + "]";
}

void RuleSet::fromXml(const QDomElement& ele) throw(XmlParseException)
{
    QDomNodeList list = ele.childNodes();
    int len = list.length();
    QDomElement current;
    
    for(int i = 0; i < len; i++)
    {
        current = list.item(i).toElement();
        if(!current.isNull())
        {
            if(current.nodeName() == "book")
                m_book = current.text().simplified();
            else if(current.nodeName() == "version")
                m_version = current.text().simplified();
            else if(current.nodeName() == "edition")
                m_edition = current.text().simplified();
            else if(current.nodeName() == "rules")
                RuleList::fromXml(current);
            else
                throw XmlParseException("invalid node" , current);
        }
    }
    
    if(m_book.isEmpty())
        throw XmlParseException("missing ruleset book node", ele);
    
    if(m_edition.isEmpty())
        throw XmlParseException("missing ruleset edition node", ele);
    
    if(m_version.isEmpty())
        throw XmlParseException("missing ruleset version node", ele);
}

QDomElement& RuleSet::toXml(QDomDocument& doc, QDomElement& parent) const
    throw(ValidationException)
{
    if(m_book.isEmpty())
        throw ValidationException("RuleSet", "book", "is null");
    
    if(m_edition.isEmpty())
        throw ValidationException("RuleSet", "edition", "is null");
    
    if(m_version.isEmpty())
        throw ValidationException("RuleSet", "version", "is null");
    
    QDomElement ruleList = doc.createElement("rules");
    RuleList::toXml(doc, ruleList);
    
    appendElement(doc, parent, "book", m_book);
    appendElement(doc, parent, "edition", m_edition);
    appendElement(doc, parent, "version", m_version);
    
    parent.appendChild(ruleList);
    
    return parent;
}




