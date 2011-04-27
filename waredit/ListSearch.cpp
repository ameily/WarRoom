/*
    This file is part of the War Edit application (waredit)
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

#include "ListSearch.h"

QList< int > mkmap(const QList< Rule* >& in)
{
    QList<int> ret;
    int len = in.length();
    for(int i = 0; i < len; i++)
        ret.insert(i, i);
    
    return ret;
}

QList< int > mkmap(const QList< Wargear* >& in)
{
    QList<int> ret;
    int len = in.length();
    for(int i = 0; i < len; i++)
        ret.insert(i, i);
    
    return ret;
}

QList< int > searchList(const QList< Rule* >& in, const QString& str, bool includeID)
{
    int len = in.length();
    QList<int> ret;
    Rule *current;
    for(int i = 0; i < len; i++)
    {
        current = in[i];
        if(current->name().contains(str, Qt::CaseInsensitive) ||
            (includeID && current->id().contains(str, Qt::CaseInsensitive)))
        {
            ret.append(i);
        }
    }
    
    return ret;
}

QList< int > searchList(const QList< Wargear* >& in, const QString& str, bool includeID)
{
    int len = in.length();
    QList<int> ret;
    Wargear *current;
    for(int i = 0; i < len; i++)
    {
        current = in[i];
        if(current->name().contains(str, Qt::CaseInsensitive) ||
            (includeID && current->id().contains(str, Qt::CaseInsensitive)))
        {
            ret.append(i);
        }
    }
    
    return ret;
}


