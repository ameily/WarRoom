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


#ifndef RULEREFLIST_H
#define RULEREFLIST_H
#include <QList>
#include "Rule.h"
#include "UnresolvedReference.h"

class Race;

class RuleRefList : public virtual XmlObject
{

public:
    RuleRefList();
    virtual ~RuleRefList();
    RuleRefList(const RuleRefList& other);
    virtual RuleRefList& operator=(const RuleRefList& other);
    virtual bool operator==(const RuleRefList& other) const;
    
    RuleRef* addRuleRef(const RuleRef& ref);
    bool removeRuleRef(const RuleRef& ref);
    //RuleRef* getRuleRef(const QString& id);
    //RuleRef getRuleRef(const QString& id) const;
    bool hasRule(const QString& id) const;
    QList<RuleRef> ruleRefs() const;
    QList<RuleRef*> ruleRefs();
    
    virtual QDomElement& toXml(QDomDocument& doc, QDomElement& parent) const
        throw(ValidationException);
        
    virtual const Race& race() const = 0;
    
    virtual void resolveReferences() throw(UnresolvedReferenceException);
    
protected:
    virtual void fromXml(const QDomElement& ele) throw(XmlParseException);
    
private:
    QList<RuleRef> m_ruleRefs;
    QList<UnresolvedReference> m_unresolvedRules;
};

#endif // RULEREFLIST_H
