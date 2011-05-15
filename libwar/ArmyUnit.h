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


#ifndef ARMYUNIT_H
#define ARMYUNIT_H

#include "XmlObject.h"
#include "Unit.h"
#include "Army.h"

class ArmyUnitWargear;

class ArmyUnit : public virtual XmlObject
{

public:
    ArmyUnit(const Unit& unit, const Army& army);
    ArmyUnit(const QDomElement& ele, const Army& army) throw(XmlParseException);
    ArmyUnit(const ArmyUnit& other);
    virtual ~ArmyUnit();
    virtual ArmyUnit& operator=(const ArmyUnit& other);
    virtual bool operator==(const ArmyUnit& other) const;
    
    /*!
     * Total cost of the unit (including all upgrades)
     */
    int totalCost() const;
    
    /*!
     * Cost for unit (count * cost)
     */
    int unitCost() const;
    
    /*!
     * Cost per model
     */
    int cost() const;
    int count() const;
    const Army& army() const;
    const Unit& unit() const;
    QList<ArmyUnit> upgradedUnits() const;
    QList<ArmyUnit*> upgradedUnits();
    QList<ArmyUnitWargear> upgradedWargear() const;
    QList<ArmyUnitWargear*> upgradedWargear();
    
    void cost(const int cost);
    void count(const int count);
    void addUpgradedUnit(const ArmyUnit& upgrade);
    void removeUpgradedUnit(const ArmyUnit& upgrade);
    void addUpgradedWargear(const ArmyUnitWargear& wargear);
    void removeUpgradedWargear(const ArmyUnitWargear& wargear);
    
    virtual void resolveReferences() throw(UnresolvedReferenceException);
    virtual QDomElement& toXml(QDomDocument& doc, QDomElement& parent) const
        throw(ValidationException);
    
private:
    int m_count;
    int m_cost;
    QList<ArmyUnitWargear> m_wargearUpgrades;
    QList<ArmyUnit> m_unitUpgrades;
    const Unit *m_unit;
    const Army *m_army;
    UnresolvedReference m_unresolvedUnit;
};

#endif // ARMYUNIT_H
