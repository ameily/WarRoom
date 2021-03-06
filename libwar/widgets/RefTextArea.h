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


#ifndef REFTEXTAREA_H
#define REFTEXTAREA_H

#include <QTextBrowser>
#include "../Game.h"
#include "../Race.h"
#include "../WarPage.h"

class RefTextArea : public QTextBrowser
{
    Q_OBJECT
    
public:
    RefTextArea(QWidget* parent, const WarPage& page);
    virtual ~RefTextArea();
    void clearSelection();
    
signals:
        void ruleRefClicked(const RuleRef& ref);
        void wargearRefClicked(const WargearRef& ref);
        void unitRefClicked(const Unit& ref);
    
private slots:
    void linkClicked(const QUrl& url);
        
    
private:
    void setHtml(const QString& txt);
    void setPlainText(const QString& txt);
    QTextDocument *m_warDocument;
    WarPage m_page;
};

#endif // REFTEXTAREA_H
