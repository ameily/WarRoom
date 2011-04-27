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


#ifndef ARMY_H
#define ARMY_H

#include "XmlObject.h"
#include "Race.h"

class ArmyUnit;

class Army : public virtual XmlObject
{

public:
    Army(const Race& race);
    Army(const QDomDocument& doc) throw(XmlParseException);
    Army(const Army& other);
    virtual ~Army();
    virtual Army& operator=(const Army& other);
    virtual bool operator==(const Army& other) const;
    
    const QString& author() const;
    const QString& history() const;
    const QString& description() const;
    int points() const;
    int totalCost() const;
    const Race& race() const;
    QList<ArmyUnit> units() const;
    QList<ArmyUnit*> units();
    
    
    void author(const QString& author);
    void history(const QString& history);
    void description(const QString& description);
    void points(int points);
    void addUnit(const ArmyUnit& unit);
    void removeUnit(const ArmyUnit& unit);
    
    
    virtual QDomElement& toXml(QDomDocument& doc, QDomElement& parent) const
        throw(ValidationException);
    
    const QString& parsedRaceId() const;
    void resolveReferences(const Race& race);
    
protected:
    virtual void fromXml(const QDomElement& ele) throw(XmlParseException);
    
private:
    QString m_author;
    QString m_history;
    QString m_description;
    int m_points;
    const Race *m_race;
    UnresolvedReference m_unresolvedRace;
    QList<ArmyUnit> m_units;
};

#endif // ARMY_H
