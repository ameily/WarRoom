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


#ifndef RULE_H
#define RULE_H

#include <QString>
#include "XmlObject.h"


class IRule : public virtual XmlObject
{
public:
    virtual const QString& brief() const = 0;
    virtual const QString& description() const = 0;
    virtual const QString& page() const = 0;
    virtual const QString& id() const = 0;
    virtual const QString& name() const = 0;
    virtual bool isReference() const = 0;
    
    //virtual void fromXml(const QDomElement& ele) throw(XmlParseException) = 0;
    virtual QDomElement& toXml(QDomDocument& doc, QDomElement& parent) const
        throw(ValidationException) = 0;
};

class Rule : public IRule
{
public:
    Rule();
    Rule(const Rule& other);
    Rule(const QDomElement& ele) throw(XmlParseException);
    virtual ~Rule();
    
    virtual Rule& operator=(const Rule& other);
    virtual bool operator==(const Rule& other) const;
    
    virtual const QString& brief() const;
    virtual const QString& description() const;
    virtual const QString& page() const;
    virtual const QString& id() const;
    virtual const QString& name() const;
    virtual bool isReference() const;
    
    void brief(const QString& brf);
    void description(const QString& desc);
    void page(const QString& pg);
    void id(const QString& rid);
    void name(const QString& nm);
    
    virtual QDomElement& toXml(QDomDocument& doc, QDomElement& parent) const
        throw(ValidationException);
        
    bool isNull() const;
    
private:
    QString m_brief;
    QString m_description;
    QString m_page;
    QString m_id;
    QString m_name;
};

class RuleList;

class RuleRef : public IRule
{
public:
    RuleRef(const Rule& other, const QString& nm = QString());
    RuleRef(const RuleRef& other);
    RuleRef();
    //RuleRef(const QDomElement& node, RuleList& lookup);
    
    virtual ~RuleRef();
    
    virtual Rule& operator=(const RuleRef& other);
    virtual bool operator==(const RuleRef& other) const;
    
    virtual const QString& brief() const;
    virtual const QString& description() const;
    virtual const QString& page() const;
    virtual const QString& id() const;
    virtual const QString& name() const;
    virtual bool isReference() const;
    const Rule *rule();
    bool isNull() const;
    
    virtual QDomElement& toXml(QDomDocument& doc, QDomElement& parent) const
        throw(ValidationException);
    
private:
    QString m_refName;
    const Rule *m_rule;
};

#endif // RULE_H
