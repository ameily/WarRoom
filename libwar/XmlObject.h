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


#ifndef XMLOBJECT_H
#define XMLOBJECT_H

#include <QDomElement>

class XmlParseException
{
public:
    XmlParseException(const QString& desc, const QDomElement& ele);
    XmlParseException(const QString& desc);
    XmlParseException& operator=(const XmlParseException& other);
    XmlParseException(const XmlParseException& other);
    
    int line() const;
    const QString& elementName() const;
    const QString& description() const;
    
    QString toString() const;
    
private:
    int m_line;
    QString m_elementName;
    QString m_description;
};

class ValidationException
{
public:
    ValidationException(const QString& object, const QString& field,
                        const QString& reason);
    
    ValidationException(const ValidationException& other);
    ValidationException& operator=(const ValidationException& other);
    
    const QString& object() const;
    const QString& field() const;
    const QString& reason() const;
    
    QString toString() const;
    
private:
    QString m_object;
    QString m_field;
    QString m_reason;
};


class XmlObject
{
    virtual QDomElement& toXml(QDomDocument& doc, QDomElement& parent) const 
        throw(ValidationException) = 0;
    
protected:
    void appendElement(QDomDocument& doc, QDomElement& parent,
                       const QString& name, const QString& value) const;
};

#endif // XMLOBJECT_H
