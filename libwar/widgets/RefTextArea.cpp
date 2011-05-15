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


#include "RefTextArea.h"
#include "RefTextArea.moc"
#include <QMessageBox>

RefTextArea::RefTextArea(QWidget* parent, const WarPage& page) : m_page(page),
    QTextBrowser(parent)
{
    setOpenLinks(false);
    setOpenExternalLinks(false);
    setHtml(m_page.toHtml());
    connect(this, SIGNAL(anchorClicked(QUrl)), SLOT(linkClicked(QUrl)));
}


RefTextArea::~RefTextArea()
{
    //delete m_page;
}


void RefTextArea::linkClicked(const QUrl& url)
{
    QString name = url.queryItemValue("name");
    QString id = url.host();
    if(url.scheme() == "rule")
    {
        const Rule *r = m_page.ruleList()->resolveRuleReference(id);
        RuleRef ref(*r, name);
        
        emit ruleRefClicked(ref);
    }
    else if(url.scheme() == "wargear")
    {
        Wargear *w = m_page.race()->getWargear(id);
        WargearRef ref(*w, name);
        emit wargearRefClicked(ref);
    }
    else if(url.scheme() == "unit")
    {
        Unit *u = m_page.race()->getUnit(id);
        emit unitRefClicked(*u);
    }
}

void RefTextArea::setHtml(const QString& txt)
{
    QTextBrowser::setHtml(txt);
}

void RefTextArea::setPlainText(const QString& txt)
{
    QTextBrowser::setPlainText(txt);
}



