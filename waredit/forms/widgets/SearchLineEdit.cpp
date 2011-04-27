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


#include "SearchLineEdit.h"
#include "SearchLineEdit.moc"
#include <QResizeEvent>
#include <QStyle>

SearchLineEdit::SearchLineEdit(QWidget* parent): QLineEdit(parent)
{
    m_clearButton = new QToolButton(this);
    QIcon icon;
    icon.addFile(QString::fromUtf8(":/icons/edit-delete.png"), QSize(), QIcon::Normal, QIcon::Off);
    m_clearButton->setIcon(icon);
    //m_clearButton->setIconSize(icon.pixmap().size());
    m_clearButton->setCursor(Qt::ArrowCursor);
    m_clearButton->setStyleSheet("QToolButton { border: none; padding: 0px; }");
    m_clearButton->hide();
    
    connect(m_clearButton, SIGNAL(clicked()), SLOT(onClear()));
    connect(this, SIGNAL(textChanged(const QString&)), SLOT(updateIcon(const QString&)));
    int frameWidth = style()->pixelMetric(QStyle::PM_DefaultFrameWidth);
    setStyleSheet(QString("QLineEdit { padding-right: %1px; } ").arg(
        m_clearButton->sizeHint().width() + frameWidth + 1));
    QSize msz = minimumSizeHint();
    setMinimumSize(qMax(msz.width(), m_clearButton->sizeHint().height() 
        + frameWidth * 2 + 2),
    qMax(msz.height(), 
         m_clearButton->sizeHint().height() + frameWidth * 2 + 2));
    
}

SearchLineEdit::~SearchLineEdit()
{

}

void SearchLineEdit::resizeEvent(QResizeEvent* e)
{
    QSize sz = m_clearButton->sizeHint();
    int frameWidth = style()->pixelMetric(QStyle::PM_DefaultFrameWidth);
    m_clearButton->move(rect().right() - frameWidth - sz.width(),
        (rect().bottom() + 1 - sz.height())/2);
}

void SearchLineEdit::updateIcon(const QString& txt)
{
    m_clearButton->setVisible(!txt.isEmpty());
    
}

void SearchLineEdit::onClear()
{
    clear();
    emit searchCleared();
}


