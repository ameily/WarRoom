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


#ifndef WARGEARPROFILEEDITDIALOG_H
#define WARGEARPROFILEEDITDIALOG_H

#include "designer/ui_WargearProfileEdit.h"
#include <QDialog>
#include <Rule.h>
#include <Wargear.h>
#include <WargearProfile.h>

class WargearProfileEditDialog : public QDialog, public Ui::WargearProfileEditDialog
{
    Q_OBJECT
    
public:
    WargearProfileEditDialog(QWidget *parent, const Wargear *wargear,
        QList<Rule*>& gameRules, QList<Rule*>& raceRules, WargearProfile *edit = 0);
    
    virtual ~WargearProfileEditDialog();
    
    static WargearProfile getWargearProfile(QWidget *parent,
        const Wargear *wargear, QList<Rule*>& gameRules,
        QList<Rule*>& raceRules, WargearProfile *out = 0);
    
    WargearProfile& profile();
    void initDialog();
    
private slots:
    void doAddRuleRef();
    void doEditRuleRef();
    void doRemoveRuleRef();
    void validate();
    void onRuleSelected(int index);
    
private:
    bool m_deleteProfile;
    WargearProfile m_profile;
    QList<RuleRef*> m_profile_rules;
    QList<Rule*> m_game_rules;
    QList<Rule*> m_race_rules;
};

#endif // WARGEARPROFILEEDITDIALOG_H
