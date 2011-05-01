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


#ifndef WARPAGEVIEWER_H
#define WARPAGEVIEWER_H
#include <QTabWidget>
#include <WarPage.h>

class WarPageViewer : public QTabWidget
{
    Q_OBJECT
    
public:
    WarPageViewer(QWidget* parent = 0, WarPage* page = 0);
    void setFirstPage(WarPage *page);
    virtual ~WarPageViewer();
    
private slots:
    void onRuleClicked(const RuleRef& ref);
    void onCloseTab(int index);
    
private:
    void appendPage(WarPage* page);
    QList<QString> m_tabIds;
    Race *m_race;
    RuleList *m_rules;
};

#endif // WARPAGEVIEWER_H
