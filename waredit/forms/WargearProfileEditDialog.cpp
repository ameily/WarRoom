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


#include "WargearProfileEditDialog.h"
#include "WargearProfileEditDialog.moc"
#include "ReferenceEditDialog.h"
#include <QMessageBox>
#include <QDebug>

WargearProfileEditDialog::WargearProfileEditDialog(QWidget* parent,
    const Wargear* wargear, QList< Rule* >& gameRules, QList< Rule* >& raceRules,
    WargearProfile *edit) : QDialog(parent), m_profile(*wargear)
{
    setupUi(this);
    m_game_rules = gameRules;
    m_race_rules = raceRules;
    
    if(edit)
        m_profile = *edit;
    
    wargearEdit->setText(wargear->name());
    initDialog();
}

WargearProfile& WargearProfileEditDialog::profile()
{
    return m_profile;
}


WargearProfileEditDialog::~WargearProfileEditDialog()
{
    //if(m_deleteProfile) delete m_profile;
}

void WargearProfileEditDialog::initDialog()
{
    connect(saveBox, SIGNAL(accepted()), SLOT(validate()));
    connect(saveBox, SIGNAL(rejected()), SLOT(reject()));
    connect(ruleList, SIGNAL(currentRowChanged(int)), SLOT(onRuleSelected(int)));
    connect(addButton, SIGNAL(clicked()), SLOT(doAddRuleRef()));
    connect(editButton, SIGNAL(clicked()), SLOT(doEditRuleRef()));
    connect(removeButton, SIGNAL(clicked()), SLOT(doRemoveRuleRef()));
    
    nameEdit->setText(m_profile.name());
    apEdit->setText(m_profile.armourPenetration());
    rangeEdit->setText(m_profile.range());
    strengthEdit->setText(m_profile.strength());
    m_profile_rules = m_profile.ruleRefs();
    
    int len = m_profile_rules.length();
    for(int i = 0; i < len; i++)
        ruleList->addItem(m_profile_rules[i]->name());
    
    onRuleSelected(-1);
}

void WargearProfileEditDialog::validate()
{
    QString fault;
    nameEdit->setText(nameEdit->text().trimmed());
    rangeEdit->setText(rangeEdit->text().trimmed());
    apEdit->setText(apEdit->text().trimmed());
    strengthEdit->setText(strengthEdit->text().trimmed());
    
    if(nameEdit->text().isEmpty())
        fault = "Name";
    else if(rangeEdit->text().isEmpty())
        fault = "Range";
    else if(apEdit->text().isEmpty())
        fault = "AP";
    else if(strengthEdit->text().isEmpty())
        fault = "Strength";
    
    if(!fault.isEmpty())
    {
        QMessageBox::warning(this, "Validation Error",
                             "The field " + fault + " cannot be empty.");
    }
    else
    {
        m_profile.name(nameEdit->text());
        m_profile.range(rangeEdit->text());
        m_profile.armourPenetration(apEdit->text());
        m_profile.strength(strengthEdit->text());
        emit accept();
    }
}

void WargearProfileEditDialog::doAddRuleRef()
{
    RuleRef ref = ReferenceEditDialog::getRuleRef(this, m_game_rules,
        m_race_rules, "Add Rule to Profile");
    
    if(!ref.isNull())
    {
        RuleRef *newRef = m_profile.addRuleRef(ref);
        if(newRef)
        {
            m_profile_rules.append(newRef);
            ruleList->addItem(ref.name());
            
        }
        else
        {
            QMessageBox::warning(this, "Add Rule to Profile Error",
                "You attempted to add a duplicate rule to the profile. Profile rules must be unique.");
        }
    }
}

void WargearProfileEditDialog::doEditRuleRef()
{
    int index = ruleList->currentRow();
    if(index >= 0)
    {
        RuleRef *ref = m_profile_rules[index];
        ReferenceEditDialog::getRuleRef(this, m_game_rules, m_race_rules,
            "Edit Profile Rule", ref
        );
        
        ruleList->currentItem()->setText(ref->name());
    }
}

void WargearProfileEditDialog::doRemoveRuleRef()
{
    int index = ruleList->currentRow();
    if(index >= 0)
    {
        RuleRef *dref = m_profile_rules.takeAt(index);
        m_profile.removeRuleRef(*dref);
        delete ruleList->takeItem(index);
    }
}

void WargearProfileEditDialog::onRuleSelected(int index)
{
    bool val = (index >= 0 ? true : false);
    
    removeButton->setEnabled(val);
    editButton->setEnabled(val);
}

WargearProfile WargearProfileEditDialog::getWargearProfile(QWidget* parent,
    const Wargear* wargear, QList< Rule* >& gameRules, QList< Rule* >& raceRules,
    WargearProfile* out)
{
    WargearProfileEditDialog dia(parent, wargear, gameRules, raceRules, out);
    if(out)
        dia.setWindowTitle("Edit Wargear Profile");
    else
        dia.setWindowTitle("New Wargear Profile");
    
    if(dia.exec() == QDialog::Accepted)
    {
        if(out)
        {
            (*out) = dia.profile();
            return *out;
        }
        
        return dia.profile();
    }
    
    if(out)
        return *out;
    
    return WargearProfile();
}

