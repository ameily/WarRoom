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
#include "WarEditWindow.moc"
#include <QPushButton>
#include <QIcon>
#include <QMessageBox>
#include <QTextStream>
#include <QDebug>
#include <QtAlgorithms>
#include <QDesktopServices>

/*
 * [menu] open game
 *      ask save open game
 *      ask save open race
 *      closeGame()
 *      closeRace()
 *      opmode = InvalidMode
 *      doOpenGame
 *      opmode = GameMode
 *      setupWindow
 * 
 * [menu] open race
 *      ask save open race
 *      closeRace()
 *      opmode = InvalidMode
 *      doOpenRace
 *      opmode = RaceMode
 *      setupWindow
 * 
 * doOpenGame
 *      load game
 *      populate game
 * 
 * doOpenRace
 *      load race
 *          > doOpenGame
 *      
 *      populate race
 * 
 * setupWindow
 *      if opmode = RaceMode
 *          disable game fields (except rule list)
 *          enable race fields
 *      else if opmode = GameMode
 *          clear race
 *          disable race
 *          enable game fields
 *      else
 *          clear race fields
 *          disable race
 *          clear game fields
 *          disable game
 * 
 * closeGame
 *      delete m_game
 *      m_game = NULL
 *      clear game fields
 *      disable game
 * 
 * closeRace
 *      delete m_race
 *      m_race = NULL
 *      clear race fields
 *      disable race
 */ 

WarEditWindow::WarEditWindow(QWidget *parent) : QMainWindow(parent), m_pwd(QDir::currentPath())
{
    setupUi(this);
    opmode(NoMode);
    /*
    QIcon newIcon = QIcon::fromTheme("document-new");
    QIcon openIcon = QIcon::fromTheme("document-open");
    QIcon saveIcon = QIcon::fromTheme("document-save");
    QIcon saveAsIcon = QIcon::fromTheme("document-save-as");
    QIcon addIcon = QIcon::fromTheme("list-add");
    QIcon removeIcon = QIcon::fromTheme("list-remove");
    QIcon editIcon = QIcon::fromTheme("document-properties");
    
    actionOpenGame->setIcon(openIcon);
    actionSaveGame->setIcon(saveIcon);
    actionNewGame->setIcon(newIcon);
    actionSaveGameAs->setIcon(saveAsIcon);
    game_ruleNewButton->setIcon(addIcon);
    game_ruleRemoveButton->setIcon(removeIcon);
    
    actionNewRace->setIcon(newIcon);
    actionOpenRace->setIcon(openIcon);
    actionSaveRace->setIcon(saveIcon);
    actionSaveRaceAs->setIcon(saveAsIcon);
    race_ruleNewButton->setIcon(addIcon);
    race_ruleRemoveButton->setIcon(removeIcon);
    race_unitNewButton->setIcon(addIcon);
    race_unitRemoveButton->setIcon(removeIcon);
    race_wargearNewButton->setIcon(addIcon);
    race_wargearRemoveButton->setIcon(removeIcon);
    race_wargear_profileNewButton->setIcon(addIcon);
    race_wargear_profileRemoveButton->setIcon(removeIcon);
    race_wargear_profileEditButton->setIcon(editIcon);
    race_unit_wargearAddButton->setIcon(addIcon);
    race_unit_wargearRemoveButton->setIcon(removeIcon);
    race_unit_wargearEditButton->setIcon(editIcon);
    race_unit_ruleAddButton->setIcon(addIcon);
    race_unit_ruleRemoveButton->setIcon(removeIcon);
    race_unit_ruleEditButton->setIcon(editIcon);
    */
    m_isProgrammaticChange = false;
    m_game = NULL;
    m_race = NULL;
    m_gameFile = NULL;
    m_raceFile = NULL;
    
    setupConnections();
    closeGame();
    closeRace();
    
    enableActiveWidgets();
    setWindowFilePath("No File");
    setFileHasChanges(false);
}

void WarEditWindow::enableActiveWidgets()
{
    bool gameFieldsReadOnly;
    bool raceFieldsReadOnly;
    int tab = 0;
    if(opmode() == GameMode)
    {
        actionSaveGame->setEnabled(true);
        actionSaveGameAs->setEnabled(true);
        actionPreviewGame->setEnabled(true);
        gameTab->setEnabled(true);
        
        actionSaveRace->setEnabled(false);
        actionSaveRaceAs->setEnabled(false);
        actionPreviewRace->setEnabled(false);
        raceTab->setEnabled(false);
        gameFieldsReadOnly = false;
        raceFieldsReadOnly = false;
        tab = 0;
    }
    else if(opmode() == RaceMode)
    {
        actionSaveGame->setEnabled(false);
        actionSaveGameAs->setEnabled(false);
        actionPreviewGame->setEnabled(true);
        gameTab->setEnabled(true);
        gameSaveBox->setEnabled(false);
        
        actionSaveRace->setEnabled(true);
        actionSaveRaceAs->setEnabled(true);
        actionPreviewRace->setEnabled(true);
        raceTab->setEnabled(true);
        
        race_gameEdit->setEnabled(false);
        gameFieldsReadOnly = true;
        raceFieldsReadOnly = false;
        tab = 1;
    }
    else if(opmode() == NoMode)
    {
        actionSaveGame->setEnabled(false);
        actionSaveGameAs->setEnabled(false);
        actionPreviewGame->setEnabled(false);
        gameTab->setEnabled(false);
        
        actionSaveRace->setEnabled(false);
        actionSaveRaceAs->setEnabled(false);
        actionPreviewRace->setEnabled(false);
        raceTab->setEnabled(false);
        gameFieldsReadOnly = false;
        raceFieldsReadOnly = false;
        tab = 0;
    }
    
    gameRaceTabWidget->setCurrentIndex(tab);
    
    game_idEdit->setReadOnly(gameFieldsReadOnly);
    game_nameEdit->setReadOnly(gameFieldsReadOnly);
    game_bookEdit->setReadOnly(gameFieldsReadOnly);
    game_editionEdit->setReadOnly(gameFieldsReadOnly);
    game_versionEdit->setReadOnly(gameFieldsReadOnly);
    game_rule_idEdit->setReadOnly(gameFieldsReadOnly);
    game_rule_nameEdit->setReadOnly(gameFieldsReadOnly);
    game_rule_briefEdit->setReadOnly(gameFieldsReadOnly);
    game_rule_pageEdit->setReadOnly(gameFieldsReadOnly);
    game_rule_fullEdit->setReadOnly(gameFieldsReadOnly);
    //game_rule_wargearCheckBox->blockSignals(gameFieldsReadOnly);
    game_rule_wargearCheckBox->setEnabled(false);
    game_ruleNewButton->setEnabled(!gameFieldsReadOnly);
    
    race_idEdit->setReadOnly(raceFieldsReadOnly);
    race_nameEdit->setReadOnly(raceFieldsReadOnly);
    race_bookEdit->setReadOnly(raceFieldsReadOnly);
    race_editionEdit->setReadOnly(raceFieldsReadOnly);
    race_versionEdit->setReadOnly(raceFieldsReadOnly);
    // etc
    // TODO all race fields
}


void WarEditWindow::closeEvent(QCloseEvent* event)
{
    bool doExit;
    if(askSaveOpenGame() && askSaveOpenRace())
        doExit = true;
    else
        doExit = false;
    
    if(doExit)
        event->accept();
    else
        event->ignore();
}

void WarEditWindow::setPwd(const QString& dir)
{
    QFileInfo info(dir);
    if(info.isDir())
        m_pwd = QDir(dir);
    else
        m_pwd = info.dir();
}


WarEditWindow::~WarEditWindow()
{
    if(m_game)
        delete m_game;
    
    if(m_race)
        delete m_race;
    
    if(m_gameFile)
        delete m_gameFile;
    
    if(m_raceFile)
        delete m_raceFile;
}


void WarEditWindow::setupConnections()
{
    connect(game_idEdit, SIGNAL(textEdited(const QString&)), SLOT(onGameChanged()));
    connect(game_nameEdit, SIGNAL(textEdited(const QString&)), SLOT(onGameChanged()));
    connect(game_bookEdit, SIGNAL(textEdited(const QString&)), SLOT(onGameChanged()));
    connect(game_editionEdit, SIGNAL(textEdited(const QString&)), SLOT(onGameChanged()));
    connect(game_versionEdit, SIGNAL(textEdited(const QString&)), SLOT(onGameChanged()));
    
    connect(gameSaveBox, SIGNAL(clicked(QAbstractButton*)),
        SLOT(doCommitOrRollbackGame(QAbstractButton*)));
    
    connect(actionNewGame, SIGNAL(triggered(bool)), SLOT(onMenuNewGameClicked()));
    connect(actionSaveGame, SIGNAL(triggered(bool)), SLOT(onMenuSaveGameClicked()));
    connect(actionSaveGameAs, SIGNAL(triggered(bool)), SLOT(onMenuSaveGameAsClicked()));
    connect(actionOpenGame, SIGNAL(triggered(bool)), SLOT(onMenuOpenGameClicked()));
    connect(actionPreviewGame, SIGNAL(triggered(bool)), SLOT(onMenuPreviewGameClicked()));
    
    connect(game_ruleList, SIGNAL(currentRowChanged(int)),
            SLOT(onGameRuleSelected(int)));
    
    connect(game_ruleNewButton, SIGNAL(clicked(bool)), SLOT(doNewGameRule()));
    connect(game_ruleRemoveButton, SIGNAL(clicked(bool)),
            SLOT(doRemoveGameRule()));
    
    connect(game_ruleSaveBox, SIGNAL(clicked(QAbstractButton*)),
            SLOT(doCommitOrRollbackGameRule(QAbstractButton*)));
    
    connect(game_rule_idEdit, SIGNAL(textEdited(const QString&)), SLOT(onGameRuleChanged()));
    connect(game_rule_nameEdit, SIGNAL(textEdited(const QString&)), SLOT(onGameRuleChanged()));
    connect(game_rule_briefEdit, SIGNAL(textEdited(const QString&)), SLOT(onGameRuleChanged()));
    connect(game_rule_pageEdit, SIGNAL(textEdited(const QString&)), SLOT(onGameRuleChanged()));
    connect(game_rule_fullEdit, SIGNAL(textEdited()), SLOT(onGameRuleChanged()));
    connect(game_rule_wargearCheckBox, SIGNAL(toggled(bool)), SLOT(onGameRuleChanged()));
    
    // ----------------
    connect(actionNewRace, SIGNAL(triggered(bool)), SLOT(onMenuNewRace()));
    connect(actionOpenRace, SIGNAL(triggered(bool)), SLOT(doMenuOpenRace()));
    connect(actionSaveRace, SIGNAL(triggered(bool)), SLOT(doMenuSaveRace()));
    connect(actionSaveRaceAs, SIGNAL(triggered(bool)), SLOT(doMenuSaveRaceAs()));
    connect(actionPreviewRace, SIGNAL(triggered(bool)), SLOT(onMenuPreviewRaceClicked()));
    
    connect(raceSaveBox, SIGNAL(clicked(QAbstractButton*)),
            SLOT(doCommitOrRollbackRace(QAbstractButton*)));
    connect(race_ruleSaveBox, SIGNAL(clicked(QAbstractButton*)),
            SLOT(doCommitOrRollbackRaceRule(QAbstractButton*)));
    connect(race_unitSaveBox, SIGNAL(clicked(QAbstractButton*)),
            SLOT(doCommitOrRollbackRaceUnit(QAbstractButton*)));
    connect(race_wargearSaveBox, SIGNAL(clicked(QAbstractButton*)),
            SLOT(doCommitOrRollbackRaceWargear(QAbstractButton*)));
    
    connect(race_idEdit, SIGNAL(textEdited(const QString&)), SLOT(onRaceChanged()));
    connect(race_nameEdit, SIGNAL(textEdited(const QString&)), SLOT(onRaceChanged()));
    connect(race_bookEdit, SIGNAL(textEdited(const QString&)), SLOT(onRaceChanged()));
    connect(race_editionEdit, SIGNAL(textEdited(const QString&)), SLOT(onRaceChanged()));
    connect(race_versionEdit, SIGNAL(textEdited(const QString&)), SLOT(onRaceChanged()));
    
    connect(race_ruleList, SIGNAL(currentRowChanged(int)), SLOT(onRaceRuleSelected(int)));
    connect(race_unitList, SIGNAL(currentRowChanged(int)), SLOT(onRaceUnitSelected(int)));
    connect(race_wargearList, SIGNAL(currentRowChanged(int)), SLOT(onRaceWargearSelected(int)));
    
    connect(race_unitNewButton, SIGNAL(clicked()), SLOT(doNewRaceUnit()));
    connect(race_unitRemoveButton, SIGNAL(clicked()), SLOT(doRemoveRaceUnit()));
    connect(race_wargearNewButton, SIGNAL(clicked()), SLOT(doNewRaceWargear()));
    connect(race_wargearRemoveButton, SIGNAL(clicked()), SLOT(doRemoveRaceWargear()));
    connect(race_ruleNewButton, SIGNAL(clicked()), SLOT(doNewRaceRule()));
    connect(race_ruleRemoveButton, SIGNAL(clicked()), SLOT(doRemoveRaceRule()));
    
    connect(race_unit_wargearList, SIGNAL(currentRowChanged(int)), SLOT(onRaceUnitWargearSelected(int)));
    connect(race_unit_ruleList, SIGNAL(currentRowChanged(int)), SLOT(onRaceUnitRuleSelected(int)));
    connect(race_wargear_profileList, SIGNAL(currentRowChanged(int)), SLOT(onRaceWargearProfileSelected(int)));
    
    connect(race_unit_ruleAddButton, SIGNAL(clicked()), SLOT(doNewRaceUnitRule()));
    connect(race_unit_ruleEditButton, SIGNAL(clicked()), SLOT(doEditRaceUnitRule()));
    connect(race_unit_ruleRemoveButton, SIGNAL(clicked()), SLOT(doRemoveRaceUnitRule()));
    
    connect(race_unit_wargearAddButton, SIGNAL(clicked()), SLOT(doNewRaceUnitWargear()));
    connect(race_unit_wargearEditButton, SIGNAL(clicked()), SLOT(doEditRaceUnitWargear()));
    connect(race_unit_wargearRemoveButton, SIGNAL(clicked()), SLOT(doRemoveRaceUnitWargear()));
    
    connect(race_wargear_profileNewButton, SIGNAL(clicked()), SLOT(doNewRaceWargearProfile()));
    connect(race_wargear_profileEditButton, SIGNAL(clicked()), SLOT(doEditRaceWargearProfile()));
    connect(race_wargear_profileRemoveButton, SIGNAL(clicked()), SLOT(doRemoveRaceWargearProfile()));
    
    connect(race_rule_idEdit, SIGNAL(textEdited(const QString&)), SLOT(onRaceRuleChanged()));
    connect(race_rule_briefEdit, SIGNAL(textEdited(const QString&)), SLOT(onRaceRuleChanged()));
    connect(race_rule_nameEdit, SIGNAL(textEdited(const QString&)), SLOT(onRaceRuleChanged()));
    connect(race_rule_fullEdit, SIGNAL(textEdited()), SLOT(onRaceRuleChanged()));
    connect(race_rule_pageEdit, SIGNAL(textEdited(const QString&)), SLOT(onRaceRuleChanged()));
    
    connect(race_unit_idEdit, SIGNAL(textEdited(const QString&)), SLOT(onRaceUnitChanged()));
    connect(race_unit_nameEdit, SIGNAL(textEdited(const QString&)), SLOT(onRaceUnitChanged()));
    connect(race_unit_pageEdit, SIGNAL(textEdited(const QString&)), SLOT(onRaceUnitChanged()));
    connect(race_unit_bsEdit, SIGNAL(textEdited(const QString&)), SLOT(onRaceUnitChanged()));
    connect(race_unit_wsEdit, SIGNAL(textEdited(const QString&)), SLOT(onRaceUnitChanged()));
    connect(race_unit_sEdit, SIGNAL(textEdited(const QString&)), SLOT(onRaceUnitChanged()));
    connect(race_unit_tEdit, SIGNAL(textEdited(const QString&)), SLOT(onRaceUnitChanged()));
    connect(race_unit_aEdit, SIGNAL(textEdited(const QString&)), SLOT(onRaceUnitChanged()));
    connect(race_unit_wEdit, SIGNAL(textEdited(const QString&)), SLOT(onRaceUnitChanged()));
    connect(race_unit_iEdit, SIGNAL(textEdited(const QString&)), SLOT(onRaceUnitChanged()));
    connect(race_unit_ldEdit, SIGNAL(textEdited(const QString&)), SLOT(onRaceUnitChanged()));
    connect(race_unit_svEdit, SIGNAL(textEdited(const QString&)), SLOT(onRaceUnitChanged()));
    connect(race_unit_isvEdit, SIGNAL(textEdited(const QString&)), SLOT(onRaceUnitChanged()));
    connect(race_unit_afEdit, SIGNAL(textEdited(const QString&)), SLOT(onRaceUnitChanged()));
    connect(race_unit_asEdit, SIGNAL(textEdited(const QString&)), SLOT(onRaceUnitChanged()));
    connect(race_unit_arEdit, SIGNAL(textEdited(const QString&)), SLOT(onRaceUnitChanged()));
    
    connect(race_wargear_idEdit, SIGNAL(textEdited(const QString&)), SLOT(onRaceWargearChanged()));
    connect(race_wargear_nameEdit, SIGNAL(textEdited(const QString&)), SLOT(onRaceWargearChanged()));
    connect(race_wargear_pageEdit, SIGNAL(textEdited(const QString&)), SLOT(onRaceWargearChanged()));
    connect(race_wargear_briefEdit, SIGNAL(textEdited(const QString&)), SLOT(onRaceWargearChanged()));
    connect(race_wargear_fullEdit, SIGNAL(textEdited()), SLOT(onRaceWargearChanged()));
    
    race_unitList->setContextMenuPolicy(Qt::CustomContextMenu);
    connect(race_unitList, SIGNAL(customContextMenuRequested(const QPoint&)), SLOT(doShowUnitContextMenu(const QPoint&)));
}



void WarEditWindow::trim(QLineEdit* box)
{
    m_isProgrammaticChange = true;
    box->setText(box->text().trimmed());
    m_isProgrammaticChange = false;
}

void WarEditWindow::trim(QPlainTextEdit* box)
{
    m_isProgrammaticChange = true;
    box->setPlainText(box->toPlainText().trimmed());
    m_isProgrammaticChange = false;
}

void WarEditWindow::setEnabledList(QListWidget* list, QPushButton* add,
                                   QPushButton* remove, bool val)
{
    list->setEnabled(val);
    add->setEnabled(val);
    if(val && list->currentRow() >= 0)
        remove->setEnabled(true);
    else
        remove->setEnabled(false);
}

QString WarEditWindow::genUniqueRuleId(const RuleList& list, int start)
{
    QString id;
    bool done = false;
    int diff = 1;
    while(!done)
    {
        id = "rule_" + QString::number(diff + start);
        if(!list.hasRule(id))
            done = true;
        else
            diff++;
    }
    
    return id;
}

bool WarEditWindow::openXml(QDomDocument& doc, QFile* file)
{
    QString err;
    int line;
    if(!doc.setContent(file, &err, &line))
    {
        QMessageBox::warning(this, "Parse Error", "Could not parse file " +
            file->fileName() + "[line " + QString::number(line) + ": " +
            err + "]");
        
        return false;
    }
    
    return true;
}

QString WarEditWindow::strippedFileName(const QString& file)
{
    return QFileInfo(file).fileName();
}

void WarEditWindow::setFileHasChanges(bool val)
{
    setWindowModified(val);
    m_fileHasChanges = val;
}

bool WarEditWindow::fileHasChanges()
{
    return m_fileHasChanges;
}

void WarEditWindow::opmode(int mode)
{
    m_opMode = mode;
    
    QAction *action = 0;
    QList<QAction*> unset;
    
    if(m_opMode == GameMode)
    {
        action = actionSaveGame;
        unset.append(actionSaveRace);
    }
    else if(m_opMode == RaceMode)
    {
        action = actionSaveRace;
        unset.append(actionSaveRace);
    }
    else
    {
        unset.append(actionSaveGame);
        unset.append(actionSaveRace);
    }
    
    foreach(QAction *a, unset)
    {
        a->setShortcut(QKeySequence());
    }
    
    if(action)
        action->setShortcut(QKeySequence::Save);
}

int WarEditWindow::opmode() const
{
    return m_opMode;
}

QString WarEditWindow::genUniqueUnitId()
{
    if(!m_race)
        return QString();
    
    int num = m_race_units.length() + 1;
    QString id;
    bool done = false;
    while(!done)
    {
        id = "unit_" + QString::number(num);
        if(!m_race->getUnit(id))
            done = true;
        else
            num++;
    }
    
    return id;
}




