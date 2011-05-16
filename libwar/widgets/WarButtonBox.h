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


#ifndef WARBUTTONBOX_H
#define WARBUTTONBOX_H

#include <QDialogButtonBox>
#include <QPushButton>

class WarButtonBox : public QDialogButtonBox
{
    Q_OBJECT
    
public:
    WarButtonBox(QWidget *parent = 0);
    virtual ~WarButtonBox();
    
    QPushButton *ok();
    QPushButton *cancel();
    QPushButton *apply();
    QPushButton *discard();
    QPushButton *close();
    
    void setStandardButtons(StandardButtons buttons);
    
private:
    void setButtonIcon(QAbstractButton *b);
    
};

#endif // WARBUTTONBOX_H
