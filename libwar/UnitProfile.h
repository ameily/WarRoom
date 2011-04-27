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


#ifndef UNITPROFILE_H
#define UNITPROFILE_H

#include "XmlObject.h"

class UnitProfile : public virtual XmlObject
{
public:
    UnitProfile();
    UnitProfile(const UnitProfile& other);
    UnitProfile(const QDomElement& ele) throw(XmlParseException);
    virtual ~UnitProfile();
    virtual UnitProfile& operator=(const UnitProfile& other);
    virtual bool operator==(const UnitProfile& other) const;
    
    //const QString& name() const;
    const QString& weaponSkill() const;
    const QString& ballisticSkill() const;
    const QString& strength() const;
    const QString& toughness() const;
    const QString& wounds() const;
    const QString& attacks() const;
    const QString& initiative() const;
    const QString& leadership() const;
    const QString& armourSave() const;
    const QString& invulnerableSave() const;
    const QString& frontArmour() const;
    const QString& rearArmour() const;
    const QString& sideArmour() const;
    
    //void name(const QString& other);
    void weaponSkill(const QString& other);
    void ballisticSkill(const QString& other);
    void strength(const QString& other);
    void toughness(const QString& other);
    void wounds(const QString& other);
    void attacks(const QString& other);
    void initiative(const QString& other);
    void leadership(const QString& other);
    void armourSave(const QString& other);
    void invulnerableSave(const QString& other);
    void frontArmour(const QString& other);
    void rearArmour(const QString& other);
    void sideArmour(const QString& other);
    
    bool isNull() const;
    
    virtual QDomElement& toXml(QDomDocument& doc, QDomElement& parent) const
        throw(ValidationException);
    
private:
    //QString m_name;
    QString m_weaponSkill, m_ballisticSkill, m_strength, m_toughness, m_wounds,
        m_leadership, m_armourSave, m_invulnerableSave, m_attacks,
        m_frontArmour, m_rearArmour, m_sideArmour, m_initiative;
};

#endif // UNITPROFILE_H
