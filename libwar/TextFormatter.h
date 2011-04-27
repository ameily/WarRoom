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


#ifndef TEXTFORMATTER_H
#define TEXTFORMATTER_H
#include <QString>
#include "Game.h"
#include "Race.h"

class TextFormatter
{
public:
    static void destroy();
    static TextFormatter& instance();
    
    QString toHtml(const QString& in, Game& game) const;
    QString toHtml(const QString& in, Race& race) const;
    QString fromXml(const QDomElement& ele) const;
    
private:
    static TextFormatter *m_instance;
    TextFormatter();
    
    struct ReferenceString
    {
        QString prefix;
        QString name;
        QString id;
        QString title;
    };
    
    
    void parseRefs(QString& in, Game *game, Race *race) const;
    QString resolveRef(TextFormatter::ReferenceString& ref, Game* game, Race* race) const;
    void toHtml(QString& out) const;
};

#endif // TEXTFORMATTER_H
