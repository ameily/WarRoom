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


#include "WarLoaderHelper.h"
#include <QFile>
#include <QFileDialog>
#include <QDebug>

WarLoaderHelper::WarLoaderHelper(QWidget *parent, const QString& pwd) : m_pwd(pwd)
{
    m_parent = parent;
}

QString WarLoaderHelper::pwdString() const
{
    return m_pwd.absolutePath();
}

void WarLoaderHelper::setPwd(const QString& path)
{
    QFileInfo info(path);
    m_pwd = info.isDir() ? info.absoluteDir() : info.dir();
}



Game* WarLoaderHelper::loadGame(QString& filename) throw(WarLoaderHelper::LoadException)
{
    Game *ret = 0;
    loadFile(filename, 0, &ret, GameFilter);
    
    return ret;
}

Race* WarLoaderHelper::loadRace(QString& filename, Game** game) throw(WarLoaderHelper::LoadException)
{
    Race *race = 0;
    loadFile(filename, &race, game, RaceFilter);
    
    return race;
}

QString WarLoaderHelper::getFileName(WarLoaderHelper::WarFileFilters filters)
{
    QString filter;
    QString title;
    
    if(filters.testFlag(RaceFilter) && filters.testFlag(GameFilter))
    {
        title = "Open War File";
        filter = "War Files (*.race *.game);;Races (*.race);;Games (*.game)";
    }
    else if(filters.testFlag(GameFilter))
    {
        title = "Open Game";
        filter = "Games (*.game)";
    }
    else if(filters.testFlag(RaceFilter))
    {
         title = "Open Race";
         filter = "Races (*.race)";
    }
    else
        return "";
    
    QString path = QFileDialog::getOpenFileName(m_parent, title,
            m_pwd.path(), filter);
    
    return path;
}

bool WarLoaderHelper::loadFile(QString& filename, Race** race, Game** game,
    WarLoaderHelper::WarFileFilters filters) throw(WarLoaderHelper::LoadException)
{
    qDebug() << "loadFile(): pwd  = " << m_pwd.absolutePath();
    qDebug() << "loadFile(): name = " << filename;
    
    if(filename.isEmpty() || !m_pwd.exists(filename))
        filename = getFileName(filters);
    else
        filename = m_pwd.absoluteFilePath(filename);
    
    qDebug() << "before isempty()";
    if(!filename.isEmpty())
    {
        QDomDocument doc;
        QFile fp(filename);
        if(!fp.open(QIODevice::ReadOnly))
            throw LoadException(filename, fp.errorString());
        
        QString error;
        int line;
        if(!doc.setContent(&fp, &error, &line))
        {
            fp.close();
            throw LoadException(error, line, filename);
        }
        
        try
        {
            if(game && race && doc.documentElement().tagName() == "race")
            {
                *race = new Race(doc);
                try
                {
                    if(!*game)
                    {
                        QString gameFile = (*race)->parsedGameId() + ".game";
                        if(!loadFile(gameFile, 0, game, GameFilter))
                        {
                            qDebug() << "before delete";
                            delete *race;
                            *race = 0;
                            qDebug() << "after delete";
                            return false;
                        }
                    }
                }
                catch(LoadException e)
                {
                    delete *race;
                    *race = 0;
                    throw e;
                }
                
                (*race)->resolveReferences(**game);
            }
            else if(game && doc.documentElement().tagName() == "game")
                *game = new Game(doc);
            else
                return false;
            
            setPwd(filename);
        }
        catch(UnresolvedReferenceException e)
        {
            throw LoadException(e, filename);
        }
        catch(XmlParseException e)
        {
            throw LoadException(e, filename);
        }
        
    }
    else
        return false;
    
    return true;
}


WarLoaderHelper::LoadException::LoadException(const XmlParseException& e, const QString& filename)
{
    m_msg = "The file is either invalid, incomplete or corrupted and could not be loaded.\n\n"
            "    File:\t" + QFileInfo(filename).fileName() + "\n"
            "    Reason:\tXML Parse Error\n"
            "    Line:\t" + QString::number(e.line()) + "\n"
            "    Node:\t" + val(e.elementName()) + "\n"
            "    Error:\t" + val(e.description());
}

WarLoaderHelper::LoadException::LoadException(const UnresolvedReferenceException& e, const QString& filename)
{
    m_msg = "The file is either invalid, incomplete or corrupted and could not be loaded.\n\n"
            "    File:\t" + QFileInfo(filename).fileName() + "\n"
            "    Reason:\tUnresolved Reference\n"
            "    Type:\t" + val(e.type()) + "\n"
            "    ID:\t" + val(e.id()) + "\n"
            "    Name:\t" + val(e.name());
}

WarLoaderHelper::LoadException::LoadException(const QString& desc, const QString& filename)
{
    m_msg = "There was an error while loading the file.\n\n"
            "    File:\t" + QFileInfo(filename).fileName() + "\n"
            "    Error:\t" + desc;
}

WarLoaderHelper::LoadException::LoadException(const QString& msg, int line, const QString& filename)
{
    m_msg = "The file is either invalid, incomplete or corrupted and could not be loaded.\n\n"
            "    File:\t" + QFileInfo(filename).fileName() + "\n"
            "    Line:\t" + QString::number(line) + "\n"
            "    Error:\t" + val(msg);
}


WarLoaderHelper::LoadException::LoadException(const WarLoaderHelper::LoadException& other) :
    m_msg(other.m_msg)
{
}

QString WarLoaderHelper::LoadException::val(const QString& s) const
{
    return s.isEmpty() ? "(null)" : s;
}

const QString& WarLoaderHelper::LoadException::message() const
{
    return m_msg;
}
