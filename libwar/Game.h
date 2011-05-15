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


#ifndef GAME_H
#define GAME_H

#include <QString>
#include "RuleSet.h"
#include "XmlObject.h"

class Game : public virtual RuleSet
{

public:
    Game();
    Game(QDomDocument& doc) throw(XmlParseException);
    Game(const Game& other);
    virtual ~Game();
    //virtual Game& operator=(const Game& other);
    virtual bool operator==(const Game& other) const;
    
    virtual QDomElement& toXml(QDomDocument& doc, QDomElement& parent) const
        throw(ValidationException);
    
    const QString& name() const;
    const QString& id() const;
    
    void name(const QString& nm);
    void id(const QString& gid);
    
    const Race& race() const;
    
protected:
    virtual void fromXml(const QDomElement& ele) throw(XmlParseException);
    
private:
    QString m_name;
    QString m_id;
};

//typedef Reference<Game> GameRef;

#endif // GAME_H
