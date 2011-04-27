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

#ifndef RULELIST_H
#define RULELIST_H

#include <QList>
#include <QHash>
#include <QDomDocument>
#include "Rule.h"
#include "XmlObject.h"
#include "UnresolvedReference.h"

class Race;

class RuleList : public virtual XmlObject
{
public:
    RuleList();
    
    RuleList(const RuleList& other);
    
    /*!
     * Delete all allocated rules and rule references from the list. Any
     * pointers to items in this list will be broken.
     */
    virtual ~RuleList();
    
    virtual RuleList& operator=(const RuleList& other);
    virtual bool operator==(const RuleList& other) const;
    
    Rule getRule(const QString& id) const;
    Rule* getRule(const QString& id);
    QList<Rule> findRulesByName(const QString& name) const;
    QList<Rule> rules() const;
    QList<Rule*> rules();
    
    /*!
     * true: rule was added
     * false: rule already existed and was updated
     */
    Rule* addRule(const Rule& rule);
    
    bool hasRule(const QString& id) const;
    
    /*!
     * Remove the given rule from the rule lsit
     */
    bool removeRule(const Rule& rule);
    
    virtual QDomElement& toXml(QDomDocument& doc, QDomElement& parent) const
        throw(ValidationException);
    
    
    /*!
     * Subclasses need to override this to output the Race that this RuleList
     * corresponds to. This method is used internally for resolving rule
     * references via the resolveReferences() method.
     */
    //virtual const Race& race() const = 0;
    
    /*!
     * Resolve rule references.
     */
    //virtual void resolveReferences() throw(UnresolvedReferenceException);
    
protected:
    
    /*!
     * Used for classes that override this one.
     */
    virtual void fromXml(const QDomElement& ele) throw(XmlParseException);
    
private:
    QHash<QString, Rule> m_rules;
};

#endif // RULELIST_H
