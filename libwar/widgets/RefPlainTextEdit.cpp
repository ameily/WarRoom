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


#include "RefPlainTextEdit.h"
#include "RefPlainTextEdit.moc"

RefPlainTextEdit::RefPlainTextEdit(QWidget* parent): QPlainTextEdit(parent)
{
    connect(this, SIGNAL(textChanged()), SLOT(onTextChanged()));
}

RefPlainTextEdit::~RefPlainTextEdit()
{

}

void RefPlainTextEdit::clear()
{
    m_isProgrammaticChange = true;
    QPlainTextEdit::clear();
    m_isProgrammaticChange = false;
}

void RefPlainTextEdit::setPlainText(const QString& txt)
{
    m_isProgrammaticChange = true;
    QPlainTextEdit::setPlainText(txt);
    m_isProgrammaticChange = false;
}

void RefPlainTextEdit::onTextChanged()
{
    if(!m_isProgrammaticChange)
        emit textEdited();
}
/*
void RefPlainTextEdit::contextMenuEvent(QContextMenuEvent* event)
{
    QMenu *menu = createStandardContextMenu();
    QAction *preview = menu->addAction("Preview Formatted Text");
    if(menu->exec(event->globalPos()) == preview)
        doPreview();
    
    delete menu;
}

void RefPlainTextEdit::doPreview()
{

}

void RefPlainTextEdit::previewDone()
{
    
    
}
*/
