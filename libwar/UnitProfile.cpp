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


#include "UnitProfile.h"

UnitProfile::UnitProfile() : m_weaponSkill(), m_ballisticSkill(),
    m_strength(), m_toughness(), m_wounds(), m_leadership(), m_armourSave(),
    m_invulnerableSave(), m_attacks(), m_frontArmour(), m_rearArmour(),
    m_sideArmour(), m_initiative()
{

}

UnitProfile::UnitProfile(const UnitProfile& other) : 
    m_weaponSkill(other.m_weaponSkill),
    m_ballisticSkill(other.m_ballisticSkill), m_strength(other.m_strength),
    m_toughness(other.m_toughness), m_wounds(other.m_wounds),
    m_leadership(other.m_leadership), m_armourSave(other.m_armourSave),
    m_invulnerableSave(other.m_invulnerableSave), m_attacks(other.m_attacks),
    m_frontArmour(other.m_frontArmour), m_rearArmour(other.m_rearArmour),
    m_sideArmour(other.m_sideArmour), m_initiative(other.m_initiative)
{

}

UnitProfile::UnitProfile(const QDomElement& ele) throw(XmlParseException)
{
    QDomNodeList list = ele.childNodes();
    int len = list.length();
    QDomElement current;
    
    for(int i = 0; i < len; i++)
    {
        current = list.item(i).toElement();
        if(!current.isNull())
        {
            if(current.nodeName() == "weapon_skill")
                m_weaponSkill = current.text().simplified();
            else if(current.nodeName() == "ballistic_skill")
                m_ballisticSkill = current.text().simplified();
            else if(current.nodeName() == "attacks")
                m_attacks = current.text().simplified();
            else if(current.nodeName() == "strength")
                m_strength = current.text().simplified();
            else if(current.nodeName() == "toughness")
                m_toughness = current.text().simplified();
            else if(current.nodeName() == "wounds")
                m_wounds = current.text().simplified();
            else if(current.nodeName() == "initiative")
                m_initiative = current.text().simplified();
            else if(current.nodeName() == "leadership")
                m_leadership = current.text().simplified();
            else if(current.nodeName() == "armour_save")
                m_armourSave = current.text().simplified();
            else if(current.nodeName() == "invulnerable_save")
                m_invulnerableSave = current.text().simplified();
            else if(current.nodeName() == "front_armour")
                m_frontArmour = current.text().simplified();
            else if(current.nodeName() == "side_armour")
                m_sideArmour = current.text().simplified();
            else if(current.nodeName() == "rear_armour")
                m_rearArmour = current.text().simplified();
            else
                throw XmlParseException("invalid unit profile node",
                                        current);
        }
    }
    
    if(isNull())
        throw XmlParseException("null unit profile node", ele);
}


UnitProfile::~UnitProfile()
{

}

UnitProfile& UnitProfile::operator=(const UnitProfile& other)
{
    if(*this == other)
        return *this;
    
    m_armourSave = other.m_armourSave;
    m_attacks = other.m_attacks;
    m_ballisticSkill = other.m_ballisticSkill;
    m_frontArmour = other.m_frontArmour;
    m_invulnerableSave = other.m_invulnerableSave;
    m_leadership = other.m_leadership;
    m_initiative = other.m_initiative;
    m_rearArmour = other.m_rearArmour;
    m_sideArmour = other.m_sideArmour;
    m_strength = other.m_strength;
    m_toughness = other.m_toughness;
    m_weaponSkill = other.m_weaponSkill;
    m_wounds = other.m_wounds;
    
    return *this;
}

bool UnitProfile::operator==(const UnitProfile& other) const
{
    return m_armourSave == other.m_armourSave &&
        m_attacks == other.m_attacks &&
        m_ballisticSkill == other.m_ballisticSkill && 
        m_frontArmour == other.m_frontArmour &&
        m_invulnerableSave == other.m_invulnerableSave &&
        m_leadership == other.m_leadership &&
        //m_name == other.m_name &&
        m_rearArmour == other.m_rearArmour &&
        m_sideArmour == other.m_sideArmour &&
        m_strength == other.m_strength &&
        m_toughness == other.m_toughness &&
        m_weaponSkill == other.m_weaponSkill &&
        m_wounds == other.m_wounds &&
        m_initiative == other.m_initiative;
}


const QString& UnitProfile::armourSave() const
{
    return m_armourSave;
}

void UnitProfile::armourSave(const QString& other)
{
     m_armourSave = other;
}

const QString& UnitProfile::attacks() const
{
    return m_attacks;
}

void UnitProfile::attacks(const QString& other)
{
    m_attacks = other;
}

const QString& UnitProfile::ballisticSkill() const
{
    return m_ballisticSkill;
}

void UnitProfile::ballisticSkill(const QString& other)
{
    m_ballisticSkill = other;
}

const QString& UnitProfile::frontArmour() const
{
    return m_frontArmour;
}

void UnitProfile::frontArmour(const QString& other)
{
    m_frontArmour = other;
}

const QString& UnitProfile::invulnerableSave() const
{
    return m_invulnerableSave;
}

void UnitProfile::invulnerableSave(const QString& other)
{
    m_invulnerableSave = other;
}

const QString& UnitProfile::leadership() const
{
    return m_leadership;
}

void UnitProfile::leadership(const QString& other)
{
    m_leadership = other;
}

/*
const QString& UnitProfile::name() const
{
    return m_name;
}


void UnitProfile::name(const QString& other)
{
    m_name = other;
}
*/

const QString& UnitProfile::rearArmour() const
{
    return m_rearArmour;
}

void UnitProfile::rearArmour(const QString& other)
{
    m_rearArmour = other;
}

const QString& UnitProfile::sideArmour() const
{
    return m_sideArmour;
}

void UnitProfile::sideArmour(const QString& other)
{
    m_sideArmour = other;
}

const QString& UnitProfile::strength() const
{
    return m_strength;
}

void UnitProfile::strength(const QString& other)
{
    m_strength = other;
}

const QString& UnitProfile::toughness() const
{
    return m_toughness;
}

void UnitProfile::toughness(const QString& other)
{
    m_toughness = other;
}

const QString& UnitProfile::weaponSkill() const
{
    return m_weaponSkill;
}

void UnitProfile::weaponSkill(const QString& other)
{
    m_weaponSkill = other;
}

const QString& UnitProfile::wounds() const
{
    return m_wounds;
}

void UnitProfile::wounds(const QString& other)
{
    m_wounds = other;
}

const QString& UnitProfile::initiative() const
{
    return m_initiative;
}

void UnitProfile::initiative(const QString& other)
{
    m_initiative = other;
}


bool UnitProfile::isNull() const
{
    return m_attacks.isEmpty() && m_ballisticSkill.isEmpty() &&
        m_frontArmour.isEmpty() && m_invulnerableSave.isEmpty() &&
        m_leadership.isEmpty() && m_rearArmour.isEmpty() &&
        m_sideArmour.isEmpty() && m_strength.isEmpty() &&
        m_toughness.isEmpty() && m_weaponSkill.isEmpty() &&
        m_weaponSkill.isEmpty() && m_wounds.isEmpty() && m_initiative.isEmpty();
}

QDomElement& UnitProfile::toXml(QDomDocument& doc, QDomElement& parent) const
    throw(ValidationException)
{
    if(isNull())
        throw ValidationException("UnitProfile", "*", "is null");
    
    if(!m_armourSave.isEmpty())
        appendElement(doc, parent, "armour_save", m_armourSave);
    
    if(!m_attacks.isEmpty())
        appendElement(doc, parent, "attacks", m_attacks);
    
    if(!m_ballisticSkill.isEmpty())
        appendElement(doc, parent, "ballistic_skill", m_ballisticSkill);
    
    if(!m_initiative.isEmpty())
        appendElement(doc, parent, "initiative", m_initiative);
    
    if(!m_frontArmour.isEmpty())
        appendElement(doc, parent, "front_armour", m_frontArmour);
    
    if(!m_invulnerableSave.isEmpty())
        appendElement(doc, parent, "invulnerable_save", m_invulnerableSave);
    
    if(!m_leadership.isEmpty())
        appendElement(doc, parent, "leadership", m_leadership);
    
    if(!m_rearArmour.isEmpty())
        appendElement(doc, parent, "rear_armour", m_rearArmour);
    
    if(!m_sideArmour.isEmpty())
        appendElement(doc, parent, "side_armour", m_sideArmour);
    
    if(!m_strength.isEmpty())
        appendElement(doc, parent, "strength", m_strength);
    
    if(!m_toughness.isEmpty())
        appendElement(doc, parent, "toughness", m_toughness);
    
    if(!m_weaponSkill.isEmpty())
        appendElement(doc, parent, "weapon_skill", m_weaponSkill);
    
    if(!m_wounds.isEmpty())
        appendElement(doc, parent, "wounds", m_wounds);
    
    return parent;
}

