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


#include "WarPageViewer.h"
#include "WarPageViewer.moc"
#include <QHBoxLayout>
#include <QDebug>
#include "RefTextArea.h"
#include "SearchLineEdit.h"
#include <QLabel>
#include <QToolBar>
#include <QAction>

WarPageViewer::WarPageViewer(QWidget* parent, WarPage *page) : QTabWidget(parent)
{
    connect(this, SIGNAL(tabCloseRequested(int)), SLOT(onCloseTab(int)));
    m_doClear = false;
    m_keepOpenCount = 1;
    this->setTabsClosable(true);
    if(page)
    {
        m_race = page->race();
        m_rules = page->ruleList();
        appendPage(*page);
    }
    
    QAction *findAction = new QAction(this);
    findAction->setShortcut(QKeySequence::Find);
    this->addAction(findAction);
    connect(findAction, SIGNAL(triggered()), SLOT(doSetFocusFind()));
}

WarPageViewer::~WarPageViewer()
{

}

void WarPageViewer::setFirstPage(WarPage& page)
{
    m_race = page.race();
    m_rules = page.ruleList();
    appendPage(page);
}


void WarPageViewer::appendPage(const WarPage& page)
{
    qDebug() << "begin appendPage()";
    QWidget *tab = new QWidget(this);
    QVBoxLayout *vbox = new QVBoxLayout(tab);
    QToolBar *bar = new QToolBar(tab);
    RefTextArea *area = new RefTextArea(tab, page);
    QHBoxLayout *hbox = new QHBoxLayout(tab);
    SearchLineEdit *search = new SearchLineEdit(tab);
    QPushButton *searchNext = new QPushButton(tab);
    QPushButton *searchPrevious = new QPushButton(tab);
    QLabel *findLabel = new QLabel(tab);
    
    QIcon up, down;
    up.addFile(":/icons/go-up-search.png");
    down.addFile(":/icons/go-down-search.png");
    
    searchNext->setText("Next");
    searchNext->setIcon(down);
    searchPrevious->setText("Previous");
    searchPrevious->setIcon(up);
    findLabel->setText("Find: ");
    
    bar->setMovable(false);
    bar->setFloatable(false);
    QAction *zoomin = bar->addAction(QIcon(":/icons/toolbar/zoom-in.png"), "Zoom In");
    QAction *zoomoriginal = bar->addAction(QIcon(":/icons/toolbar/zoom-original.png"), "Zoom Original");
    QAction *zoomout = bar->addAction(QIcon(":/icons/toolbar/zoom-out.png"), "Zoom Out");
    
    connect(zoomin, SIGNAL(triggered()), SLOT(doTabZoomIn()));
    connect(zoomout, SIGNAL(triggered()), SLOT(doTabZoomOut()));
    connect(zoomoriginal, SIGNAL(triggered()), SLOT(doTabZoomOriginal()));
    
    
    hbox->addWidget(findLabel);
    hbox->addWidget(search);
    hbox->addWidget(searchNext);
    hbox->addWidget(searchPrevious);
    vbox->addWidget(bar);
    vbox->addWidget(area);
    vbox->addLayout(hbox);
    
    tab->setLayout(vbox);
    
    
    connect(area, SIGNAL(ruleRefClicked(const RuleRef&)), SLOT(onRuleClicked(const RuleRef&)));
    connect(area, SIGNAL(unitRefClicked(const Unit&)), SLOT(onUnitClicked(const Unit&)));
    connect(area, SIGNAL(wargearRefClicked(const WargearRef&)), SLOT(onWargearClicked(const WargearRef&)));
    connect(search, SIGNAL(textChanged(const QString&)), SLOT(onSearchTextChanged(const QString&)));
    connect(search, SIGNAL(returnPressed()), SLOT(doSearchNext()));
    connect(searchNext, SIGNAL(clicked()), SLOT(doSearchNext()));
    connect(searchPrevious, SIGNAL(clicked()), SLOT(doSearchPrevious()));
    
    addTab(tab, page.name());
    
    TabPage tp;
    tp.doSearch[0] = searchNext;
    tp.doSearch[1] = searchPrevious;
    tp.search = search;
    tp.text = area;
    tp.id = page.id();
    tp.zoom = 0;
    m_tabs.append(tp);
    
    setCurrentIndex(m_tabs.length() - 1);
    onSearchTextChanged("");
    qDebug() << "end appendPage()";
}


void WarPageViewer::onRuleClicked(const RuleRef& ref)
{
    qDebug() << "begin onRuleClicked()";
    int index = indexOf(ref.id());
    
    if(index >= 0)
        setCurrentIndex(index);
    else
    {
        WarPage page(ref, *m_rules, m_race);
        appendPage(page);
    }
    qDebug() << "end onRuleClicked()";
}

void WarPageViewer::onUnitClicked(const Unit& ref)
{
    int index = indexOf(ref.id());
    if(index >= 0)
        setCurrentIndex(index);
    else
    {
        WarPage page(ref, *m_race);
        appendPage(page);
    }
}

void WarPageViewer::onWargearClicked(const WargearRef& ref)
{
    int index = indexOf(ref.id());
    if(index >= 0)
        setCurrentIndex(index);
    else
    {
        WarPage page(ref, *m_race);
        appendPage(page);
    }
}


void WarPageViewer::onCloseTab(int index)
{
    if(index >= m_keepOpenCount || m_doClear)
    {
        m_tabs.removeAt(index);
        removeTab(index);
    }
}

void WarPageViewer::clear()
{
    m_doClear = true;
    QTabWidget::clear();
    m_tabs.clear();
    m_doClear = false;
}


int WarPageViewer::indexOf(const QString& id) const
{
    int index = -1, len = m_tabs.length();
    for(int i = 0; i < len && index < 0; i++)
    {
        if(m_tabs[i].id == id)
            index = i;
    }
    
    return index;
}

WarPageViewer::TabPage& WarPageViewer::currentTabPage()
{
    return m_tabs[currentIndex()];
}

void WarPageViewer::doSearchNext()
{
    TabPage& tab = currentTabPage();
    QString find = tab.search->text().trimmed();
    
    if(!find.isEmpty())
    {
        int status = tab.text->find(find) ? 1 : 0;
        setSearchBgColor(tab, status);
    }
    
}

void WarPageViewer::doSearchPrevious()
{
    TabPage& tab = currentTabPage();
    QString find = tab.search->text().trimmed();
    
    if(!find.isEmpty())
    {
        int status = tab.text->find(find, QTextDocument::FindBackward) ? 1 : 0;
        setSearchBgColor(tab, status);
    }
}

void WarPageViewer::onSearchTextChanged(const QString& txt)
{
    TabPage& tab = currentTabPage();
    tab.text->clearSelection();
    bool enable = !txt.isEmpty();
    
    if(tab.doSearch[0]->isEnabled() != enable)
    {
        tab.doSearch[0]->setEnabled(enable);
        tab.doSearch[1]->setEnabled(enable);
    }
    
    if(enable)
        doSearchNext();
    else
        setSearchBgColor(tab, -1);
}

void WarPageViewer::setSearchBgColor(WarPageViewer::TabPage& tab, int found)
{
    QPalette pal = palette();
    QColor color;
    if(found == 0)
        color.setRgb(0xff, 0xdd, 0xdd);
    else if(found == 1)
        color.setRgb(0xdd, 0xdd, 0xff);
    else
        color = pal.color(QPalette::Active, QPalette::Base);
    
    pal.setColor(QPalette::Active, QPalette::Base, color);
    tab.search->setPalette(pal);
}


void WarPageViewer::doTabZoomIn()
{
    TabPage& tab = currentTabPage();
    tab.text->zoomIn(1);
    tab.zoom++;
}

void WarPageViewer::doTabZoomOut()
{
    TabPage& tab = currentTabPage();
    tab.text->zoomOut(1);
    tab.zoom--;
}

void WarPageViewer::doTabZoomOriginal()
{
    TabPage& tab = currentTabPage();
    if(tab.zoom < 0)
        tab.text->zoomIn(-tab.zoom);
    else if(tab.zoom > 0)
        tab.text->zoomOut(tab.zoom);
    
    tab.zoom = 0;
}

void WarPageViewer::doSetFocusFind()
{
    if(count() > 0)
    {
        qDebug() << "here";
        TabPage& tab = currentTabPage();
        if(!tab.search->hasFocus())
            tab.search->setFocus();
    }
}





