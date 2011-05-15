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


#ifndef RACE_H
#define RACE_H

#include <QString>
#include "Game.h"
#include "UnitList.h"
#include "WargearList.h"
#include "RuleSet.h"
#include "Rule.h"
#include "RuleList.h"
#include "UnresolvedReference.h"

class Race : public virtual UnitList, public virtual WargearList, public virtual RuleSet
{
public:
    Race(const Game *game = NULL);
    Race(const Race& other);
    Race(const QDomDocument& doc) throw(XmlParseException);
    virtual ~Race();
    //virtual Race& operator=(const Race& other);
    virtual bool operator==(const Race& other) const;
    
    const QString& name() const;
    const Game* game() const;
    const QString& id() const;
    
    void name(const QString& nm);
    void game(const Game& gm);
    void id(const QString& rid);
    
    virtual QDomElement& toXml(QDomDocument& doc, QDomElement& parent) const
        throw(ValidationException);
    
    const QString& parsedGameId() const;
    virtual void resolveReferences(const Game& game)
        throw(UnresolvedReferenceException);
    
    virtual const Race& race() const;
    
    virtual const Rule* resolveRuleReference(const QString& id)
        throw(UnresolvedReferenceException);
    
protected:
    virtual void fromXml(const QDomElement& ele) throw(XmlParseException);
    
private:
    const Game *m_game;
    UnresolvedReference m_unresolvedGame;
    QString m_name;
    QString m_id;
};

#endif // RACE_H
