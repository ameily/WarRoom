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


#include "ArmyUnit.h"
#include "ArmyUnitWargear.h"

ArmyUnit::ArmyUnit(const Unit& unit, const Army& army) : m_count(0), m_cost(0),
    m_wargearUpgrades(), m_unitUpgrades(), m_unresolvedUnit()
{
    m_unit = &unit;
    m_army = &army;
}

ArmyUnit::ArmyUnit(const QDomElement& ele, const Army& army)
    throw(XmlParseException)
{

}

ArmyUnit::ArmyUnit(const ArmyUnit& other) : m_count(other.m_count),
    m_cost(other.m_cost), m_wargearUpgrades(other.m_wargearUpgrades),
    m_unitUpgrades(other.m_unitUpgrades),
    m_unresolvedUnit(other.m_unresolvedUnit)
{
    m_army = other.m_army;
    m_unit = other.m_unit;
}

ArmyUnit::~ArmyUnit()
{

}

ArmyUnit& ArmyUnit::operator=(const ArmyUnit& other)
{
    if(*this == other)
        return *this;
    
    m_army = other.m_army;
    m_cost = other.m_cost;
    m_count = other.m_count;
    m_unit = other.m_unit;
    m_unitUpgrades = other.m_unitUpgrades;
    m_unresolvedUnit = other.m_unresolvedUnit;
    m_wargearUpgrades = other.m_wargearUpgrades;
    
    return *this;
}

bool ArmyUnit::operator==(const ArmyUnit& other) const
{
    return m_army == other.m_army && m_cost == other.m_cost &&
        m_count == other.m_count && m_unit == other.m_unit &&
        m_unitUpgrades == other.m_unitUpgrades &&
        m_unresolvedUnit == other.m_unresolvedUnit &&
        m_wargearUpgrades == other.m_wargearUpgrades;
}

const Army& ArmyUnit::army() const
{
    return *m_army;
}

int ArmyUnit::cost() const
{
    return m_cost;
}

void ArmyUnit::cost(const int cost)
{
    m_cost = cost;
}

void ArmyUnit::count(const int count)
{
    m_count = count;
}

int ArmyUnit::count() const
{
    return m_count;
}

int ArmyUnit::totalCost() const
{
    int total = unitCost();
    int len = m_unitUpgrades.length();
    for(int i = 0; i < len; i++)
    {
        total += m_unitUpgrades[i].totalCost();
    }
    
    len = m_wargearUpgrades.length();
    for(int i = 0; i < len; i++)
    {
        total += m_wargearUpgrades[i].totalCost();
    }
}

int ArmyUnit::unitCost() const
{
    return m_cost * m_count;
}

const Unit& ArmyUnit::unit() const
{
    return *m_unit;
}

void ArmyUnit::addUpgradedUnit(const ArmyUnit& upgrade)
{
    m_unitUpgrades.append(upgrade);
}

void ArmyUnit::addUpgradedWargear(const ArmyUnitWargear& wargear)
{
    m_wargearUpgrades.append(wargear);
}

void ArmyUnit::removeUpgradedUnit(const ArmyUnit& upgrade)
{
    int index = m_unitUpgrades.indexOf(upgrade);
    if(index >= 0)
        m_unitUpgrades.removeAt(index);
}

void ArmyUnit::removeUpgradedWargear(const ArmyUnitWargear& wargear)
{
    int index = m_wargearUpgrades.indexOf(wargear);
    if(index >= 0)
        m_wargearUpgrades.removeAt(index);
}

QDomElement& ArmyUnit::toXml(QDomDocument& doc, QDomElement& parent) const
    throw(ValidationException)
{
    
    return parent;
}


void ArmyUnit::resolveReferences() throw(UnresolvedReferenceException)
{
    if(m_unresolvedUnit.isNull() || m_unit != NULL)
        return;
    
    const Unit* unit = const_cast<Race&>(m_army->race()).getUnit(
        m_unresolvedUnit.id());
    
    if(unit == NULL)
        throw UnresolvedReferenceException(m_unresolvedUnit, "Unit");
    
    m_unit = unit;
    
    int len = m_unitUpgrades.length();
    for(int i = 0; i < len; i++)
        m_unitUpgrades[i].resolveReferences();
    
    len = m_wargearUpgrades.length();
    for(int i = 0; i < len; i++)
        m_wargearUpgrades[i].resolveReferences();
}

QList< ArmyUnit > ArmyUnit::upgradedUnits() const
{
    return m_unitUpgrades;
}

QList< ArmyUnit* > ArmyUnit::upgradedUnits()
{
    QList<ArmyUnit*> units;
    int len = m_unitUpgrades.length();
    for(int i = 0; i < len; i++)
        units.append(&m_unitUpgrades[i]);
    
    return units;
}

QList< ArmyUnitWargear > ArmyUnit::upgradedWargear() const
{
    return m_wargearUpgrades;
}

QList< ArmyUnitWargear* > ArmyUnit::upgradedWargear()
{
    QList<ArmyUnitWargear*> wargears;
    int len = m_wargearUpgrades.length();
    for(int i = 0; i < len; i++)
        wargears.append(&m_wargearUpgrades[i]);
    
    return wargears;
}

