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


#ifndef RULESET_H
#define RULESET_H

#include <QString>
#include <QHash>
#include <QXmlStreamReader>
#include <QXmlStreamWriter>
#include "Rule.h"
#include "RuleList.h"
#include "XmlObject.h"

//class Race;

class RuleSet : public virtual RuleList
{
public:
    RuleSet();
    RuleSet(const RuleSet& other);
    virtual ~RuleSet();
    //virtual RuleSet& operator=(const RuleSet& other);
    virtual bool operator==(const RuleSet& other) const;
    
    const QString& book() const;
    const QString& edition() const;
    const QString& version() const;
    
    void book(const QString& bk);
    void edition(const QString& ed);
    void version(const QString& ver);
    
    virtual QDomElement& toXml(QDomDocument& doc, QDomElement& parent) const
        throw(ValidationException);
    
    virtual const Race& race() const = 0;
    
    QString toString() const;
    
protected:
    virtual void fromXml(const QDomElement& ele) throw(XmlParseException);
    
private:
    QString m_book;
    QString m_edition;
    QString m_version;
    //QString m_name;
};

//typedef Reference<RuleSet> RuleSetRef;

#endif // RULESET_H
