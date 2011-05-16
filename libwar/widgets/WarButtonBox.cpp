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


#include "WarButtonBox.h"
#include "WarButtonBox.moc"

WarButtonBox::WarButtonBox(QWidget* parent): QDialogButtonBox(parent)
{

}


WarButtonBox::~WarButtonBox()
{

}

QPushButton* WarButtonBox::apply()
{
    return button(Apply);
}

QPushButton* WarButtonBox::cancel()
{
    return button(Cancel);
}

QPushButton* WarButtonBox::close()
{
    return button(Close);
}

QPushButton* WarButtonBox::discard()
{
    return button(Discard);
}

QPushButton* WarButtonBox::ok()
{
    return button(Ok);
}

void WarButtonBox::setButtonIcon(QAbstractButton *b)
{
    if(b->icon().isNull())
    {
        QIcon icon;
        StandardButton which = standardButton(b);
        if(which == Ok || which == Apply)
            icon.addFile(":/icons/dialog-ok-apply.png");
        else if(which == Discard || which == Cancel)
            icon.addFile(":/icons/dialog-cancel.png");
        else if(which == Close)
            icon.addFile(":/icons/window-close.png");
        
        if(!icon.isNull())
            b->setIcon(icon);
    }
}

void WarButtonBox::setStandardButtons(QDialogButtonBox::StandardButtons buttons)
{
    QDialogButtonBox::setStandardButtons(buttons);
    QList<QAbstractButton*> bs = this->buttons();
    int len = bs.length();
    for(int i = 0; i < len; i++)
        setButtonIcon(bs[i]);
}


