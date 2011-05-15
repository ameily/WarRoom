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

#include "WarEditWindow.h"
#include <QMessageBox>
#include <QFileDialog>
#include <QDebug>
#include <WarPage.h>
#include "WarPageViewerDialog.h"

void WarEditWindow::onGameChanged()
{
    gameSaveBox->setEnabled(true);
}

void WarEditWindow::doCommitOrRollbackGame(QAbstractButton* button)
{
    if(gameSaveBox->buttonRole(button) == QDialogButtonBox::ApplyRole)
    {
        if(validateGame())
        {
            m_game->id(game_idEdit->text());
            m_game->name(game_nameEdit->text());
            m_game->book(game_bookEdit->text());
            m_game->edition(game_editionEdit->text());
            m_game->version(game_versionEdit->text());
            
            gameSaveBox->setEnabled(false);
            setFileHasChanges(true);
        }
    }
    else if(gameSaveBox->buttonRole(button) == QDialogButtonBox::DestructiveRole)
    {
        populateGame();
        if(validateGame(false))
            gameSaveBox->setEnabled(false);
    }
}

bool WarEditWindow::validateGame(bool show)
{
    QString fault;
    trim(game_idEdit);
    trim(game_nameEdit);
    trim(game_bookEdit);
    trim(game_editionEdit);
    trim(game_versionEdit);
    
    if(game_idEdit->text().isEmpty())
        fault = "ID";
    else if(game_nameEdit->text().isEmpty())
        fault = "Name";
    else if(game_bookEdit->text().isEmpty())
        fault = "Book";
    else if(game_editionEdit->text().isEmpty())
        fault = "Edition";
    else if(game_versionEdit->text().isEmpty())
        fault = "Version";
    
    if(!fault.isEmpty())
    {
        if(show)
        {
            QMessageBox::warning(this, "Game Validation Error", "Game field " +
                fault + " cannot be empty");
        }
        
        return false;
    }
    
    return true;
}



void WarEditWindow::populateGame()
{
    m_isProgrammaticChange = true;
    if(m_game)
    {
        game_idEdit->setText(m_game->id());
        game_nameEdit->setText(m_game->name());
        game_bookEdit->setText(m_game->book());
        game_editionEdit->setText(m_game->edition());
        game_versionEdit->setText(m_game->version());
    }
    else
    {
        game_idEdit->clear();
        game_nameEdit->clear();
        game_bookEdit->clear();
        game_editionEdit->clear();
        game_versionEdit->clear();
        game_ruleList->clear();
    }
    m_isProgrammaticChange = false;
}

void WarEditWindow::onGameRuleSelected(int index)
{
    m_isProgrammaticChange = true;
    bool ruleFieldsEnabled = false;
    if(index >= 0)
    {
        if(opmode() == GameMode)
            game_ruleRemoveButton->setEnabled(true);
        
        ruleFieldsEnabled = true;
        Rule *rule = m_game_rules[index];
        game_rule_idEdit->setText(rule->id());
        game_rule_nameEdit->setText(rule->name());
        game_rule_pageEdit->setText(rule->page());
        game_rule_briefEdit->setText(rule->brief());
        game_rule_fullEdit->setPlainText(rule->description());
    }
    else
    {
        game_rule_idEdit->clear();
        game_rule_nameEdit->clear();
        game_rule_pageEdit->clear();
        game_rule_briefEdit->clear();
        game_rule_fullEdit->clear();
        
        game_ruleRemoveButton->setEnabled(false);
    }
    m_isProgrammaticChange = false;
    
    if(ruleFieldsEnabled != game_rule_idEdit->isEnabled())
    {
        game_rule_idEdit->setEnabled(ruleFieldsEnabled);
        game_rule_nameEdit->setEnabled(ruleFieldsEnabled);
        game_rule_pageEdit->setEnabled(ruleFieldsEnabled);
        game_rule_briefEdit->setEnabled(ruleFieldsEnabled);
        game_rule_fullEdit->setEnabled(ruleFieldsEnabled);
    }
    
    game_ruleSaveBox->setEnabled(false);
}

void WarEditWindow::doNewGameRule()
{
    QString id = genUniqueRuleId(*m_game, m_game_rules.length());
    
    Rule r;
    r.id(id);
    r.name("New Rule");
    r.page("N/A");
    r.brief("A Rule");
    m_game->addRule(r);
    
    m_game_rules.append(m_game->getRule(id));
    game_ruleList->addItem(r.name());
    game_ruleList->setCurrentRow(m_game_rules.length() - 1);
    setFileHasChanges(true);
}

void WarEditWindow::doRemoveGameRule()
{
    int index = game_ruleList->currentRow();
    if(index >= 0)
    {
        delete game_ruleList->takeItem(index);
        Rule *rule = m_game_rules.takeAt(index);
        m_game->removeRule(*rule);
        setFileHasChanges(true);
    }
}


bool WarEditWindow::askSaveOpenGame()
{
    if(fileHasChanges() && opmode() == GameMode)
    {
        int ret = QMessageBox::question(this, "Save Game?",
            "The current game has unsaved changes. Do you want to save them?",
            QMessageBox::No, QMessageBox::Cancel, QMessageBox::Yes);
        
        if(ret == QMessageBox::Yes)
        {
            if(!doSaveGame(false))
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

void WarEditWindow::closeGame()
{
    if(m_gameFile)
        delete m_gameFile;
    
    if(m_game)
        delete m_game;
    
    m_game_rules.clear();
    m_game = NULL;
    m_gameFile = NULL;
    populateGame();
    onGameRuleSelected(-1);
}

void WarEditWindow::populateGameRuleList()
{
    game_ruleList->clear();
    int len = m_game_rules.length();
    for(int i = 0; i < len; i++)
        game_ruleList->addItem(m_game_rules[i]->name());
}


void WarEditWindow::onMenuOpenGameClicked()
{
    int status = doOpenGame();
    closeRace();
    if(status == ActionOk)
    {
        //setWindowTitle("waredit - " + m_gameFile->fileName() + " [game]");
        setWindowFilePath(strippedFileName(m_gameFile->fileName()));
        setFileHasChanges(false);
        opmode(GameMode);
        enableActiveWidgets();
        populateGame();
        populateGameRuleList();
        onGameRuleSelected(-1);
        gameSaveBox->setEnabled(false);
        
        //remove me
        /*
        WarPage page(*m_game);
        game_rule_fullEdit->setEnabled(true);
        game_rule_fullEdit->setPlainText(page.toHtml());
        */
        
    }
    else if(status == ActionFailed)
    {
        setWindowFilePath("No File");
        opmode(NoMode);
        enableActiveWidgets();
    }
}

void WarEditWindow::onMenuNewGameClicked()
{
    if(askSaveOpenGame() && askSaveOpenRace()) // user continues
    {
        closeGame();
        closeRace();
        opmode(GameMode);
        m_game = new Game();
        setWindowFilePath("New Game");
        setFileHasChanges(true);
        enableActiveWidgets();
        onGameRuleSelected(-1);
    }
}


int WarEditWindow::doOpenGame()
{
    if(askSaveOpenGame() && askSaveOpenRace())
    {
        QString filter = "Game Files (*.game)";
        QString path = QFileDialog::getOpenFileName(this, "Open Game",
            m_pwd.path(), filter, &filter);
        
        if(path.isNull())
            return ActionCancelled;
        
        closeGame();
        
        m_gameFile = new QFile(path);
        if(!m_gameFile->open(QIODevice::ReadOnly))
        {
            QMessageBox::warning(this, "Open Error", "Could not open file " +
                m_gameFile->fileName() + ".\n\nDetails: " + m_gameFile->errorString());
            
            delete m_gameFile;
            m_gameFile = NULL;
            
            return ActionFailed;
        }
        
        QDomDocument doc;
        QString err;
        int line;
        if(!doc.setContent(m_gameFile, &err, &line))
        {
            QMessageBox::warning(this, "Parse Error", "Could not parse file " +
                m_gameFile->fileName() + "[line " + QString::number(line) + ": " +
                err + "]");
            
            delete m_gameFile;
            m_gameFile = NULL;
            
            return ActionFailed;
        }
        
        try
        {
            m_game = new Game(doc);
        }
        catch(XmlParseException e)
        {
            QMessageBox::warning(this, "Parse Error", "Could not parse file " +
                m_gameFile->fileName() + ".\n[" + e.elementName() + "@" +
                QString::number(e.line()) + "]: " + e.description());
            
            m_gameFile->close();
            delete m_gameFile;
            m_gameFile = NULL;
            m_game = NULL;
            
            return ActionFailed;
        }
        
        m_gameFile->close();
        m_game_rules = m_game->rules();
        qSort(m_game_rules.begin(), m_game_rules.end(), compareRule);
        
        setPwd(path);
        
        return ActionOk;
    }
    
    return ActionCancelled;
}

bool WarEditWindow::canSaveGame()
{
    if(gameSaveBox->isEnabled())
    {
        QMessageBox::warning(this, "Game Save Error",
            "The game contains changes that must be applied or discarded before saving can occur.");
        return false;
    }
    
    if(game_ruleSaveBox->isEnabled())
    {
        QMessageBox::warning(this, "Game Save Error",
            "The game's current rule contains changes that must be applied or discarded before saving can occur.");
        
        return false;
    }
    
    if(!validateGame())
        return false;
    
    return true;
}

void WarEditWindow::onMenuPreviewGameClicked()
{
    WarPage page(*m_game);
    WarPageViewerDialog *dia = new WarPageViewerDialog(this, page);
    dia->exec();
    delete dia;
}

void WarEditWindow::onMenuSaveGameClicked()
{
    doSaveGame(false);
}


void WarEditWindow::onMenuSaveGameAsClicked()
{
    doSaveGame(true);
}

bool WarEditWindow::doSaveGame(bool override)
{
    if(!canSaveGame())
        return false;
    
    if(!m_gameFile || override) // save as or new game
    {
        QString filter = "Game Files (*.game)";
        QString path = QFileDialog::getSaveFileName(this, "Save Game",
            m_pwd.path(), filter, &filter);
        
        if(path.isNull()) // user cancelled
            return false;
        
        if(m_gameFile)
            delete m_gameFile;
        
        m_gameFile = new QFile(path);
        setPwd(path);
    }
    
    if(!m_gameFile->open(QIODevice::WriteOnly))
    {
        QMessageBox::warning(this, "Save Error", "Could save to file " +
            m_gameFile->fileName() + ": " + m_gameFile->errorString());
        
        delete m_gameFile;
        m_gameFile = NULL;
        
        setFileHasChanges(true);
        return false;
    }
    
    QDomDocument doc;
    QDomElement worthless;
    try
    {
        m_game->toXml(doc, worthless);
    }
    catch(ValidationException e)
    {
        QMessageBox::warning(this, "Save Error", "An error occured while saving the game.\n" 
            + e.field() + ": " + e.reason());
        
        m_gameFile->close();
        return false;
    }
    
    QTextStream ts(m_gameFile);
    ts << doc.toString(4);
    
    m_gameFile->close();
    
    setWindowFilePath(strippedFileName(m_gameFile->fileName()));
    setFileHasChanges(false);
    
    return true;
}


void WarEditWindow::onGameRuleChanged()
{
    if(!m_isProgrammaticChange)
    {
        setEnabledList(game_ruleList, game_ruleNewButton, game_ruleRemoveButton,
            false);
        
        game_ruleSaveBox->setEnabled(true);
    }
}

void WarEditWindow::doCommitOrRollbackGameRule(QAbstractButton* button)
{
    if(game_ruleSaveBox->buttonRole(button) == QDialogButtonBox::ApplyRole)
    {
        if(validateGameRule())
        {
            Rule *r = m_game_rules[game_ruleList->currentRow()];
            if(r->id() != game_rule_idEdit->text())
            {
                QString oldId = r->id(), newId = game_rule_idEdit->text();
                r = m_game->resetRuleId(oldId, newId);
                m_game_rules[game_ruleList->currentRow()] = r;
            }
            //r->id(game_rule_idEdit->text());
            r->name(game_rule_nameEdit->text());
            r->page(game_rule_pageEdit->text());
            r->brief(game_rule_briefEdit->text());
            r->description(game_rule_fullEdit->toPlainText());
            
            game_ruleList->currentItem()->setText(r->name());
            setFileHasChanges(true);
            game_ruleSaveBox->setEnabled(false);
        }
    }
    else
    {
        onGameRuleSelected(game_ruleList->currentRow());
        if(validateGameRule(false))
            game_ruleSaveBox->setEnabled(false);
    }
    
    setEnabledList(game_ruleList, game_ruleNewButton, game_ruleRemoveButton,
                   true);
}


bool WarEditWindow::validateGameRule(bool show)
{
    QString fault;

    trim(game_rule_idEdit);
    trim(game_rule_nameEdit);
    trim(game_rule_pageEdit);
    trim(game_rule_briefEdit);
    trim(game_rule_fullEdit);
    
    if(game_rule_idEdit->text().isEmpty())
        fault = "ID";
    else if(game_rule_nameEdit->text().isEmpty())
        fault = "Name";
    else if(game_rule_pageEdit->text().isEmpty())
        fault = "Page";
    else if(game_rule_briefEdit->text().isEmpty())
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
    
    Rule *check = m_game->getRule(game_rule_idEdit->text());
    Rule *rule = m_game_rules[game_ruleList->currentRow()];
    // check if the current rule's id exists in the game. if it does check if
    // the found rule is the current rule. if it is not, user trying to make a
    // rule without a unique id
    if(check && check != rule)
    {
        if(show)
        {
            QMessageBox::warning(this, "Rule Validation Error",
                "The Rule ID you enetered is not unique. Please choose a unique Rule ID.");
        }
        
        return false;
    }   
    
    return true;
}
