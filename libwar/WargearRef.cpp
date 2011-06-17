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


#include "Wargear.h"
#include "WargearList.h"
#include "Race.h"

/*
WargearRef::WargearRef(const QDomElement& node, WargearList& lookup)
{

}
*/

WargearRef::WargearRef(const Wargear& other, const QString nm)
{
    m_wargear = &other;
    
    if(nm.isEmpty())
        m_refName = m_wargear->name();
    else
        m_refName = nm;
}

WargearRef::WargearRef(const WargearRef& other) : m_refName(other.m_refName)
{
    m_wargear = other.m_wargear;
}

WargearRef::WargearRef() : m_refName()
{
    m_wargear = NULL;
}

WargearRef::~WargearRef()
{

}


const QString& WargearRef::brief() const
{
    return m_wargear->brief();
}

const QString& WargearRef::description() const
{
    return m_wargear->description();
}

const QString& WargearRef::id() const
{
    return m_wargear->id();
}

const QString& WargearRef::name() const
{
    return m_refName;
}

const QString& WargearRef::page() const
{
    return m_wargear->page();
}

QString WargearRef::title() const
{
    return m_refName != m_wargear->name() ? 
        m_refName + " [" + m_wargear->name() + "]" : m_refName;
}

QList< WargearProfile > WargearRef::profiles() const
{
    return m_wargear->profiles();
}

const Wargear* WargearRef::wargear() const
{
    return m_wargear;
}

WargearRef& WargearRef::operator=(const WargearRef& other)
{
    m_wargear = other.m_wargear;
    m_refName = other.m_refName;
    return *this;
}

bool WargearRef::operator==(const WargearRef& other) const
{
    return m_refName == other.m_refName && m_wargear == other.m_wargear;
}

const Race& WargearRef::race() const
{
    return m_wargear->race();
}

QDomElement& WargearRef::toXml(QDomDocument& doc, QDomElement& parent) const
    throw(ValidationException)
{
    QString nm = m_refName == m_wargear->name() ? QString() : m_refName;
    UnresolvedReference ref(id(), nm);
    ref.toXml(doc, parent);
    
    return parent;
}

bool WargearRef::isReference() const
{
    return true;
}

bool WargearRef::isNull() const
{
    return !m_wargear;
}
