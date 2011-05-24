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


#include "XmlObject.h"

XmlParseException::XmlParseException(const QString& desc, const QDomElement& ele)
{
    m_description = desc;
    m_line = ele.lineNumber();
    m_elementName = ele.nodeName();
}

XmlParseException::XmlParseException(const QString& desc) : m_elementName()
{
    m_description = desc;
    m_line = 0;
}

XmlParseException::XmlParseException(const XmlParseException& other)
{
    m_description = other.m_description;
    m_line = other.m_line;
    m_elementName = other.m_elementName;
}

XmlParseException& XmlParseException::operator=(const XmlParseException& other)
{
    m_description = other.m_description;
    m_line = other.m_line;
    m_elementName = other.m_elementName;
    
    return *this;
}

const QString& XmlParseException::description() const
{
    return m_description;
}

const QString& XmlParseException::elementName() const
{
    return m_elementName;
}

int XmlParseException::line() const
{
    return m_line;
}

QString XmlParseException::toString() const
{
    if(m_elementName.isEmpty())
        return m_description;
    
    return "[" + m_elementName + ":" + QString::number(m_line) + "] " + m_description;
}


void XmlObject::appendElement(QDomDocument& doc, QDomElement& parent,
                              const QString& name, const QString& value) const
{
    QDomElement ele = doc.createElement(name);
    //ele.setNodeValue(value);
    if(!value.isEmpty())
    {
        QDomText txt = doc.createTextNode(value);
        ele.appendChild(txt);
    }
    parent.appendChild(ele);
}



ValidationException::ValidationException(const QString& object,
    const QString& field, const QString& reason) : m_object(object),
    m_field(field), m_reason(reason)
{
}

ValidationException::ValidationException(const ValidationException& other) :
    m_object(other.m_object), m_field(other.m_field), m_reason(other.m_reason)
{
}

ValidationException& ValidationException::operator=(
    const ValidationException& other)
{
    m_field = other.m_field;
    m_object = other.m_object;
    m_reason = other.m_reason;
}

const QString& ValidationException::field() const
{
    return m_field;
}

const QString& ValidationException::object() const
{
    return m_object;
}

const QString& ValidationException::reason() const
{
    return m_reason;
}

QString ValidationException::toString() const
{
    return "[" + m_object + ":" + m_field + "] " + m_reason;
}




