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


#ifndef UNITLIST_H
#define UNITLIST_H

#include <QString>
#include <QHash>
#include "Unit.h"

class UnitList : public virtual XmlObject
{

public:
    UnitList();
    UnitList(const UnitList& other);
    virtual ~UnitList();
    //virtual UnitList& operator=(const UnitList& other);
    virtual bool operator==(const UnitList& other) const;
    
    Unit* getUnit(const QString& id);
    Unit getUnit(const QString& id) const;
    QList<Unit> searchUnitsByName(const QString& name);
    QList<Unit> units() const;
    QList<Unit*> units();
    
    virtual const Race& race() const = 0;
    
    Unit* addUnit(const Unit& unit);
    bool hasUnit(const QString& id) const;
    bool removeUnit(const Unit& unit);
    
    Unit* resetUnitId(const QString& oldId, const QString& newId);
    
    virtual QDomElement& toXml(QDomDocument& doc, QDomElement& parent) const
        throw(ValidationException);
    virtual void resolveReferences() throw(UnresolvedReferenceException);
    
protected:
    virtual void fromXml(const QDomElement& ele) throw(XmlParseException);
    
private:
    QHash<QString, Unit> m_units;
};

#endif // UNITLIST_H
