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


#include "WarPageViewer.h"
#include "WarPageViewer.moc"
#include <QHBoxLayout>
#include <QDebug>
#include "RefTextArea.h"
#include "SearchLineEdit.h"

WarPageViewer::WarPageViewer(QWidget* parent, WarPage *page) : QTabWidget(parent)
{
    connect(this, SIGNAL(tabCloseRequested(int)), SLOT(onCloseTab(int)));
    this->setTabsClosable(true);
    if(page)
    {
        m_race = page->race();
        m_rules = page->ruleList();
        appendPage(page);
    }
}

WarPageViewer::~WarPageViewer()
{

}

void WarPageViewer::setFirstPage(WarPage* page)
{
    m_race = page->race();
    m_rules = page->ruleList();
    appendPage(page);
}


void WarPageViewer::appendPage(WarPage *page)
{
    qDebug() << "begin appendPage()";
    m_tabIds.append(page->id());
    QWidget *tab = new QWidget();
    QHBoxLayout *layout = new QHBoxLayout(tab);
    RefTextArea *area = new RefTextArea(0, page);
    //SearchLineEdit *search = new SearchLineEdit();
    layout->addWidget(area);
    //layout->addWidget(search);
    tab->setLayout(layout);
    
    connect(area, SIGNAL(ruleRefClicked(const RuleRef&)), SLOT(onRuleClicked(const RuleRef&)));
    //connect(search, SIGNAL(returnPressed()), SLOT(doSearch()));
    addTab(tab, page->name());
    setCurrentIndex(m_tabIds.length()-1);
    qDebug() << "end appendPage()";
}


void WarPageViewer::onRuleClicked(const RuleRef& ref)
{
    qDebug() << "begin onRuleClicked()";
    int index = m_tabIds.indexOf(ref.id());
    
    if(index >= 0)
        setCurrentIndex(index);
    else
    {
        WarPage *page = new WarPage(ref, *m_rules, m_race);
        appendPage(page);
    }
    qDebug() << "end onRuleClicked()";
}

void WarPageViewer::onCloseTab(int index)
{
    if(index > 0)
    {
        m_tabIds.removeAt(index);
        removeTab(index);
    }
}
