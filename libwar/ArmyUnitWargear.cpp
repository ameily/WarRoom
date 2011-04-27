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


#include "ArmyUnitWargear.h"


ArmyUnitWargear::ArmyUnitWargear(const ArmyUnit& armyUnit,
    const IWargear& wargear) : m_unresolvedWargear(), m_cost(0), m_count(0)
{
    m_armyUnit = &armyUnit;
    //m_wargear = new WargearRef(wargear);
}

ArmyUnitWargear::ArmyUnitWargear(const QDomElement& ele,
    const ArmyUnit& armyUnit) throw(XmlParseException) : m_cost(0), m_count(0),
    m_unresolvedWargear()
{
    m_armyUnit = &armyUnit;
    m_wargear = NULL;
    
    QDomNodeList list = ele.childNodes();
    QDomElement current;
    int len = list.length();
    for(int i = 0; i < len; i++)
    {
        current = list.item(i).toElement();
        if(!current.isNull())
        {
            if(current.nodeName() == "wargear_ref")
                m_unresolvedWargear = UnresolvedReference(current);
            else if(current.nodeName() == "cost")
            {
                bool ok;
                m_cost = current.text().toInt(&ok);
                if(!ok)
                    throw XmlParseException("invalid number", current);
            }
            else if(current.nodeName() == "count")
            {
                bool ok;
                m_count = current.text().toInt(&ok);
                if(!ok)
                    throw XmlParseException("invalid number", current);
            }
            else
            {
                throw XmlParseException("invalid army unit wargear node",
                                        current);
            }
        }
    }
    
    if(m_unresolvedWargear.isNull())
        throw XmlParseException("missing wargear reference node", ele);
}

ArmyUnitWargear::ArmyUnitWargear(const ArmyUnitWargear& other) :
    m_cost(other.m_cost), m_count(other.m_count),
    m_unresolvedWargear(other.m_unresolvedWargear)
{
    m_armyUnit = other.m_armyUnit;
    m_wargear = new WargearRef(*(other.m_wargear));
}


const ArmyUnit& ArmyUnitWargear::armyUnit() const
{
    return *m_armyUnit;
}

int ArmyUnitWargear::cost() const
{
    return m_cost;
}

void ArmyUnitWargear::cost(const int cost)
{
    m_cost = cost;
}

int ArmyUnitWargear::count() const
{
    return m_count;
}

void ArmyUnitWargear::count(const int count)
{
    m_count = count;
}

ArmyUnitWargear& ArmyUnitWargear::operator=(const ArmyUnitWargear& other)
{
    m_armyUnit = other.m_armyUnit;
    m_cost = other.m_cost;
    m_count = other.m_count;
    m_wargear = other.m_wargear;
}

bool ArmyUnitWargear::operator==(const ArmyUnitWargear& other) const
{
    return m_armyUnit == other.m_armyUnit && m_cost == other.m_cost &&
        m_count == other.m_count && m_wargear == other.m_wargear;
}

int ArmyUnitWargear::totalCost() const
{
    return m_count * m_cost;
}

QDomElement& ArmyUnitWargear::toXml(QDomDocument& doc, QDomElement& parent)
    const throw(ValidationException)
{
    QDomElement refNode = doc.createElement("wargear_ref");
    UnresolvedReference ref(m_wargear->id(), m_wargear->name());
    //appendElement(doc, parent, );
}


const IWargear& ArmyUnitWargear::wargear() const
{
    return *m_wargear;
}

void ArmyUnitWargear::resolveReferences() throw(UnresolvedReferenceException)
{
    if(m_unresolvedWargear.isNull() || m_wargear != NULL)
        return;
    
    Race& race = const_cast<Race&>(m_armyUnit->army().race());
    const Wargear *wargear = race.getWargear(m_unresolvedWargear.id());
    if(wargear == NULL)
        throw UnresolvedReferenceException(m_unresolvedWargear, "Wargear");
    
    m_wargear = new WargearRef(*wargear);
}








