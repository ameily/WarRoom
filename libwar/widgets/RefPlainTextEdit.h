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


#ifndef REFPLAINTEXTEDIT_H
#define REFPLAINTEXTEDIT_H
#include <QWidget>
#include <QPlainTextEdit>
#include <QMenu>

class RefPlainTextEdit : public QPlainTextEdit
{
    Q_OBJECT
    
public:
    RefPlainTextEdit(QWidget *parent = 0);
    virtual ~RefPlainTextEdit();
    void setPlainText(const QString& txt);
    void clear();
    
//public slots:
//    void previewDone();

//protected:
//    void contextMenuEvent(QContextMenuEvent *event);
    
signals:
    void textEdited();
//    void previewEnabled();
    
private slots:
    void onTextChanged();
//    void doPreview();
    
private:
    bool m_isProgrammaticChange;
};

#endif // REFPLAINTEXTEDIT_H
