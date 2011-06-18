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

#include "WarEditWindow.h"
#include <QMessageBox>
#include <QFileDialog>
#include <QTextStream>
#include <QDebug>
#include "ReferenceEditDialog.h"
#include <WargearProfile.h>
#include "WargearProfileEditDialog.h"
#include <WarPage.h>
#include "WarPageViewerDialog.h"

void WarEditWindow::onMenuNewRace()
{
    bool didOpenGame = false;
    if(askSaveOpenGame() && askSaveOpenRace())
    {
        closeRace();
        
        if(!m_game)
        {
            QMessageBox::information(this, "Open Game",
                "Please select a Game to use for the new Race");
            
            int status = doOpenGame();
            if(status == ActionFailed || status == ActionCancelled)
            {
                opmode(NoMode);
                enableActiveWidgets();
                return;
            }
            
            populateGame();
            populateGameRuleList();
            didOpenGame = true;
        }
        
        opmode(RaceMode);
        m_race = new Race(m_game);
        m_race->name("New Race");
        m_race->id("new_race");
        m_race->book("New Race Codex");
        m_race->edition("5");
        m_race->version("1.0-alpha");
        
        setWindowFilePath("New Race");
        setFileHasChanges(true);
        populateRace();
        enableActiveWidgets();
        
        if(didOpenGame)
            onGameRuleSelected(-1);
        
        onRaceRuleSelected(-1);
        onRaceUnitSelected(-1);
        onRaceWargearSelected(-1);
        
        race_gameEdit->setText(m_game->name());
    }
}

void WarEditWindow::closeRace()
{
    if(m_race)
        delete m_race;
    
    if(m_raceFile)
        delete m_raceFile;
    
    m_race = NULL;
    m_raceFile = NULL;
    m_race_rule = NULL;
    m_race_unit = NULL;
    m_race_wargear = NULL;
    
    populateRace();
    onRaceUnitSelected(-1);
    onRaceWargearSelected(-1);
    onRaceRuleSelected(-1);
}

void WarEditWindow::populateRaceLists()
{
    race_ruleList->clear();
    race_unitList->clear();
    race_wargearList->clear();
    
    int len = m_race_rules.length();
    for(int i = 0; i < len; i++)
        race_ruleList->addItem(m_race_rules[i]->name());
    
    len = m_race_units.length();
    for(int i = 0; i < len; i++)
        race_unitList->addItem(m_race_units[i]->name());
    
    len = m_race_wargears.length();
    for(int i = 0; i < len; i++)
        race_wargearList->addItem(m_race_wargears[i]->name());
}

void WarEditWindow::populateRace()
{
    if(m_race)
    {
        race_idEdit->setText(m_race->id());
        race_nameEdit->setText(m_race->name());
        race_bookEdit->setText(m_race->book());
        race_editionEdit->setText(m_race->edition());
        race_versionEdit->setText(m_race->version());
        race_gameEdit->setText(m_game->name());
    }
    else
    {
        race_idEdit->clear();
        race_nameEdit->clear();
        race_bookEdit->clear();
        race_editionEdit->clear();
        race_versionEdit->clear();
        race_gameEdit->clear();
        race_ruleList->clear();
        race_unitList->clear();
        race_wargearList->clear();
    }
    
    raceSaveBox->setEnabled(false);
}


void WarEditWindow::doMenuOpenRace()
{
    bool loadedGame = (m_game == NULL);
    int status = doOpenRace();
    if(status == ActionOk)
    {
        setWindowFilePath(strippedFileName(m_raceFile->fileName()));
        opmode(RaceMode);
        enableActiveWidgets();
        
        if(loadedGame)
        {
            populateGame();
            onGameRuleSelected(-1);
            populateGameRuleList();
        }
        
        populateRace();
        populateRaceLists();
        onRaceRuleSelected(-1);
        onRaceUnitSelected(-1);
        onRaceWargearSelected(-1);
        raceSaveBox->setEnabled(false);
    }
    else
    {
        if(loadedGame && m_game)
            closeGame();
        else if(m_game)
            opmode(GameMode);
        else
            opmode(NoMode);
        
        enableActiveWidgets();
    }
}

void WarEditWindow::doMenuSaveRace()
{
    doSaveRace(false);
}

void WarEditWindow::doMenuSaveRaceAs()
{
    doSaveRace(true);
}

void WarEditWindow::onMenuPreviewRaceClicked()
{
    WarPage page(*m_race);
    WarPageViewerDialog *dia = new WarPageViewerDialog(this, page);
    dia->exec();
    delete dia;
}

int WarEditWindow::doOpenRace()
{
    if(askSaveOpenGame() && askSaveOpenRace())
    {
        QString filter = "Race Files (*.race)";
        QString path = QFileDialog::getOpenFileName(this, "Open Race",
            m_pwd.path(), filter, &filter);
        
        if(path.isNull())
            return ActionCancelled;
        
        closeRace();
        
        m_raceFile = new QFile(path);
        if(!m_raceFile->open(QIODevice::ReadOnly))
        {
            QMessageBox::warning(this, "Open Error", "Could not open file " +
                m_raceFile->fileName() + ".\n\nDetails: " + m_raceFile->errorString());
            
            closeRace();
            return ActionFailed;
        }
        
        setPwd(path);
        
        QDomDocument doc;
        if(!openXml(doc, m_raceFile))
        {
            closeRace();
            return ActionFailed;
        }
        
        try
        {
            m_race = new Race(doc);
        }
        catch(XmlParseException e)
        {
            QMessageBox::warning(this, "Parse Error", "Could not parse file " +
                m_raceFile->fileName() + ".\n[" + e.elementName() + "@" +
                QString::number(e.line()) + "]: " + e.description());
            
            m_raceFile->close();
            closeRace();
            return ActionFailed;
        }
        
        m_raceFile->close();
        
        if(!m_game)
        {
            int status = doOpenGame(m_race->parsedGameId());
            if(status != ActionOk)
            {
                closeRace();
                return status;
            }
        }
        
        if(m_game->id() != m_race->parsedGameId())
        {
            int ret = QMessageBox::warning(this, "Incorrect Game ID",
                "The Race could not be loaded because the Race references a game that is not currently open.");
            
            closeRace();
            if(opmode() != GameMode)
            {
                delete m_game;
                m_gameFile = NULL;
            }
            
            return ActionFailed;
        }
        
        try
        {
            m_race->resolveReferences(*m_game);
        }
        catch(UnresolvedReferenceException e)
        {
            QMessageBox::warning(this, "Unresolved Reference",
                "The race could not be loaded because it has an unresolved reference. This can be caused by an old, incomplete, or incorrect game file.\n\nDetails: "
                + e.type() + "." + e.id() + " : " + e.name());
            
            closeRace();
            if(opmode() != GameMode)
                closeGame();
            
            return ActionFailed;
        }
        
        m_race_rules = m_race->rules();
        m_race_units = m_race->units();
        m_race_wargears = m_race->wargears();
        m_all_wargears = m_race_wargears + m_game->baseWargears();
        
        qSort(m_race_rules.begin(), m_race_rules.end(), compareRulePtr);
        qSort(m_race_units.begin(), m_race_units.end(), compareUnit);
        qSort(m_race_wargears.begin(), m_race_wargears.end(), compareWargear);
        qSort(m_all_wargears.begin(), m_all_wargears.end(), compareWargear);
        
        return ActionOk;
    }
    
    return ActionCancelled;
}



void WarEditWindow::onRaceRuleSelected(int index)
{
    bool ruleFieldsEnabled = false;
    Rule r;
    if(index >= 0)
    {
        m_race_rule = m_race_rules[index];
        r = *m_race_rule;
        ruleFieldsEnabled = true;
        
        if(opmode() == RaceMode)
            race_ruleRemoveButton->setEnabled(true);
    }
    else
    {
        m_race_rule = NULL;
        race_ruleRemoveButton->setEnabled(false);
    }
    
    race_rule_idEdit->setText(r.id());
    race_rule_nameEdit->setText(r.name());
    race_rule_pageEdit->setText(r.page());
    race_rule_briefEdit->setText(r.brief());
    race_rule_fullEdit->setPlainText(r.description());
    
    if(ruleFieldsEnabled != race_rule_idEdit->isEnabled())
    {
        race_rule_idEdit->setEnabled(ruleFieldsEnabled);
        race_rule_nameEdit->setEnabled(ruleFieldsEnabled);
        race_rule_pageEdit->setEnabled(ruleFieldsEnabled);
        race_rule_briefEdit->setEnabled(ruleFieldsEnabled);
        race_rule_fullEdit->setEnabled(ruleFieldsEnabled);
    }
    
    race_ruleSaveBox->setEnabled(false);
}

void WarEditWindow::onRaceUnitSelected(int index, bool reload)
{
    bool unitFieldsEnabled = false;
    bool hasSelection = false;
    Unit u(*m_race);
    if(index >= 0)
    {
        m_race_unit = m_race_units[index];
        u = *m_race_unit;
        unitFieldsEnabled = true;
        hasSelection = true;
        
        if(reload)
        {
            m_race_unit_rules = m_race_unit->ruleRefs();
            m_race_unit_wargears = m_race_unit->wargearRefs();
            race_unit_wargearList->clear();
            race_unit_ruleList->clear();
            
            int len = m_race_unit_rules.length();
            for(int i = 0; i < len; i++)
                race_unit_ruleList->addItem(m_race_unit_rules[i]->name());
            
            len = m_race_unit_wargears.length();
            for(int i = 0; i < len; i++)
                race_unit_wargearList->addItem(m_race_unit_wargears[i]->name());
        }  
    }
    else
    {
        m_race_unit = NULL;
        m_race_unit_rules.clear();
        m_race_unit_wargears.clear();
        race_unit_ruleList->clear();
        race_unit_wargearList->clear();
    }
    
    race_unit_idEdit->setText(u.id());
    race_unit_nameEdit->setText(u.name());
    race_unit_pageEdit->setText(u.page());
    race_unit_wsEdit->setText(u.profile().weaponSkill());
    race_unit_bsEdit->setText(u.profile().ballisticSkill());
    race_unit_sEdit->setText(u.profile().strength());
    race_unit_tEdit->setText(u.profile().toughness());
    race_unit_wEdit->setText(u.profile().wounds());
    race_unit_iEdit->setText(u.profile().initiative());
    race_unit_aEdit->setText(u.profile().attacks());
    race_unit_ldEdit->setText(u.profile().leadership());
    race_unit_svEdit->setText(u.profile().armourSave());
    race_unit_isvEdit->setText(u.profile().invulnerableSave());
    race_unit_afEdit->setText(u.profile().frontArmour());
    race_unit_asEdit->setText(u.profile().sideArmour());
    race_unit_arEdit->setText(u.profile().rearArmour());
    
    race_unitSaveBox->setEnabled(false);
    race_unit_wargearEditButton->setEnabled(false);
    race_unit_wargearRemoveButton->setEnabled(false);
    race_unit_ruleEditButton->setEnabled(false);
    race_unit_ruleRemoveButton->setEnabled(false);
    
    if(unitFieldsEnabled != race_unit_idEdit->isEnabled())
    {
        race_unit_idEdit->setEnabled(unitFieldsEnabled);
        race_unit_nameEdit->setEnabled(unitFieldsEnabled);
        race_unit_pageEdit->setEnabled(unitFieldsEnabled);
        race_unit_wsEdit->setEnabled(unitFieldsEnabled);
        race_unit_bsEdit->setEnabled(unitFieldsEnabled);
        race_unit_sEdit->setEnabled(unitFieldsEnabled);
        race_unit_tEdit->setEnabled(unitFieldsEnabled);
        race_unit_wEdit->setEnabled(unitFieldsEnabled);
        race_unit_aEdit->setEnabled(unitFieldsEnabled);
        race_unit_iEdit->setEnabled(unitFieldsEnabled);
        race_unit_ldEdit->setEnabled(unitFieldsEnabled);
        race_unit_svEdit->setEnabled(unitFieldsEnabled);
        race_unit_isvEdit->setEnabled(unitFieldsEnabled);
        race_unit_afEdit->setEnabled(unitFieldsEnabled);
        race_unit_asEdit->setEnabled(unitFieldsEnabled);
        race_unit_arEdit->setEnabled(unitFieldsEnabled);
        race_unit_ruleList->setEnabled(unitFieldsEnabled);
        race_unit_wargearList->setEnabled(unitFieldsEnabled);
        
        race_unit_ruleAddButton->setEnabled(opmode() == RaceMode && hasSelection);
        race_unit_wargearAddButton->setEnabled(opmode() == RaceMode && hasSelection);
        race_unitRemoveButton->setEnabled(opmode() == RaceMode && hasSelection);
    }
}

void WarEditWindow::onRaceWargearSelected(int index, bool reload)
{
    bool wargearFieldsEnabled = false;
    bool hasSelection = false;
    Wargear w(*m_race);
    if(index >= 0)
    {
        m_race_wargear = m_race_wargears[index];
        w = *m_race_wargear;
        wargearFieldsEnabled = true;
        hasSelection = true;
        
        if(reload)
        {
            m_race_wargear_profiles = m_race_wargear->profiles();
            race_wargear_profileList->clear();
            int len = m_race_wargear_profiles.length();
            for(int i = 0; i < len; i++)
                race_wargear_profileList->addItem(m_race_wargear_profiles[i]->name());
        }
    }
    else
    {
        race_wargear_profileList->clear();
        m_race_wargear = NULL;
        m_race_wargear_profiles.clear();
    }
    
    race_wargear_idEdit->setText(w.id());
    race_wargear_briefEdit->setText(w.brief());
    race_wargear_pageEdit->setText(w.page());
    race_wargear_nameEdit->setText(w.name());
    race_wargear_fullEdit->setPlainText(w.description());
    
    race_wargearSaveBox->setEnabled(false);
    race_wargear_profileRemoveButton->setEnabled(false);
    race_wargear_profileEditButton->setEnabled(false);
    
    if(wargearFieldsEnabled != race_wargear_idEdit->isEnabled())
    {
        race_wargear_idEdit->setEnabled(wargearFieldsEnabled);
        race_wargear_nameEdit->setEnabled(wargearFieldsEnabled);
        race_wargear_pageEdit->setEnabled(wargearFieldsEnabled);
        race_wargear_briefEdit->setEnabled(wargearFieldsEnabled);
        race_wargear_fullEdit->setEnabled(wargearFieldsEnabled);
        race_wargear_profileList->setEnabled(wargearFieldsEnabled);
        
        race_wargear_profileNewButton->setEnabled(opmode() == RaceMode && hasSelection);
        race_wargearRemoveButton->setEnabled(opmode() == RaceMode && hasSelection);
    }
}

void WarEditWindow::onRaceChanged()
{
    raceSaveBox->setEnabled(true);
}

void WarEditWindow::onRaceRuleChanged()
{
    race_ruleSaveBox->setEnabled(true);
    setEnabledList(race_ruleList, race_ruleNewButton, race_ruleRemoveButton,
                   false);
}

void WarEditWindow::onRaceUnitChanged()
{
    race_unitSaveBox->setEnabled(true);
    setEnabledList(race_unitList, race_unitNewButton, race_unitRemoveButton,
        false);
}

void WarEditWindow::onRaceWargearChanged()
{
    race_wargearSaveBox->setEnabled(true);
    setEnabledList(race_wargearList, race_wargearNewButton,
                   race_wargearRemoveButton, false);
}

void WarEditWindow::doCommitOrRollbackRace(QAbstractButton* button)
{
    if(raceSaveBox->buttonRole(button) == QDialogButtonBox::ApplyRole)
    {
        if(validateRace())
        {
            m_race->id(race_idEdit->text());
            m_race->name(race_nameEdit->text());
            m_race->book(race_bookEdit->text());
            m_race->edition(race_editionEdit->text());
            m_race->version(race_versionEdit->text());
            setFileHasChanges(true);
            raceSaveBox->setEnabled(false);
        }
    }
    else
    {
        populateRace();
        raceSaveBox->setEnabled(false);
    }
}

void WarEditWindow::doCommitOrRollbackRaceUnit(QAbstractButton* button)
{
    if(race_unitSaveBox->buttonRole(button) == QDialogButtonBox::ApplyRole)
    {
        if(validateRaceUnit())
        {
            if(m_race_unit->id() != race_unit_idEdit->text())
            {
                m_race_unit = m_race->resetUnitId(m_race_unit->id(),
                                                  race_unit_idEdit->text());
                m_race_units[race_unitList->currentRow()] = m_race_unit;
            }
            
            m_race_unit->name(race_unit_nameEdit->text());
            m_race_unit->page(race_unit_pageEdit->text());
            m_race_unit->profile().weaponSkill(race_unit_wsEdit->text());
            m_race_unit->profile().ballisticSkill(race_unit_bsEdit->text());
            m_race_unit->profile().strength(race_unit_sEdit->text());
            m_race_unit->profile().toughness(race_unit_tEdit->text());
            m_race_unit->profile().wounds(race_unit_wEdit->text());
            m_race_unit->profile().initiative(race_unit_iEdit->text());
            m_race_unit->profile().attacks(race_unit_aEdit->text());
            m_race_unit->profile().leadership(race_unit_ldEdit->text());
            m_race_unit->profile().armourSave(race_unit_svEdit->text());
            m_race_unit->profile().invulnerableSave(race_unit_isvEdit->text());
            m_race_unit->profile().frontArmour(race_unit_afEdit->text());
            m_race_unit->profile().sideArmour(race_unit_asEdit->text());
            m_race_unit->profile().rearArmour(race_unit_arEdit->text());
            race_unitList->currentItem()->setText(m_race_unit->name());
            
            setFileHasChanges(true);
        }
    }
    else
        onRaceUnitSelected(race_unitList->currentRow(), false);
    
    race_unitSaveBox->setEnabled(false);
    setEnabledList(race_unitList, race_unitNewButton, race_unitRemoveButton,
            true);
}

void WarEditWindow::doCommitOrRollbackRaceWargear(QAbstractButton* button)
{
    if(race_wargearSaveBox->buttonRole(button) == QDialogButtonBox::ApplyRole)
    {
        if(validateRaceWargear())
        {
            if(m_race_wargear->id() != race_wargear_idEdit->text())
            {
                qDebug() << "before reset";
                m_race_wargear = m_race->resetWargearId(m_race_wargear->id(),
                    race_wargear_idEdit->text());
                qDebug() << "after reset: " << (m_race_wargear != 0);
                m_race_wargears[race_wargearList->currentRow()] = m_race_wargear;
            }
            
            m_race_wargear->name(race_wargear_nameEdit->text());
            m_race_wargear->brief(race_wargear_briefEdit->text());
            m_race_wargear->page(race_wargear_pageEdit->text());
            m_race_wargear->description(race_wargear_fullEdit->toPlainText());
            race_wargearList->currentItem()->setText(m_race_wargear->name());
            
            setFileHasChanges(true);
        }
    }
    else
        onRaceWargearSelected(race_wargearList->currentRow(), false);
    
    race_wargearSaveBox->setEnabled(false);
    setEnabledList(race_wargearList, race_wargearNewButton,
                   race_wargearRemoveButton, true);
}

void WarEditWindow::doCommitOrRollbackRaceRule(QAbstractButton* button)
{
    if(race_ruleSaveBox->buttonRole(button) == QDialogButtonBox::ApplyRole)
    {
        if(validateRaceRule())
        {
            if(m_race_rule->id() != race_rule_idEdit->text())
            {
                m_race_rule = m_race->resetRuleId(m_race_rule->id(),
                                                  race_rule_idEdit->text());
                m_race_rules[race_ruleList->currentRow()] = m_race_rule;
            }
            m_race_rule->name(race_rule_nameEdit->text());
            m_race_rule->page(race_rule_pageEdit->text());
            m_race_rule->brief(race_rule_briefEdit->text());
            m_race_rule->description(race_rule_fullEdit->toPlainText());
            race_ruleList->currentItem()->setText(m_race_rule->name());
            
            setFileHasChanges(true);
        }
    }
    else
        onRaceRuleSelected(race_ruleList->currentRow());
    
    race_ruleSaveBox->setEnabled(false);
    setEnabledList(race_ruleList, race_ruleNewButton, race_ruleRemoveButton,
                   true);
    
}

bool WarEditWindow::validateRace(bool show)
{
    trim(race_idEdit);
    trim(race_nameEdit);
    trim(race_bookEdit);
    trim(race_editionEdit);
    trim(race_versionEdit);
    
    QString fault;
    if(race_idEdit->text().isEmpty())
        fault = "ID";
    else if(race_nameEdit->text().isEmpty())
        fault = "Name";
    else if(race_bookEdit->text().isEmpty())
        fault = "Book";
    else if(race_editionEdit->text().isEmpty())
        fault = "Edition";
    else if(race_versionEdit->text().isEmpty())
        fault = "Version";
    
    if(!fault.isEmpty())
    {
        if(show)
        {
            QMessageBox::warning(this, "Race Validation Error", "Race field " +
                fault + " cannot be empty");
        }
        
        return false;
    }
    
    return true;
}

bool WarEditWindow::validateRaceRule(bool show)
{
    QString fault;
    trim(race_rule_idEdit);
    trim(race_rule_nameEdit);
    trim(race_rule_pageEdit);
    trim(race_rule_briefEdit);
    trim(race_rule_fullEdit);
    
    if(race_rule_idEdit->text().isEmpty())
        fault = "ID";
    else if(race_rule_nameEdit->text().isEmpty())
        fault = "Name";
    else if(race_rule_pageEdit->text().isEmpty())
        fault = "Page";
    else if(race_rule_briefEdit->text().isEmpty())
        fault = "Brief";
    
    if(!fault.isEmpty())
    {
        if(show)
        {
            QMessageBox::warning(this, "Rule Validation Error",
                "Rule field " + fault + " cannot be empty");
        }
        
        return false;
    }
    
    Rule *r = m_game->getRule(race_rule_idEdit->text());
    if(!r)
        r = m_race->getRule(race_rule_idEdit->text());
    
    if(r && r != m_race_rule)
    {
        if(show)
        {
            QMessageBox::warning(this, "Rule Validation Error",
                "The Rule ID you entered is not unique. Please choose a unique Rule ID.");
        }
        
        return false;
    }
    
    return true;
}

bool WarEditWindow::validateRaceUnit(bool show)
{
    trim(race_unit_idEdit);
    trim(race_unit_nameEdit);
    trim(race_unit_pageEdit);
    trim(race_unit_wsEdit);
    trim(race_unit_bsEdit);
    trim(race_unit_sEdit);
    trim(race_unit_tEdit);
    trim(race_unit_iEdit);
    trim(race_unit_aEdit);
    trim(race_unit_ldEdit);
    trim(race_unit_svEdit);
    trim(race_unit_isvEdit);
    trim(race_unit_afEdit);
    trim(race_unit_asEdit);
    trim(race_unit_arEdit);
    
    QString fault;
    if(race_unit_idEdit->text().isEmpty())
        fault = "ID";
    else if(race_unit_nameEdit->text().isEmpty())
        fault = "Name";
    else if(race_unit_pageEdit->text().isEmpty())
        fault = "Page";
    
    if(!fault.isEmpty())
    {
        if(show)
        {
            QMessageBox::warning(this, "Unit Validation Error",
                                 "Unit field " + fault + 
                                 " cannot be empty");
        }
        
        return false;
    }
    
    Unit *u = m_race->getUnit(race_unit_idEdit->text());
    if(u && u != m_race_unit)
    {
        if(show)
        {
            QMessageBox::warning(this, "Unit Validation Error",
                "The Unit ID you entered is not unique. Please choode a unique Unit ID.");
        }
        
        return false;
    }
    
    return true;
}

bool WarEditWindow::validateRaceWargear(bool show)
{
    trim(race_wargear_idEdit);
    trim(race_wargear_nameEdit);
    trim(race_wargear_pageEdit);
    trim(race_wargear_briefEdit);
    trim(race_wargear_fullEdit);
    
    QString fault;
    if(race_wargear_idEdit->text().isEmpty())
        fault = "ID";
    else if(race_wargear_nameEdit->text().isEmpty())
        fault = "Name";
    else if(race_wargear_pageEdit->text().isEmpty())
        fault = "Page";
    
    if(!fault.isEmpty())
    {
        if(show)
        {
            QMessageBox::warning(this, "Wargear Validation Error",
                                 "Wargear field " + fault +
                                 " cannot be empty");
        }
        
        return false;
    }
    
    Wargear *wg = m_race->getWargear(race_wargear_idEdit->text());
    if(wg && wg != m_race_wargear)
    {
        if(show)
        {
            QMessageBox::warning(this, "Wargear Validation Error",
                "The Wargear ID you entered is not unique. Please choose a unique Wargear ID.");
        }
        
        return false;
    }
    
    
    return true;
}

bool WarEditWindow::askSaveOpenRace()
{
    if(fileHasChanges() && opmode() == RaceMode)
    {
        int ret = QMessageBox::question(this, "Save Race?",
            "The current race has unsaved changes. Do you want to save them?",
            QMessageBox::No, QMessageBox::Cancel, QMessageBox::Yes);
        
        if(ret == QMessageBox::Yes)
        {
            if(!doSaveRace(false))
                return false;
            
            return true;
        }
        else if(ret == QMessageBox::No)
            return true;
        else
            return false;
    }
    
    return true;
}

bool WarEditWindow::doSaveRace(bool override)
{
    if(!canSaveRace())
        return false;
    
    if(!m_raceFile || override)
    {
        QString filter = "Race Files (*.race)";
        QString path = QFileDialog::getSaveFileName(this, "Save Race",
            m_pwd.path(), filter, &filter);
        
        if(path.isNull()) // user cancelled
            return false;
        
        if(m_raceFile)
            delete m_raceFile;
        
        m_raceFile = new QFile(path);
        setPwd(path);
    }
    
    QDomDocument doc;
    QDomElement worthless;
    try
    {
        m_race->toXml(doc, worthless);
    }
    catch(ValidationException e)
    {
        QMessageBox::warning(this, "Save Error", "An error occured while saving the game.\n" 
            + e.object() + "." + e.field() + ": " + e.reason());
        
        return false;
    }
    
    if(!m_raceFile->open(QIODevice::WriteOnly))
    {
        QMessageBox::warning(this, "Save Error", "Could save to file " +
            m_raceFile->fileName() + ": " + m_raceFile->errorString());
        
        delete m_raceFile;
        m_raceFile = NULL;
        
        setFileHasChanges(true);
        
        return false;
    }
    
    QTextStream ts(m_raceFile);
    ts << doc.toString(4);
    
    m_raceFile->close();
    
    setWindowFilePath(strippedFileName(m_raceFile->fileName()));
    setFileHasChanges(false);
    
    return true;
}

bool WarEditWindow::canSaveRace()
{
    QString type;
    if(raceSaveBox->isEnabled())
        type = "fields";
    else if(race_ruleSaveBox->isEnabled())
        type = "Rule";
    else if(race_unitSaveBox->isEnabled())
        type = "Unit";
    else if(race_wargearSaveBox->isEnabled())
        type = "Wargear";
    
    if(!type.isEmpty())
    {
        QMessageBox::warning(this, "Race Save Error", "The Race contains changes to the current "
            + type + " that must be applied and discarded before saving can occurr");
        
        return false;
    }
    
    return true;
}

void WarEditWindow::doNewRaceRule()
{
    QString id = genUniqueRuleId(*m_race, m_race_rules.length());
    Rule r;
    r.id(id);
    r.name("New Rule");
    r.page("N/A");
    r.brief("A Rule");
    
    m_race->addRule(r);
    m_race_rules.append(m_race->getRule(id));
    race_ruleList->addItem(r.name());
    race_ruleList->setCurrentRow(m_race_rules.length() - 1);
    setFileHasChanges(true);
    race_rule_idEdit->setFocus();
    race_rule_idEdit->selectAll();
}



void WarEditWindow::doNewRaceWargear()
{
    QString id;
    bool done = false;
    int diff = 1, start = m_race_wargears.length();
    while(!done)
    {
        id = "wargear_" + QString::number(diff + start);
        if(!m_race->hasWargear(id))
            done = true;
        else
            diff++;
    }
    
    Wargear w(*m_race);
    w.id(id);
    w.name("New Wargear");
    w.page("N/A");
    Wargear *add = m_race->addWargear(w);
    
    m_race_wargears.append(add);
    m_all_wargears.append(add);
    race_wargearList->addItem(w.name());
    race_wargearList->setCurrentRow(m_race_wargears.length() - 1);
    setFileHasChanges(true);
    race_wargear_idEdit->setFocus();
    race_wargear_idEdit->selectAll();
}

void WarEditWindow::doNewRaceUnit()
{
    QString id;
    bool done = false;
    int diff = 1, start = m_race_units.length();
    while(!done)
    {
        id = "unit_" + QString::number(diff + start);
        if(!m_race->getUnit(id))
            done = true;
        else
            diff++;
    }
    
    Unit u(*m_race);
    u.id(id);
    u.name("New Unit");
    u.page("N/A");
    m_race->addUnit(u);
    m_race_units.append(m_race->getUnit(id));
    race_unitList->addItem(u.name());
    race_unitList->setCurrentRow(m_race_units.length() - 1);
    setFileHasChanges(true);
    race_unit_idEdit->setFocus();
    race_unit_idEdit->selectAll();
}



void WarEditWindow::doRemoveRaceRule()
{
    int index = race_ruleList->currentRow();
    if(index >= 0)
    {
        delete race_ruleList->takeItem(index);
        Rule *rule = m_race_rules.takeAt(index);
        m_race->removeRule(*rule);
        setFileHasChanges(true);
    }
}

void WarEditWindow::doRemoveRaceUnit()
{
    int index = race_unitList->currentRow();
    if(index >= 0)
    {
        delete race_unitList->takeItem(index);
        Unit *unit = m_race_units.takeAt(index);
        m_race->removeUnit(*unit);
        setFileHasChanges(true);
    }
}

void WarEditWindow::doRemoveRaceWargear()
{
    int index = race_wargearList->currentRow();
    if(index >= 0)
    {
        delete race_wargearList->takeItem(index);
        Wargear *w = m_race_wargears.takeAt(index);
        m_all_wargears.removeOne(w);
        m_race->removeWargear(*w);
        setFileHasChanges(true);
    }
}

void WarEditWindow::onRaceUnitWargearSelected(int index)
{
    bool buttonsEnabled = (index >= 0 ? true : false);
    race_unit_wargearEditButton->setEnabled(buttonsEnabled);
    race_unit_wargearRemoveButton->setEnabled(buttonsEnabled);
}

void WarEditWindow::onRaceUnitRuleSelected(int index)
{
    bool buttonsEnabled = (index >= 0 ? true : false);
    race_unit_ruleEditButton->setEnabled(buttonsEnabled);
    race_unit_ruleRemoveButton->setEnabled(buttonsEnabled);
}


void WarEditWindow::onRaceWargearProfileSelected(int index)
{
    bool buttonsEnabled = (index >= 0 ? true : false);
    race_wargear_profileEditButton->setEnabled(buttonsEnabled);
    race_wargear_profileRemoveButton->setEnabled(buttonsEnabled);
}

void WarEditWindow::doNewRaceUnitRule()
{
    RuleRef ref = ReferenceEditDialog::getRuleRef(this, m_game_rules,
        m_race_rules, "Add Rule to Unit");
    
    if(!ref.isNull())
    {
        RuleRef *newRef = m_race_unit->addRuleRef(ref);
        if(newRef)
        {
            m_race_unit_rules.append(newRef);
            race_unit_ruleList->addItem(ref.name());
            setFileHasChanges(true);
        }
        else
        {
            QMessageBox::warning(this, "Add Rule to Unit Error",
                "You attempted to add a duplicate rule to the unit. Unit rules must be unique.");
        }
    }
}

void WarEditWindow::doEditRaceUnitRule()
{
    RuleRef *ref = m_race_unit_rules[race_unit_ruleList->currentRow()];
    ReferenceEditDialog::getRuleRef(this, m_game_rules, m_race_rules,
        "Edit Unit Rule", ref);
    
    race_unit_ruleList->currentItem()->setText(ref->name());
    setFileHasChanges(true);
}

void WarEditWindow::doRemoveRaceUnitRule()
{
    int index = race_unit_ruleList->currentRow();
    RuleRef *ref = m_race_unit_rules.takeAt(index);
    delete race_unit_ruleList->takeItem(index);
    m_race_unit->removeRuleRef(*ref);
    setFileHasChanges(true);
}

void WarEditWindow::doNewRaceUnitWargear()
{
    WargearRef ref = ReferenceEditDialog::getWargearRef(this, m_all_wargears,
        "Add Wargear to Unit");
    
    if(!ref.isNull())
    {
        WargearRef *newRef = m_race_unit->addWargearRef(ref);
        if(newRef)
        {
            m_race_unit_wargears.append(newRef);
            race_unit_wargearList->addItem(ref.name());
            setFileHasChanges(true);
        }
        else
        {
            QMessageBox::warning(this, "Add Wargear to Unit Error",
                "You attempted to add a duplicate wargear to the unit. Unit wargears must be unique.");
        }
    }
}

void WarEditWindow::doEditRaceUnitWargear()
{
    WargearRef *ref = m_race_unit_wargears[race_unit_wargearList->currentRow()];
    ReferenceEditDialog::getWargearRef(this, m_all_wargears,
        "Edit Unit Wargear", ref);
    
    race_unit_wargearList->currentItem()->setText(ref->name());
    setFileHasChanges(true);
}

void WarEditWindow::doRemoveRaceUnitWargear()
{
    int index = race_unit_wargearList->currentRow();
    WargearRef *ref = m_race_unit_wargears.takeAt(index);
    delete race_unit_wargearList->takeItem(index);
    m_race_unit->removeWargearRef(*ref);
    setFileHasChanges(true);
}

void WarEditWindow::doNewRaceWargearProfile()
{
    WargearProfile profile = WargearProfileEditDialog::getWargearProfile(
        this, m_race_wargear, m_game_rules, m_race_rules);
    
    if(!profile.isNull())
    {
        WargearProfile *wp = m_race_wargear->addProfile(profile);
        if(wp)
        {
            m_race_wargear_profiles.append(wp);
            race_wargear_profileList->addItem(wp->name());
            setFileHasChanges(true);
        }
        else
        {
            QMessageBox::warning(this, "Add Wargear Profile",
                "You attempted to add a duplicate wargear profile. Profiles must be unique.");
        }
    }
}

void WarEditWindow::doEditRaceWargearProfile()
{
    int index = race_wargear_profileList->currentRow();
    WargearProfile *profile = m_race_wargear_profiles[index];
    WargearProfileEditDialog::getWargearProfile(
        this, m_race_wargear, m_game_rules, m_race_rules, profile);
    
    race_wargear_profileList->currentItem()->setText(profile->name());
    setFileHasChanges(true);
}

void WarEditWindow::doRemoveRaceWargearProfile()
{
    int index = race_wargear_profileList->currentRow();
    WargearProfile *profile = m_race_wargear_profiles.takeAt(index);
    m_race_wargear->removeProfile(*profile);
    delete race_wargear_profileList->takeItem(index);
    
    setFileHasChanges(true);
}

void WarEditWindow::doShowUnitContextMenu(const QPoint& p)
{
    //qDebug() << m_race_unit->id();
    //int index = race_unitList->indexAt(p).row();
    
    if(m_race_unit) //index >= 0)
    {
        QPoint globalPoint = race_unitList->mapToGlobal(p);
        QMenu menu;
        
        QIcon copyIcon;
        copyIcon.addFile(":/icons/edit-copy.png");
        QAction *copyAction = new QAction(copyIcon, "Copy Unit", &menu);
        menu.addAction(copyAction);
        
        QAction *action = menu.exec(globalPoint);
        if(action == copyAction)
        {
            Unit u(*m_race_unit);
            u.id(genUniqueUnitId());
            u.name(u.name() + " Copy");
            m_race_units.append(m_race->addUnit(u));
            race_unitList->addItem(u.name());
            race_unitList->setCurrentRow(m_race_units.length() - 1);
            setFileHasChanges(true);
        }
    }
}
