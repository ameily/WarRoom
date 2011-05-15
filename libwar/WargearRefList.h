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


#ifndef WARGEARREFLIST_H
#define WARGEARREFLIST_H
#include <QList>
#include "UnresolvedReference.h"
#include "Wargear.h"

class WargearRefList : public virtual XmlObject
{

public:
    WargearRefList();
    WargearRefList(const WargearRefList& other);
    virtual ~WargearRefList();
    virtual WargearRefList& operator=(const WargearRefList& other);
    virtual bool operator==(const WargearRefList& other) const;
    
    WargearRef* addWargearRef(const WargearRef& ref);
    bool removeWargearRef(const WargearRef& ref);
    bool hasWargear(const QString& id) const;
    QList<WargearRef> wargearRefs() const;
    QList<WargearRef*> wargearRefs();
    //WargearRef *getWargearRef(const QString& id);
    //WargearRef getWargearRef(const QString& id) const;
    
    virtual const Race& race() const = 0;
    
    virtual QDomElement& toXml(QDomDocument& doc, QDomElement& parent) const
        throw(ValidationException);
        
    void resolveReferences() throw(UnresolvedReferenceException);
    
protected:
    void fromXml(const QDomElement& ele) throw(XmlParseException);
    
private:
    QList<WargearRef> m_wargearRefs;
    QList<UnresolvedReference> m_unresolvedWargears;
};

#endif // WARGEARREFLIST_H
