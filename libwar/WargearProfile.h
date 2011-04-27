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


#ifndef WARGEARPROFILE_H
#define WARGEARPROFILE_H

#include <QString>
#include <QList>
#include "RuleRefList.h"

class Wargear;

class WargearProfile : public virtual RuleRefList
{
public:
    WargearProfile();
    WargearProfile(const Wargear& wargear);
    WargearProfile(const WargearProfile& other, const Wargear *override = 0);
    WargearProfile(const QDomElement& ele, const Wargear& wargear)
        throw(XmlParseException);
    
    virtual ~WargearProfile();
    
    virtual WargearProfile& operator=(const WargearProfile& other);
    virtual bool operator==(const WargearProfile& other) const;
    
    const QString& name() const;
    const QString& range() const;
    const QString& strength() const;
    const QString& armourPenetration() const;
    const Wargear& wargear() const;
    
    void name(const QString& nm);
    void range(const QString& rn);
    void strength(const QString& str);
    void armourPenetration(const QString& ap);
    
    bool isNull() const;
    
    virtual QDomElement& toXml(QDomDocument& doc, QDomElement& parent) const
        throw(ValidationException);
    virtual const Race& race() const;
    
private:
    QString m_name;
    QString m_range, m_strength, m_armourPenetration;
    const Wargear *m_wargear;
};

#endif // WARGEARPROFILE_H
