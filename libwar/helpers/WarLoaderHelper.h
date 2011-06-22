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


#ifndef WARLOADERHELPER_H
#define WARLOADERHELPER_H
#include "../Game.h"
#include "../Race.h"
#include <QDomDocument>
#include <QDir>

class WarLoaderHelper
{
public:
    enum WarFileFilter
    {
        GameFilter = 1,
        RaceFilter = 2,
        ArmyFilter = 4
    };
    Q_DECLARE_FLAGS(WarFileFilters, WarFileFilter);
    
    class LoadException
    {
    public:
        LoadException(const XmlParseException& e, const QString& filename);
        LoadException(const UnresolvedReferenceException& e, const QString& filename);
        LoadException(const QString& desc, const QString& filename);
        LoadException(const QString& msg, int line, const QString& filename);
        LoadException(const LoadException& other);
        
        const QString& message() const;
    private:
        QString val(const QString& s) const;
        QString m_msg;
    };
    
    WarLoaderHelper(QWidget* parent, const QString& pwd);
    Game* loadGame(QString& filename) throw(LoadException);
    Race* loadRace(QString& filename, Game **game) throw(LoadException);
    bool loadFile(QString& filename, Race **race, Game **game, WarFileFilters filters) throw(LoadException);
    QString pwdString() const;
    void setPwd(const QString& path);
    
private:
    QString getFileName(WarFileFilters filters);
    QWidget *m_parent;
    QDir m_pwd;
};

Q_DECLARE_OPERATORS_FOR_FLAGS(WarLoaderHelper::WarFileFilters);

#endif // WARLOADERHELPER_H
