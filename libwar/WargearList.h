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


#ifndef WARGEARLIST_H
#define WARGEARLIST_H

#include <QString>
#include <QList>
#include <QHash>
#include "Wargear.h"

class WargearList : public virtual XmlObject
{
public:
    WargearList();
    WargearList(const WargearList& other);
    virtual ~WargearList();
    virtual WargearList& operator=(const WargearList& other);
    virtual bool operator==(const WargearList& other) const;
    
    Wargear getWargear(const QString& id) const;
    Wargear* getWargear(const QString& id);
    QList<Wargear> findWargearsByName(const QString& name) const;
    QList<Wargear> wargears() const;
    QList< Wargear* > wargears();
    
    Wargear* addWargear(const Wargear& wargear);
    bool removeWargear(const Wargear& wargear);
    bool hasWargear(const QString& id) const;
    Wargear* resetWargearId(const QString& oldId, const QString& newId);
    
    virtual void resolveReferences() throw(UnresolvedReferenceException);
    virtual const Race& race() const = 0;
    
    virtual QDomElement& toXml(QDomDocument& doc, QDomElement& parent) const
        throw(ValidationException);
    
protected:
    virtual void fromXml(const QDomElement& ele) throw(XmlParseException);
    //void sortWargear();
    
private:
    QHash<QString, Wargear> m_wargears;
    QList<UnresolvedReference> m_unresolvedWargears;
};

#endif // WARGEARLIST_H
