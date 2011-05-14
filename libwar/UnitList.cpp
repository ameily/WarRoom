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


#include "UnitList.h"

UnitList::UnitList() : m_units()
{

}

UnitList::UnitList(const UnitList& other) : m_units(other.m_units)
{

}

UnitList::~UnitList()
{
    /*QMutableHashIterator<QString, Unit*> i(m_units);
    Unit *dead;
    while(i.hasNext())
    {
        i.next();
        dead = i.value();
        i.remove();
        delete dead;
    }*/
}

bool UnitList::operator==(const UnitList& other) const
{
    return m_units == other.m_units;
}

Unit* UnitList::addUnit(const Unit& unit)
{
    if(hasUnit(unit.id()))
        return 0;
    
    m_units.insert(unit.id(), unit);
    return getUnit(unit.id());
}

bool UnitList::hasUnit(const QString& id) const
{
    return m_units.contains(id);
}


QList<Unit> UnitList::searchUnitsByName(const QString& name)
{
    QList<Unit> ret;
    QMutableHashIterator<QString, Unit> i(m_units);
    while(i.hasNext())
    {
        i.next();
        if(i.value().name().contains(name, Qt::CaseInsensitive))
            ret.append(i.value());
    }
    
    return ret;
}

Unit* UnitList::getUnit(const QString& id)
{
    Unit *ret = NULL;
    if(m_units.contains(id))
        ret = &m_units[id];
    
    return ret;
}

Unit UnitList::getUnit(const QString& id) const
{
    if(m_units.contains(id))
        return m_units[id];
    
    return Unit();
}


bool UnitList::removeUnit(const Unit& unit)
{
    bool ret = !m_units.contains(unit.id());
    if(ret)
        m_units.remove(unit.id());
    
    return ret;
}

QList<Unit> UnitList::units() const
{
    return m_units.values();
}

QList< Unit* > UnitList::units()
{
    QList<Unit*> ret;
    QMutableHashIterator<QString, Unit> i(m_units);
    while(i.hasNext())
    {
        i.next();
        ret.append(&i.value());
    }
    
    return ret;
}

Unit* UnitList::resetUnitId(const QString& oldId, const QString& newId)
{
    if(hasUnit(oldId) || hasUnit(newId))
        return 0;
    
    Unit unit = m_units.take(oldId);
    unit.id(newId);
    return addUnit(unit);
}


void UnitList::fromXml(const QDomElement& ele) throw(XmlParseException)
{
    QDomNodeList list = ele.childNodes();
    int len = list.length();
    QDomElement current;
    
    for(int i = 0; i < len; i++)
    {
        current = list.item(i).toElement();
        if(!current.isNull())
        {
            if(current.nodeName() == "unit")
            {
                Unit unit(current, race());
                m_units.insert(unit.id(), unit);
            }
            else
                throw XmlParseException("invalid unit list node", current);
        }
    }
}

QDomElement& UnitList::toXml(QDomDocument& doc, QDomElement& parent) const
    throw(ValidationException)
{
    QHashIterator<QString, Unit> i(m_units);
    QDomElement ele;
    while(i.hasNext())
    {
        i.next();
        ele = doc.createElement("unit");
        i.value().toXml(doc, ele);
        parent.appendChild(ele);
    }
    
    return parent;
}

void UnitList::resolveReferences() throw(UnresolvedReferenceException)
{
    QMutableHashIterator<QString, Unit> i(m_units);
    while(i.hasNext())
    {
        i.next();
        i.value().resolveReferences();
    }
}

