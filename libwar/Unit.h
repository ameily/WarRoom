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


#ifndef UNIT_H
#define UNIT_H

#include <QString>
#include <QList>
#include "RuleRefList.h"
#include "UnitProfile.h"
#include "WargearRefList.h"



class Unit : public virtual WargearRefList, public virtual RuleRefList
{
public:
    Unit(const Race& race);
    Unit(const Unit& other);
    Unit(const QDomElement& ele, const Race& race);
    Unit();
    virtual ~Unit();
    virtual Unit& operator=(const Unit& other);
    virtual bool operator==(const Unit& other) const;
    
    const QString& name() const;
    const QString& id() const;
    const UnitProfile& profile() const;
    UnitProfile& profile();
    const Race& race() const;
    
    void name(const QString& nm);
    void id(const QString& uid);
    void profile(const UnitProfile& pf);
    
    virtual QDomElement& toXml(QDomDocument& doc, QDomElement& parent) const
        throw(ValidationException);
    
    virtual void resolveReferences() throw(UnresolvedReferenceException);
    
    bool isNull() const;
    
private:
    UnitProfile m_profile;
    QString m_id;
    QString m_name;
    const Race *m_race;
};


#endif // UNIT_H
