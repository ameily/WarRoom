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


#include "Army.h"
#include "ArmyUnit.h"

Army::Army(const Race& race)
{

}

Army::Army(const Army& other)
{

}

Army::Army(const QDomDocument& doc) throw(XmlParseException)
{

}

Army::~Army()
{

}

void Army::addUnit(const ArmyUnit& unit)
{
    m_units.append(unit);
}

const QString& Army::author() const
{
    return m_author;
}

void Army::author(const QString& author)
{
    m_author = author;
}

const QString& Army::description() const
{
    return m_description;
}

void Army::description(const QString& description)
{
    m_description = description;
}

const QString& Army::history() const
{
    return m_history;
}

void Army::history(const QString& history)
{
    m_history = history;
}

Army& Army::operator=(const Army& other)
{
    m_author = other.m_author;
    m_description = other.m_description;
    m_history = other.m_history;
    m_points = other.m_points;
    m_race = other.m_race;
    m_units = other.m_units;
    m_unresolvedRace = other.m_unresolvedRace;
}

bool Army::operator==(const Army& other) const
{
    return m_author == other.m_author && m_description == other.m_description &&
        m_history == other.m_history && m_points == other.m_points &&
        m_race == other.m_race && m_units == other.m_units &&
        m_unresolvedRace == other.m_unresolvedRace;
}

const QString& Army::parsedRaceId() const
{
    return m_unresolvedRace.id();
}

int Army::points() const
{
    return m_points;
}

void Army::points(int points)
{
    m_points = points;
}

const Race& Army::race() const
{
    return *m_race;
}

void Army::removeUnit(const ArmyUnit& unit)
{
    int index = m_units.indexOf(unit);
    if(index > 0)
        m_units.removeAt(index);
}

int Army::totalCost() const
{
    int total = 0;
    int len = m_units.length();
    for(int i = 0; i < len; i++)
        total += m_units[i].totalCost();
    
    return total;
}

QList< ArmyUnit > Army::units() const
{
    return m_units;
}

QList< ArmyUnit* > Army::units()
{
    QList<ArmyUnit*> ret;
    int len = m_units.length();
    for(int i = 0; i < len; i++)
        ret.append(&m_units[i]);
    
    return ret;
}

void Army::resolveReferences(const Race& race)
{
    m_race = &race;
    int len = m_units.length();
    for(int i = 0; i < len; i++)
        m_units[i].resolveReferences();
}

QDomElement& Army::toXml(QDomDocument& doc, QDomElement& parent) const
    throw(ValidationException)
{
    return parent;
}


void Army::fromXml(const QDomElement& ele) throw(XmlParseException)
{

}


