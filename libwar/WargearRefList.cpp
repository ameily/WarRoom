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


#include "WargearRefList.h"
#include "Race.h"

WargearRefList::WargearRefList() : m_wargearRefs(), m_unresolvedWargears()
{

}

WargearRefList::WargearRefList(const WargearRefList& other) :
    m_wargearRefs(other.m_wargearRefs),
    m_unresolvedWargears(other.m_unresolvedWargears)
{

}

WargearRefList::~WargearRefList()
{

}

WargearRefList& WargearRefList::operator=(const WargearRefList& other)
{
    m_wargearRefs = other.m_wargearRefs;
    m_unresolvedWargears = other.m_unresolvedWargears;
    return *this;
}

bool WargearRefList::operator==(const WargearRefList& other) const
{
    return m_unresolvedWargears == other.m_unresolvedWargears &&
        m_wargearRefs == other.m_wargearRefs;
}

WargearRef* WargearRefList::addWargearRef(const WargearRef& ref)
{
    if(hasWargear(ref.id()))
        return 0;
    
    m_wargearRefs.append(ref);
    return &m_wargearRefs.last();
}

bool WargearRefList::removeWargearRef(const WargearRef& ref)
{
    int index = m_wargearRefs.indexOf(ref);
    if(index >= 0)
        m_wargearRefs.removeAt(index);
    
    return index >= 0;
}

bool WargearRefList::hasWargear(const QString& id) const
{
    int len = m_wargearRefs.length();
    bool ret = false;
    for(int i = 0; i < len && !ret; i++)
        ret = (m_wargearRefs[i].id() == id);
    
    return ret;
}


QList< WargearRef > WargearRefList::wargearRefs() const
{
    return m_wargearRefs;
}

QList< WargearRef* > WargearRefList::wargearRefs()
{
    QList<WargearRef*> ret;
    int len = m_wargearRefs.length();
    for(int i = 0; i < len; i++)
        ret.append(&m_wargearRefs[i]);
    
    return ret;
}
/*
WargearRef* WargearRefList::getWargearRef(const QString& id)
{
    int len = m_wargearRefs.length();
    for(int i = 0; i < len; i++)
    {
        if(m_wargearRefs[i].id() == id)
            return &m_wargearRefs[i];
    }
    
    return NULL;
}

WargearRef WargearRefList::getWargearRef(const QString& id) const
{
    int len = m_wargearRefs.length();
    for(int i = 0; i < len; i++)
    {
        if(m_wargearRefs[i].id() == id)
            return m_wargearRefs[i];
    }
    
    return WargearRef();
}
*/

void WargearRefList::fromXml(const QDomElement& ele) throw(XmlParseException)
{
    QDomNodeList list = ele.childNodes();
    int len = list.length();
    QDomElement current;
    
    for(int i = 0; i < len; i++)
    {
        current = list.item(i).toElement();
        if(!current.isNull())
        {
            if(current.nodeName() == "wargear_ref")
            {
                UnresolvedReference ref(current);
                m_unresolvedWargears.append(ref);
            }
            else
            {
                throw XmlParseException("invalid wargear reference list node",
                                        current);
            }
        }
    }
}

QDomElement& WargearRefList::toXml(QDomDocument& doc, QDomElement& parent) const
    throw(ValidationException)
{
    QDomElement current;
    int len = m_wargearRefs.length();
    for(int i = 0; i < len; i++)
    {
        current = doc.createElement("wargear_ref");
        m_wargearRefs[i].toXml(doc, current);
        parent.appendChild(current);
    }
    
    return parent;
}

void WargearRefList::resolveReferences() throw(UnresolvedReferenceException)
{
    int len = m_unresolvedWargears.length();
    // cast away const because we need getWargear to return a pointer
    Race &race = const_cast<Race&>(this->race());
    
    for(int i = 0; i < len; i++)
    {
        Wargear *w = race.getWargear(m_unresolvedWargears[i].id());
        if(!w)
        {
            throw UnresolvedReferenceException(m_unresolvedWargears[i],
                                               "WargearRef");
        }
        
        WargearRef ref(*w, m_unresolvedWargears[i].name());
        m_wargearRefs.append(ref);
    }
    
    m_unresolvedWargears.clear();
}


