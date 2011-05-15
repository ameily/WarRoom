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


#include "WarPageViewerDialog.h"
#include "WarPageViewerDialog.moc"
#include <QKeyEvent>

WarPageViewerDialog::WarPageViewerDialog(QWidget* parent, WarPage& page): QDialog(parent)
{
        setupUi(this);
        tabWidget->setFirstPage(page);
        
        connect(buttonBox->button(QDialogButtonBox::Close), SIGNAL(clicked()), SLOT(accept()));
}

WarPageViewerDialog::~WarPageViewerDialog()
{

}

void WarPageViewerDialog::keyPressEvent(QKeyEvent* event)
{
    if(buttonBox->hasFocus() ||
        buttonBox->button(QDialogButtonBox::Close)->hasFocus() &&
        event->key() == Qt::Key_Enter)
    {
        accept();
    }
}

