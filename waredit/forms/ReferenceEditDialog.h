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


#ifndef REFERENCEEDITDIALOG_H
#define REFERENCEEDITDIALOG_H

#include "designer/ui_RefEditDialog.h"
#include <QDialog>
#include <Rule.h>
#include <Wargear.h>

class ReferenceEditDialog : public QDialog, public Ui::RefEditDialog
{
    Q_OBJECT
public:
    enum OpMode { RuleMode, WargearMode };
    enum RuleSelectedFrom { NoList, GameRuleList, RaceRuleList };
    
    ReferenceEditDialog(QWidget* parent, QList<Rule*> gameRules, QList<Rule*> raceRules);
    ReferenceEditDialog(QWidget* parent, QList<Wargear*> wargears);
    
    static RuleRef getRuleRef(QWidget* parent, QList<Rule*>& gameRules, 
                      QList<Rule*>& raceRules, const QString& title, RuleRef *out = 0);
    
    static WargearRef getWargearRef(QWidget *parent, QList<Wargear*> wargears,
                                    const QString& title, WargearRef *ref = 0);
    virtual ~ReferenceEditDialog();
    
    int selectedIndex();
    QString refName();
    int getRuleSelectedFrom();
    
    
private slots:
    void selectionChanged(int index);
    void search();
    void validate();
    
    
private:
    void setupList();
    void populateList();
    QList<Rule*> m_rules;
    int m_gameRuleCount;
    QList<Wargear*> m_wargears;
    QList<int> m_map;
    int m_selectedIndex;
    int m_opMode;
    int m_ruleSelectedFrom;
    bool m_populateNameField;
};

#endif // REFERENCEEDITDIALOG_H
