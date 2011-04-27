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


#include "Rule.h"
#include "RuleList.h"

RuleRef::RuleRef(const Rule& other, const QString& nm)
{
    m_rule = &other;
    
    if(nm.isEmpty())
        m_refName = other.name();
    else
        m_refName = nm;
}

RuleRef::RuleRef(const RuleRef& other)
{
    m_rule = other.m_rule;
    m_refName = other.m_refName;
}

RuleRef::RuleRef() : m_refName()
{
    m_rule = NULL;
}


RuleRef::~RuleRef()
{

}

Rule& RuleRef::operator=(const RuleRef& other)
{
    m_rule = other.m_rule;
    m_refName = other.m_refName;
}

bool RuleRef::operator==(const RuleRef& other) const
{
    return m_rule == other.m_rule && m_refName == other.m_refName;
}


const QString& RuleRef::name() const
{
    return m_refName;
}

const QString& RuleRef::id() const
{
    return m_rule->id();
}

const QString& RuleRef::page() const
{
    return m_rule->page();
}

const QString& RuleRef::description() const
{
    return m_rule->description();
}

const QString& RuleRef::brief() const
{
    return m_rule->brief();
}

QDomElement& RuleRef::toXml(QDomDocument& doc, QDomElement& parent) const
    throw(ValidationException)
{
    QString name = (m_refName == m_rule->name() ? QString() : m_refName);
    UnresolvedReference ref(id(), name);
    
    return ref.toXml(doc, parent);
}

bool RuleRef::isReference() const
{
    return true;
}

bool RuleRef::isNull() const
{
    return !m_rule;
}

const Rule* RuleRef::rule()
{
    return m_rule;
}

