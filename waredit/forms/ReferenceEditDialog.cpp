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


#include "ReferenceEditDialog.h"
#include "ReferenceEditDialog.moc"
#include "../ListSearch.h"
#include <QMessageBox>
#include <QDebug>

ReferenceEditDialog::ReferenceEditDialog(QWidget* parent, QList< Rule* > gameRules, 
                                         QList<Rule*> raceRules) : QDialog(parent)
{
    m_opMode = RuleMode;
    m_rules = gameRules + raceRules;
    m_gameRuleCount = gameRules.length();
    m_map = mkmap(m_rules);
    setupList();
}

ReferenceEditDialog::ReferenceEditDialog(QWidget* parent, QList< Wargear* > wargears): QDialog(parent)
{
    m_opMode = WargearMode;
    m_wargears = wargears;
    m_gameRuleCount = 0;
    m_map = mkmap(m_wargears);
    setupList();
}

ReferenceEditDialog::~ReferenceEditDialog()
{

}


void ReferenceEditDialog::setupList()
{
    setupUi(this);
    m_populateNameField = true;
    searchButton->setIcon(QIcon::fromTheme("edit-find"));
    searchButton->setText("Find");
    
    connect(refList, SIGNAL(currentRowChanged(int)), SLOT(selectionChanged(int)));
    connect(searchButton, SIGNAL(clicked()), SLOT(search()));
    connect(searchEdit, SIGNAL(returnPressed()), SLOT(search()));
    connect(searchEdit, SIGNAL(searchCleared()), SLOT(search()));
    connect(saveBox, SIGNAL(accepted()), SLOT(validate()));
    connect(saveBox, SIGNAL(rejected()), SLOT(reject()));
    
    populateList();
    selectionChanged(-1);
}

void ReferenceEditDialog::populateList()
{
    refList->clear();
    int len = m_map.length();
    if(m_opMode == RuleMode)
    {
        for(int i = 0; i < len; i++)
            refList->addItem(m_rules[m_map[i]]->name());
    }
    else
    {
        for(int i = 0; i < len; i++)
            refList->addItem(m_wargears[m_map[i]]->name());
    }
}


void ReferenceEditDialog::selectionChanged(int index)
{
    QString name;
    m_selectedIndex = index;
    if(index >= 0)
    {
        saveBox->button(QDialogButtonBox::Ok)->setEnabled(true);
        if(m_opMode == RuleMode)
            name = m_rules[m_map[index]]->name();
        else
            name = m_wargears[m_map[index]]->name();
        
        nameEdit->setEnabled(true);
    }
    else
    {
        saveBox->button(QDialogButtonBox::Ok)->setEnabled(false);
        name = "";
        nameEdit->setEnabled(false);
    }
    
    if(m_populateNameField) nameEdit->setText(name);
    qDebug() << "selection changed: " << index;
}

QString ReferenceEditDialog::refName()
{
    return nameEdit->text().trimmed();
}

int ReferenceEditDialog::selectedIndex()
{
    if(m_selectedIndex >= 0)
    {
        int index = m_map[m_selectedIndex];
        if(index >= m_gameRuleCount && m_opMode == RuleMode)
            index -= m_gameRuleCount;
        
        return index;
    }
    
    return -1;
}

int ReferenceEditDialog::getRuleSelectedFrom()
{
    if(m_selectedIndex >= 0)
        return m_map[m_selectedIndex] >= m_gameRuleCount ? RaceRuleList : GameRuleList;
    
    return NoList;
}


void ReferenceEditDialog::search()
{
    qDebug() << "search()";
    QString str = searchEdit->text().trimmed();
    if(str.isEmpty())
    {
        if(m_opMode == RuleMode)
            m_map = mkmap(m_rules);
        else
            m_map = mkmap(m_wargears);
    }
    else
    {
        if(m_opMode == WargearMode)
            m_map = searchList(m_wargears, str, true);
        else
            m_map = searchList(m_rules, str, true);
    }
    
    populateList();
}

RuleRef ReferenceEditDialog::getRuleRef(QWidget* parent,
    QList< Rule* >& gameRules, QList< Rule* >& raceRules,
    const QString& title, RuleRef *out)
{
    ReferenceEditDialog dia(parent, gameRules, raceRules);
    RuleRef rr;
    dia.setWindowTitle(title);
    if(out)
    {
        int index = gameRules.indexOf(const_cast<Rule*>(out->rule()));
        if(index < 0)
        {
            qDebug() << "not a game rule";
            index = raceRules.indexOf(const_cast<Rule*>(out->rule()));
            if(index < 0)
            {
                qDebug() << "not a race rule";
                index = 0;
            }
            else
                index += dia.m_gameRuleCount;
        }
        
        qDebug() << "index: " << index;
        dia.m_populateNameField = false;
        dia.refList->setCurrentRow(index);
        dia.nameEdit->setText(out->name());
    }
    
    if(dia.exec() == QDialog::Accepted)
    {
        int index = dia.selectedIndex();
        Rule *rule;
        if(dia.getRuleSelectedFrom() == ReferenceEditDialog::GameRuleList)
            rule = gameRules[index];
        else
            rule = raceRules[index];
        
        QString refName = dia.refName();
        
        rr = RuleRef(*rule, refName);
        if(out)
            *out = rr;
    }
    
    return rr;
}

void ReferenceEditDialog::validate()
{
    qDebug() << "validate()";
    if(m_selectedIndex < 0)
    {
        QMessageBox::warning(this, "Must Select Reference",
                             "You must select a reference");
    }
    else
        emit accept();
}


WargearRef ReferenceEditDialog::getWargearRef(QWidget* parent,
    QList< Wargear* > wargears, const QString& title, WargearRef* ref)
{
    ReferenceEditDialog dia(parent, wargears);
    WargearRef wr;
    dia.setWindowTitle(title);
    
    if(ref)
    {
        int index = wargears.indexOf(const_cast<Wargear*>(ref->wargear()));
        if(index < 0)
            index = 0;
        
        dia.m_populateNameField = false;
        dia.refList->setCurrentRow(index);
        dia.nameEdit->setText(ref->name());
    }
    
    if(dia.exec() == QDialog::Accepted)
    {
        qDebug() << "accepted";
        int index = dia.selectedIndex();
        Wargear *wargear = wargears[index];
        QString refName = dia.refName();
        
        wr = WargearRef(*wargear, refName);
        if(ref)
            *ref = wr;
        
        qDebug() << "done";
    }
    
    return wr;
}




