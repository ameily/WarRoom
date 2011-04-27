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


#include "WargearProfile.h"
#include "Race.h"
#include "Wargear.h"

WargearProfile::WargearProfile() : m_name(), m_range(), m_strength(),
    m_armourPenetration(), RuleRefList()
{
    m_wargear = 0;
}

bool WargearProfile::isNull() const
{
    return !m_wargear;
}



WargearProfile::WargearProfile(const Wargear& wargear) : m_name(), m_range(),
    m_strength(), m_armourPenetration(), RuleRefList()
{
    m_wargear = &wargear;
    m_name = wargear.name();
}

WargearProfile::WargearProfile(const WargearProfile& other,
    const Wargear *override) : m_name(other.m_name), m_range(other.m_range),
    m_strength(other.m_strength),
    m_armourPenetration(other.m_armourPenetration), RuleRefList(other)
{
    if(override)
        m_wargear = override;
    else
        m_wargear = other.m_wargear;
}

WargearProfile::WargearProfile(const QDomElement& ele, const Wargear& wargear)
    throw(XmlParseException)
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
            else if(current.nodeName() == "range")
                m_range = current.text().simplified();
            else if(current.nodeName() == "strength")
                m_strength = current.text().simplified();
            else if(current.nodeName() == "armour_penetration")
                m_armourPenetration = current.text().simplified();
            else if(current.nodeName() == "rules")
                RuleRefList::fromXml(current);
            else
            {
                throw XmlParseException("invalid wargear profile node",current);
            }
        }
    }
    
    if(m_armourPenetration.isEmpty())
        throw XmlParseException("missing wargear profile ap node", ele);
    
    if(m_range.isEmpty())
        throw XmlParseException("missing wargear profile range node", ele);
    
    if(m_strength.isEmpty())
        throw XmlParseException("missing wargear profile strength node", ele);
    
    m_wargear = &wargear;
}


WargearProfile::~WargearProfile()
{

}

WargearProfile& WargearProfile::operator=(const WargearProfile& other)
{
    if(*this == other)
        return *this;
    
    m_armourPenetration = other.m_armourPenetration;
    m_name = other.m_name;
    m_range = other.m_range;
    m_strength = other.m_strength;
    m_wargear = other.m_wargear;
    RuleRefList::operator=(other);
    
    return *this;
}

bool WargearProfile::operator==(const WargearProfile& other) const
{
    return m_armourPenetration == other.m_armourPenetration && 
        m_name == other.m_name && m_range == other.m_range &&
        m_strength == other.m_strength && RuleRefList::operator==(other) &&
        m_wargear == other.m_wargear;
}

const QString& WargearProfile::armourPenetration() const
{
    return m_armourPenetration;
}

void WargearProfile::armourPenetration(const QString& ap)
{
    m_armourPenetration = ap;
}

const QString& WargearProfile::name() const
{
    return m_name;
}

void WargearProfile::name(const QString& nm)
{
    m_name = nm;
}

const QString& WargearProfile::range() const
{
    return m_range;
}

void WargearProfile::range(const QString& rn)
{
    m_range = rn;
}

const QString& WargearProfile::strength() const
{
    return m_strength;
}

void WargearProfile::strength(const QString& str)
{
    m_strength = str;
}

QDomElement& WargearProfile::toXml(QDomDocument& doc, QDomElement& parent) const
    throw(ValidationException)
{
    if(m_range.isEmpty())
        throw ValidationException("WargearProfile", "range", "is null");
    
    if(m_strength.isEmpty())
        throw ValidationException("WargearProfile", "strength", "is null");
    
    if(m_armourPenetration.isEmpty())
    {
        throw ValidationException("WargearProfile", "armour_penetration",
                                  "is null");
    }
    
    if(m_wargear == NULL)
        throw ValidationException("WargearProfile", "wargear", "is null");
    
    appendElement(doc, parent, "name", m_name);
    appendElement(doc, parent, "range", m_range);
    appendElement(doc, parent, "strength", m_strength);
    appendElement(doc, parent, "armour_penetration", m_armourPenetration);
    
    QDomElement ele = doc.createElement("rules");
    RuleRefList::toXml(doc, ele);
    parent.appendChild(ele);
    
    return parent;
}

const Race& WargearProfile::race() const
{
    return m_wargear->race();
}

const Wargear& WargearProfile::wargear() const
{
    return *m_wargear;
}


