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


#ifndef WARGEAR_H
#define WARGEAR_H
#include <QList>
#include "Rule.h"
#include "WargearProfile.h"

class IWargear : public virtual XmlObject
{
public:
    virtual const QString& brief() const = 0;
    virtual const QString& description() const = 0;
    virtual const QString& name() const = 0;
    virtual const QString& id() const = 0;
    virtual QList<WargearProfile> profiles() const = 0;
    virtual bool isReference() const = 0;
    virtual const Race& race() const = 0;
    
    virtual QDomElement& toXml(QDomDocument& doc, QDomElement& parent) const 
        throw(ValidationException) = 0;
    //virtual void fromXml(const QDomElement& ele) throw(XmlParseException) = 0;
};

class Wargear : public IWargear
{
public:
    Wargear(const Race& race);
    Wargear();
    //Wargear(const Wargear& other);
    Wargear(const Wargear& other);
    Wargear(const QDomElement& ele, const Race& race) throw(XmlParseException);
    virtual ~Wargear();
    virtual Wargear& operator=(const Wargear& other);
    virtual bool operator==(const Wargear& other) const;
    
    void brief(const QString& brf);
    void description(const QString& desc);
    void name(const QString& nm);
    void id(const QString& wid);
    WargearProfile* addProfile(const WargearProfile& profile);
    bool removeProfile(const WargearProfile& profile);
    
    virtual const QString& brief() const;
    virtual const QString& description() const;
    virtual const QString& name() const;
    virtual const QString& id() const;
    virtual const Race& race() const;
    virtual QList< WargearProfile > profiles() const;
    QList< WargearProfile* > profiles();
    
    virtual bool isReference() const;
    virtual void resolveReferences() throw(UnresolvedReferenceException);
    
    virtual QDomElement& toXml(QDomDocument& doc, QDomElement& parent) const
        throw(ValidationException);
    
    bool isNull() const;
    
    static Wargear Null();
    
private:
    void profilesFromXml(const QDomElement& ele) throw(XmlParseException);
    QList<WargearProfile> m_profiles;
    QString m_brief;
    QString m_description;
    QString m_name;
    QString m_id;
    const Race *m_race;
};

class WargearRef : public IWargear
{
public:
    WargearRef(const Wargear& other, const QString nm = QString());
    WargearRef(const WargearRef& other);
    WargearRef();
    bool isNull() const;
    //WargearRef(const QDomElement& node, WargearList& lookup);
    virtual ~WargearRef();
    virtual bool operator==(const WargearRef& other) const;
    virtual WargearRef& operator=(const WargearRef& other);
    
    virtual const QString& brief() const;
    virtual const QString& description() const;
    virtual const QString& name() const;
    virtual const QString& id() const;
    virtual QList< WargearProfile > profiles() const;
    virtual const Race& race() const;
    const Wargear* wargear() const;
    
    virtual bool isReference() const;
    //virtual QList< WargearProfile* > profiles();
    
    virtual QDomElement& toXml(QDomDocument& doc, QDomElement& parent) const
        throw(ValidationException);
    //virtual void fromXml(const QDomElement& ele) throw(XmlParseException);
    
private:
    const Wargear *m_wargear;
    QString m_refName;
};

#endif // WARGEAR_H
