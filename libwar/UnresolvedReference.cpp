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


#include "UnresolvedReference.h"


UnresolvedReference::UnresolvedReference(const QDomElement& ele)
    throw(XmlParseException) : m_id(), m_name()
{
    QDomNamedNodeMap attrs = ele.attributes();
    if(!attrs.contains("id"))
        throw XmlParseException("invalid reference node", ele);
    
    m_id = attrs.namedItem("id").nodeValue().simplified();
    if(attrs.contains("name"))
        m_name = attrs.namedItem("name").nodeValue().simplified();
    
    if(m_id.isEmpty())
        throw XmlParseException("invalid reference node", ele);
}

UnresolvedReference::UnresolvedReference() : m_id(), m_name()
{
    
}


QDomElement& UnresolvedReference::toXml(QDomDocument& doc, QDomElement& parent)
    const throw(ValidationException)
{
    parent.setAttribute("id", m_id);
    if(!m_name.isEmpty())
        parent.setAttribute("name", m_name);
    
    return parent;
}


UnresolvedReference::UnresolvedReference(const UnresolvedReference& other) :
    m_name(other.m_name), m_id(other.m_id)
{
    
}

UnresolvedReference::UnresolvedReference(const QString& id, const QString& name)
    : m_id(id), m_name(name)
{
    
}

bool UnresolvedReference::isNull() const
{
    return m_id.isEmpty() && m_name.isEmpty();
}




const QString& UnresolvedReference::id() const
{
    return m_id;
}

const QString& UnresolvedReference::name() const
{
    return m_name;
}

UnresolvedReference& UnresolvedReference::operator=(const UnresolvedReference& other)
{
    m_id = other.m_id;
    m_name = other.m_name;
}

bool UnresolvedReference::operator==(const UnresolvedReference& other) const
{
    return m_id == other.m_id && m_name == other.m_name;
}




UnresolvedReferenceException::UnresolvedReferenceException(
    const UnresolvedReference& ref, const QString& type) : m_reference(ref),
    m_type(type)
{
}

UnresolvedReferenceException::UnresolvedReferenceException(
    const UnresolvedReferenceException& other) : m_reference(other.m_reference),
    m_type(other.m_type)
{
}

const QString& UnresolvedReferenceException::id() const
{
    return m_reference.id();
}

const QString& UnresolvedReferenceException::name() const
{
    return m_reference.name();
}

const QString& UnresolvedReferenceException::type() const
{
    return m_type;
}

UnresolvedReferenceException& UnresolvedReferenceException::operator=(
    const UnresolvedReferenceException& other)
{
    m_reference = other.m_reference;
    m_type = other.m_type;
}
