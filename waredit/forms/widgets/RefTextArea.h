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


#ifndef REFTEXTAREA_H
#define REFTEXTAREA_H

#include <QTextBrowser>
#include "Game.h"
#include "Race.h"

class RefTextArea : public QTextBrowser
{

public:
    Q_OBJECT
    
    RefTextArea(Game *game, QWidget *parent = 0);
    RefTextArea(Race *race, QWidget *parent = 0);
    virtual ~RefTextArea();
    
signals:
        void ruleRefClicked(const RuleRef& ref);
        void wargearRefClicked(const WargearRef& ref);
        void unitRefClicked(const Unit& ref);
    
private slots:
    void linkClicked(const QUrl& url);
        
    
private:
    Game *m_game;
    Race *m_race;
};

#endif // REFTEXTAREA_H
