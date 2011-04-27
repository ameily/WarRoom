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


#ifndef UNRESOLVEDREFERENCE_H
#define UNRESOLVEDREFERENCE_H

#include "XmlObject.h"

class UnresolvedReference
{
public:
    UnresolvedReference(const QDomElement& ele) throw(XmlParseException);
    UnresolvedReference(const UnresolvedReference& other);
    UnresolvedReference(const QString& id, const QString& name = QString());
    UnresolvedReference();
    virtual UnresolvedReference& operator=(const UnresolvedReference& other);
    virtual bool operator==(const UnresolvedReference& other) const;
    
    const QString& name() const;
    const QString& id() const;
    bool isNull() const;
    
    virtual QDomElement& toXml(QDomDocument& doc, QDomElement& parent) const
        throw(ValidationException);
    
private:
    QString m_name;
    QString m_id;
};

class UnresolvedReferenceException
{
public:
    UnresolvedReferenceException(const UnresolvedReference& ref,
                                 const QString& type);
    
    UnresolvedReferenceException(const UnresolvedReferenceException& other);
    UnresolvedReferenceException& operator=(
        const UnresolvedReferenceException& other);
    
    const QString& id() const;
    const QString& name() const;
    const QString& type() const;
    
private:
    UnresolvedReference m_reference;
    QString m_type;
};

#endif // UNRESOLVEDREFERENCE_H
