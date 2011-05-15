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


#ifndef WARDOCUMENT_H
#define WARDOCUMENT_H
#include <QString>
#include <QTextDocument>
#include <QDomElement>
#include "Race.h"

class WarDocument
{
public:
    //WarDocument(const QString& text);
    //WarDocument(const QTextDocument& document); // <--- TODO
    //WarDocument(const QDomElement& ele);
    WarDocument(const WarDocument& other);
    WarDocument(Game& game);
    WarDocument& operator=(const WarDocument& other);
    
    QTextDocument& toTextDocument() const;
    //void setContent(const QString& text);
    //void setContent(const QTextDocument& document);
    
    
private:
    QTextDocument m_document;
};

#endif // WARDOCUMENT_H
