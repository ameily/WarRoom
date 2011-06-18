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


#ifndef WAREDITWINDOW_H
#define WAREDITWINDOW_H

#include "designer/ui_GameRaceEdit.h"
#include <Game.h>
#include <Race.h>
#include <QFile>
#include <QAbstractButton>
#include <QMainWindow>
#include <QCloseEvent>
#include <QDir>
#include <QDomDocument>

class WarEditWindow : public QMainWindow, public Ui::MainWindow
{
    Q_OBJECT
    
public:
    WarEditWindow(QWidget *parent = 0);
    virtual ~WarEditWindow();
    void setPwd(const QString& dir);
    
    
    
protected:
    virtual void closeEvent(QCloseEvent* event);
    
private slots:
    void onGameChanged();
    void onGameRuleChanged();
    void doCommitOrRollbackGame(QAbstractButton *button);
    void doCommitOrRollbackGameRule(QAbstractButton *button);
    
    void onMenuNewGameClicked();
    void onMenuSaveGameClicked();
    void onMenuSaveGameAsClicked();
    void onMenuOpenGameClicked();
    void onMenuPreviewGameClicked();
    void doNewGameRule();
    void doRemoveGameRule();
    void onGameRuleSelected(int index);
    
    void onRaceChanged();
    void onRaceRuleChanged();
    void onRaceWargearChanged();
    void onRaceUnitChanged();
    
    void onRaceUnitWargearSelected(int index);
    void doNewRaceUnitWargear();
    void doEditRaceUnitWargear();
    void doRemoveRaceUnitWargear();
    void onRaceUnitRuleSelected(int index);
    void doNewRaceUnitRule();
    void doEditRaceUnitRule();
    void doRemoveRaceUnitRule();
    void onRaceWargearProfileSelected(int index);
    void doNewRaceWargearProfile();
    void doEditRaceWargearProfile();
    void doRemoveRaceWargearProfile();
    
    
    void doNewRaceRule();
    void doNewRaceUnit();
    void doNewRaceWargear();
    void doRemoveRaceRule();
    void doRemoveRaceUnit();
    void doRemoveRaceWargear();
    
    
    void onMenuNewRace();
    void onMenuPreviewRaceClicked();
    void doMenuOpenRace();
    void doMenuSaveRace();
    void doMenuSaveRaceAs();
    void onRaceRuleSelected(int index);
    void onRaceUnitSelected(int index, bool reload = true);
    void onRaceWargearSelected(int index, bool reload = true);
    void doCommitOrRollbackRace(QAbstractButton *button);
    void doCommitOrRollbackRaceUnit(QAbstractButton *button);
    void doCommitOrRollbackRaceRule(QAbstractButton *button);
    void doCommitOrRollbackRaceWargear(QAbstractButton *button);
    
    void doShowUnitContextMenu(const QPoint& p);
    
private:
    enum OpMode { GameMode, RaceMode, NoMode };
    enum UserAction { ActionFailed, ActionCancelled, ActionOk };
    
    int m_opMode;
    QString strippedFileName(const QString& file);
    void setFileHasChanges(bool val);
    bool fileHasChanges();
    void enableActiveWidgets();
    bool validateGame(bool show = true);
    bool validateGameRule(bool show = true);
    QString genUniqueRuleId(const RuleList& list, int start);
    QString genUniqueUnitId();
    void opmode(int mode);
    int opmode() const;
    
    void setupConnections();
    
    
    int doOpenGame(const QString& gameId = QString());
    
    void trim(QLineEdit *box);
    void trim(QPlainTextEdit *box);
    
    /*!
     * false: cancel
     * true: proceed
     */
    bool askSaveOpenGame();
    
    bool askSaveOpenRace();
    
    /*!
     * Close the current game file, disable menu items save, save as, and
     * disable the game tab.
     */
    void closeGame();
    void closeRace();
    void populateRaceLists();
    int doOpenRace();
    
    void populateRace();
    
    bool canSaveGame();
    bool doSaveGame(bool override = false);
    
    bool canSaveRace();
    bool doSaveRace(bool override = false);
    
    void populateGame();
    void populateGameRuleList();
    bool validateRace(bool show = true);
    bool validateRaceRule(bool show = true);
    bool validateRaceUnit(bool show = true);
    bool validateRaceWargear(bool show = true);
    
    
    
    void setEnabledList(QListWidget *list, QPushButton *add, QPushButton *remove,
                        bool val);
    bool openXml(QDomDocument& doc, QFile *file);
    
    QFile *m_gameFile;
    QFile *m_raceFile;
    Game *m_game;
    Race *m_race;
    QList<Rule*> m_game_rules;
    QList<Rule*> m_race_rules;
    QList<Wargear*> m_race_wargears;
    QList<Wargear*> m_all_wargears;
    QList<Unit*> m_race_units;
    Unit *m_race_unit;
    Wargear *m_race_wargear;
    Rule *m_race_rule;
    QList<RuleRef*> m_race_unit_rules;
    QList<WargearRef*> m_race_unit_wargears;
    QList<WargearProfile*> m_race_wargear_profiles;
    
    bool m_isProgrammaticChange;
    bool m_gameHasChanges;
    bool m_raceHasChanges;
    bool m_fileHasChanges;
    QDir m_pwd;
};

#endif // WAREDITWINDOW_H
