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


#ifndef ARMYUNITWARGEAR_H
#define ARMYUNITWARGEAR_H

#include "XmlObject.h"
#include "Army.h"
#include "ArmyUnit.h"
#include "Wargear.h"

class ArmyUnitWargear : public virtual XmlObject
{
public:
    ArmyUnitWargear(const ArmyUnit& armyUnit, const IWargear& wargear);
    ArmyUnitWargear(const QDomElement& ele, const ArmyUnit& armyUnit)
        throw(XmlParseException);
    
    ArmyUnitWargear(const ArmyUnitWargear& other);
    
    virtual ArmyUnitWargear& operator=(const ArmyUnitWargear& other);
    virtual bool operator==(const ArmyUnitWargear& other) const;
    
    virtual QDomElement& toXml(QDomDocument& doc, QDomElement& parent) const
        throw(ValidationException);
    
    const ArmyUnit& armyUnit() const;
    const IWargear& wargear() const;
    int cost() const;
    int count() const;
    int totalCost() const;
    
    void cost(const int cost);
    void count(const int count);
    virtual void resolveReferences() throw(UnresolvedReferenceException);
    
private:
    const ArmyUnit *m_armyUnit;
    const WargearRef *m_wargear;
    UnresolvedReference m_unresolvedWargear;
    int m_cost;
    int m_count;
};

#endif // ARMYUNITWARGEAR_H
