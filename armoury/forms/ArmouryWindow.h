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

#ifndef ARMOURYWINDOW_H
#define ARMOURYWINDOW_H

#include <QMainWindow>
#include <QDomDocument>
#include <QFile>
#include "designer/ui_ArmouryWindow.h"
#include <helpers/WarLoaderHelper.h>

class ArmouryWindow : public QMainWindow, public Ui::MainArmouryWindow
{
    Q_OBJECT
    
public:
    ArmouryWindow(QWidget *parent, const QString& pwd);
    virtual ~ArmouryWindow();
    void setPwd(const QString& dir);
    
private slots:
    void onMenuOpenFile();
    
private:
    QString m_pwd;
    void cleanup();
    void closeOpenFile();
    //bool openXml(QDomDocument& doc, QFile* file);
    WarLoaderHelper *m_loader;
    bool m_viewingFile;
    Game *m_game;
    Race *m_race;
    //Race *m_race;
};

#endif // ARMOURYWINDOW_H
