/********************************************************************************
** Form generated from reading UI file 'GameRaceEditjC2475.ui'
**
** Created: Mon May 16 16:49:31 2011
**      by: Qt User Interface Compiler version 4.7.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef GAMERACEEDITJC2475_H
#define GAMERACEEDITJC2475_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QFormLayout>
#include <QtGui/QGridLayout>
#include <QtGui/QGroupBox>
#include <QtGui/QHBoxLayout>
#include <QtGui/QHeaderView>
#include <QtGui/QLabel>
#include <QtGui/QLineEdit>
#include <QtGui/QListWidget>
#include <QtGui/QMainWindow>
#include <QtGui/QMenu>
#include <QtGui/QMenuBar>
#include <QtGui/QPushButton>
#include <QtGui/QTabWidget>
#include <QtGui/QVBoxLayout>
#include <QtGui/QWidget>
#include <widgets/RefPlainTextEdit.h>
#include <widgets/WarButtonBox.h>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QAction *actionOpenGame;
    QAction *actionSaveGame;
    QAction *actionNewGame;
    QAction *actionOpenRace;
    QAction *actionSaveRace;
    QAction *actionNewRace;
    QAction *actionSaveGameAs;
    QAction *actionSaveRaceAs;
    QAction *actionPreviewGame;
    QWidget *centralwidget;
    QHBoxLayout *horizontalLayout;
    QTabWidget *gameRaceTabWidget;
    QWidget *gameTab;
    QVBoxLayout *verticalLayout_3;
    QVBoxLayout *gameVBox;
    QFormLayout *gameForm;
    QLabel *game_idLabel;
    QLineEdit *game_idEdit;
    QLabel *game_nameLabel;
    QLineEdit *game_nameEdit;
    QLabel *game_bookLabel;
    QLineEdit *game_bookEdit;
    QLabel *game_editionLabel;
    QLineEdit *game_editionEdit;
    QLabel *game_versionLabel;
    QLineEdit *game_versionEdit;
    WarButtonBox *gameSaveBox;
    QGroupBox *game_rulesGroupBox;
    QVBoxLayout *rulesVBox;
    QHBoxLayout *game_rulesHBox;
    QFormLayout *game_ruleForm;
    QLabel *game_rule_idLabel;
    QLineEdit *game_rule_idEdit;
    QLabel *game_rule_nameLabel;
    QLineEdit *game_rule_nameEdit;
    QLabel *game_rule_pageLabel;
    QLineEdit *game_rule_pageEdit;
    QLabel *game_rule_briefLabel;
    QLineEdit *game_rule_briefEdit;
    QLabel *game_rule_fullLabel;
    WarButtonBox *game_ruleSaveBox;
    RefPlainTextEdit *game_rule_fullEdit;
    QVBoxLayout *game_ruleListVBox;
    QListWidget *game_ruleList;
    QHBoxLayout *game_ruleListActionsHBox;
    QPushButton *game_ruleNewButton;
    QPushButton *game_ruleRemoveButton;
    QWidget *raceTab;
    QVBoxLayout *verticalLayout;
    QFormLayout *raceForm;
    QLabel *race_idLabel;
    QLineEdit *race_idEdit;
    QLabel *race_nameLabel;
    QLineEdit *race_nameEdit;
    QLabel *race_bookLabel;
    QLineEdit *race_bookEdit;
    QLabel *race_editionLabel;
    QLineEdit *race_editionEdit;
    QLabel *race_versionLabel;
    QLineEdit *race_versionEdit;
    QLabel *race_gameLabel;
    QLineEdit *race_gameEdit;
    WarButtonBox *raceSaveBox;
    QTabWidget *race_tabWidget;
    QWidget *race_rulesTab;
    QHBoxLayout *horizontalLayout_2;
    QFormLayout *race_ruleForm;
    QLineEdit *race_rule_idEdit;
    QLabel *race_rule_nameLabel;
    QLineEdit *race_rule_nameEdit;
    QLabel *race_rule_idLabel;
    QLabel *race_rule_pageLabel;
    QLineEdit *race_rule_pageEdit;
    QLabel *race_rule_briefLabel;
    QLineEdit *race_rule_briefEdit;
    QLabel *race_rule_fullLabel;
    RefPlainTextEdit *race_rule_fullEdit;
    WarButtonBox *race_ruleSaveBox;
    QVBoxLayout *race_rulesVBox;
    QListWidget *race_ruleList;
    QHBoxLayout *race_ruleListActionBox;
    QPushButton *race_ruleNewButton;
    QPushButton *race_ruleRemoveButton;
    QWidget *race_wargearsTab;
    QHBoxLayout *horizontalLayout_7;
    QVBoxLayout *verticalLayout_7;
    QFormLayout *race_wargearForm;
    QLabel *race_wargear_idLabel;
    QLineEdit *race_wargear_idEdit;
    QLabel *race_wargear_nameLabel;
    QLineEdit *race_wargear_nameEdit;
    QLabel *race_wargear_briefLabel;
    QLineEdit *race_wargear_briefEdit;
    QLabel *race_wargear_fullLabel;
    RefPlainTextEdit *race_wargear_fullEdit;
    WarButtonBox *race_wargearSaveBox;
    QGroupBox *race_wargear_profilesGroup;
    QVBoxLayout *race_wargear_profileVBox;
    QListWidget *race_wargear_profileList;
    QHBoxLayout *race_wargear_profileActionBox;
    QPushButton *race_wargear_profileNewButton;
    QPushButton *race_wargear_profileEditButton;
    QPushButton *race_wargear_profileRemoveButton;
    QVBoxLayout *race_wargearVBox;
    QListWidget *race_wargearList;
    QHBoxLayout *race_wargearListActionBox;
    QPushButton *race_wargearNewButton;
    QPushButton *race_wargearRemoveButton;
    QWidget *race_unitsTab;
    QHBoxLayout *horizontalLayout_4;
    QVBoxLayout *verticalLayout_5;
    QFormLayout *race_unitForm;
    QLabel *race_unit_idLabel;
    QLineEdit *race_unit_idEdit;
    QLabel *race_unit_nameLabel;
    QLineEdit *race_unit_nameEdit;
    QGridLayout *race_unit_profileGrid;
    QLabel *race_unit_wsLabel;
    QLabel *race_unit_bsLabel;
    QLabel *race_unit_sLabel;
    QLabel *race_unit_tLabel;
    QLabel *race_unit_wLabel;
    QLabel *race_unit_iLabel;
    QLabel *race_unit_aLabel;
    QLabel *race_unit_ldLabel;
    QLabel *race_unit_svLabel;
    QLabel *race_unit_isvLabel;
    QLabel *race_unit_afLabel;
    QLabel *race_unit_asLabel;
    QLabel *race_unit_arLabel;
    QLabel *race_unit_profile_armourLabel;
    QLineEdit *race_unit_wsEdit;
    QLineEdit *race_unit_bsEdit;
    QLineEdit *race_unit_sEdit;
    QLineEdit *race_unit_tEdit;
    QLineEdit *race_unit_wEdit;
    QLineEdit *race_unit_iEdit;
    QLineEdit *race_unit_aEdit;
    QLineEdit *race_unit_ldEdit;
    QLineEdit *race_unit_svEdit;
    QLineEdit *race_unit_isvEdit;
    QLineEdit *race_unit_afEdit;
    QLineEdit *race_unit_asEdit;
    QLineEdit *race_unit_arEdit;
    WarButtonBox *race_unitSaveBox;
    QGroupBox *race_unit_wargearGroup;
    QVBoxLayout *race_unit_wargearVBox;
    QListWidget *race_unit_wargearList;
    QHBoxLayout *race_unit_wargearActionBox;
    QPushButton *race_unit_wargearAddButton;
    QPushButton *race_unit_wargearEditButton;
    QPushButton *race_unit_wargearRemoveButton;
    QGroupBox *race_unit_rulesGroup;
    QVBoxLayout *race_unit_rulesVBox;
    QListWidget *race_unit_ruleList;
    QHBoxLayout *race_unit_rulesActionBox;
    QPushButton *race_unit_ruleAddButton;
    QPushButton *race_unit_ruleEditButton;
    QPushButton *race_unit_ruleRemoveButton;
    QVBoxLayout *race_unitsVBox;
    QListWidget *race_unitList;
    QHBoxLayout *race_unitsActionBox;
    QPushButton *race_unitNewButton;
    QPushButton *race_unitRemoveButton;
    QMenuBar *menubar;
    QMenu *menuGame;
    QMenu *menuRace;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QString::fromUtf8("MainWindow"));
        MainWindow->resize(652, 732);
        QSizePolicy sizePolicy(QSizePolicy::Minimum, QSizePolicy::Preferred);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(MainWindow->sizePolicy().hasHeightForWidth());
        MainWindow->setSizePolicy(sizePolicy);
        MainWindow->setMinimumSize(QSize(652, 0));
        MainWindow->setWindowTitle(QString::fromUtf8(""));
        QIcon icon;
        icon.addFile(QString::fromUtf8(":/icons/mushroom-cloud.gif"), QSize(), QIcon::Normal, QIcon::Off);
        MainWindow->setWindowIcon(icon);
        actionOpenGame = new QAction(MainWindow);
        actionOpenGame->setObjectName(QString::fromUtf8("actionOpenGame"));
        QIcon icon1;
        icon1.addFile(QString::fromUtf8(":/icons/document-open.png"), QSize(), QIcon::Normal, QIcon::Off);
        actionOpenGame->setIcon(icon1);
        actionSaveGame = new QAction(MainWindow);
        actionSaveGame->setObjectName(QString::fromUtf8("actionSaveGame"));
        QIcon icon2;
        icon2.addFile(QString::fromUtf8(":/icons/document-save.png"), QSize(), QIcon::Normal, QIcon::Off);
        actionSaveGame->setIcon(icon2);
        actionNewGame = new QAction(MainWindow);
        actionNewGame->setObjectName(QString::fromUtf8("actionNewGame"));
        QIcon icon3;
        icon3.addFile(QString::fromUtf8(":/icons/document-new.png"), QSize(), QIcon::Normal, QIcon::Off);
        actionNewGame->setIcon(icon3);
        actionOpenRace = new QAction(MainWindow);
        actionOpenRace->setObjectName(QString::fromUtf8("actionOpenRace"));
        actionOpenRace->setIcon(icon1);
        actionSaveRace = new QAction(MainWindow);
        actionSaveRace->setObjectName(QString::fromUtf8("actionSaveRace"));
        actionSaveRace->setIcon(icon2);
        actionNewRace = new QAction(MainWindow);
        actionNewRace->setObjectName(QString::fromUtf8("actionNewRace"));
        actionNewRace->setIcon(icon3);
        actionSaveGameAs = new QAction(MainWindow);
        actionSaveGameAs->setObjectName(QString::fromUtf8("actionSaveGameAs"));
        QIcon icon4;
        icon4.addFile(QString::fromUtf8(":/icons/document-save-as.png"), QSize(), QIcon::Normal, QIcon::Off);
        actionSaveGameAs->setIcon(icon4);
        actionSaveRaceAs = new QAction(MainWindow);
        actionSaveRaceAs->setObjectName(QString::fromUtf8("actionSaveRaceAs"));
        actionSaveRaceAs->setIcon(icon4);
        actionPreviewGame = new QAction(MainWindow);
        actionPreviewGame->setObjectName(QString::fromUtf8("actionPreviewGame"));
        QIcon icon5;
        icon5.addFile(QString::fromUtf8(":/icons/document-preview.png"), QSize(), QIcon::Normal, QIcon::Off);
        actionPreviewGame->setIcon(icon5);
        centralwidget = new QWidget(MainWindow);
        centralwidget->setObjectName(QString::fromUtf8("centralwidget"));
        horizontalLayout = new QHBoxLayout(centralwidget);
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        gameRaceTabWidget = new QTabWidget(centralwidget);
        gameRaceTabWidget->setObjectName(QString::fromUtf8("gameRaceTabWidget"));
        gameRaceTabWidget->setMinimumSize(QSize(516, 0));
        gameTab = new QWidget();
        gameTab->setObjectName(QString::fromUtf8("gameTab"));
        verticalLayout_3 = new QVBoxLayout(gameTab);
        verticalLayout_3->setObjectName(QString::fromUtf8("verticalLayout_3"));
        gameVBox = new QVBoxLayout();
        gameVBox->setObjectName(QString::fromUtf8("gameVBox"));
        gameVBox->setSizeConstraint(QLayout::SetMaximumSize);
        gameForm = new QFormLayout();
        gameForm->setObjectName(QString::fromUtf8("gameForm"));
        gameForm->setSizeConstraint(QLayout::SetDefaultConstraint);
        gameForm->setFieldGrowthPolicy(QFormLayout::ExpandingFieldsGrow);
        game_idLabel = new QLabel(gameTab);
        game_idLabel->setObjectName(QString::fromUtf8("game_idLabel"));
        QSizePolicy sizePolicy1(QSizePolicy::Preferred, QSizePolicy::Preferred);
        sizePolicy1.setHorizontalStretch(0);
        sizePolicy1.setVerticalStretch(0);
        sizePolicy1.setHeightForWidth(game_idLabel->sizePolicy().hasHeightForWidth());
        game_idLabel->setSizePolicy(sizePolicy1);

        gameForm->setWidget(0, QFormLayout::LabelRole, game_idLabel);

        game_idEdit = new QLineEdit(gameTab);
        game_idEdit->setObjectName(QString::fromUtf8("game_idEdit"));
        QSizePolicy sizePolicy2(QSizePolicy::Expanding, QSizePolicy::Preferred);
        sizePolicy2.setHorizontalStretch(0);
        sizePolicy2.setVerticalStretch(0);
        sizePolicy2.setHeightForWidth(game_idEdit->sizePolicy().hasHeightForWidth());
        game_idEdit->setSizePolicy(sizePolicy2);

        gameForm->setWidget(0, QFormLayout::FieldRole, game_idEdit);

        game_nameLabel = new QLabel(gameTab);
        game_nameLabel->setObjectName(QString::fromUtf8("game_nameLabel"));
        sizePolicy1.setHeightForWidth(game_nameLabel->sizePolicy().hasHeightForWidth());
        game_nameLabel->setSizePolicy(sizePolicy1);

        gameForm->setWidget(1, QFormLayout::LabelRole, game_nameLabel);

        game_nameEdit = new QLineEdit(gameTab);
        game_nameEdit->setObjectName(QString::fromUtf8("game_nameEdit"));
        sizePolicy2.setHeightForWidth(game_nameEdit->sizePolicy().hasHeightForWidth());
        game_nameEdit->setSizePolicy(sizePolicy2);

        gameForm->setWidget(1, QFormLayout::FieldRole, game_nameEdit);

        game_bookLabel = new QLabel(gameTab);
        game_bookLabel->setObjectName(QString::fromUtf8("game_bookLabel"));
        sizePolicy1.setHeightForWidth(game_bookLabel->sizePolicy().hasHeightForWidth());
        game_bookLabel->setSizePolicy(sizePolicy1);

        gameForm->setWidget(2, QFormLayout::LabelRole, game_bookLabel);

        game_bookEdit = new QLineEdit(gameTab);
        game_bookEdit->setObjectName(QString::fromUtf8("game_bookEdit"));
        sizePolicy2.setHeightForWidth(game_bookEdit->sizePolicy().hasHeightForWidth());
        game_bookEdit->setSizePolicy(sizePolicy2);

        gameForm->setWidget(2, QFormLayout::FieldRole, game_bookEdit);

        game_editionLabel = new QLabel(gameTab);
        game_editionLabel->setObjectName(QString::fromUtf8("game_editionLabel"));
        sizePolicy1.setHeightForWidth(game_editionLabel->sizePolicy().hasHeightForWidth());
        game_editionLabel->setSizePolicy(sizePolicy1);

        gameForm->setWidget(3, QFormLayout::LabelRole, game_editionLabel);

        game_editionEdit = new QLineEdit(gameTab);
        game_editionEdit->setObjectName(QString::fromUtf8("game_editionEdit"));
        sizePolicy2.setHeightForWidth(game_editionEdit->sizePolicy().hasHeightForWidth());
        game_editionEdit->setSizePolicy(sizePolicy2);

        gameForm->setWidget(3, QFormLayout::FieldRole, game_editionEdit);

        game_versionLabel = new QLabel(gameTab);
        game_versionLabel->setObjectName(QString::fromUtf8("game_versionLabel"));
        sizePolicy1.setHeightForWidth(game_versionLabel->sizePolicy().hasHeightForWidth());
        game_versionLabel->setSizePolicy(sizePolicy1);

        gameForm->setWidget(4, QFormLayout::LabelRole, game_versionLabel);

        game_versionEdit = new QLineEdit(gameTab);
        game_versionEdit->setObjectName(QString::fromUtf8("game_versionEdit"));
        sizePolicy2.setHeightForWidth(game_versionEdit->sizePolicy().hasHeightForWidth());
        game_versionEdit->setSizePolicy(sizePolicy2);

        gameForm->setWidget(4, QFormLayout::FieldRole, game_versionEdit);


        gameVBox->addLayout(gameForm);

        gameSaveBox = new WarButtonBox(gameTab);
        gameSaveBox->setObjectName(QString::fromUtf8("gameSaveBox"));
        gameSaveBox->setStandardButtons(QDialogButtonBox::Apply|QDialogButtonBox::Discard);

        gameVBox->addWidget(gameSaveBox);

        game_rulesGroupBox = new QGroupBox(gameTab);
        game_rulesGroupBox->setObjectName(QString::fromUtf8("game_rulesGroupBox"));
        QFont font;
        font.setPointSize(9);
        font.setBold(false);
        font.setWeight(50);
        game_rulesGroupBox->setFont(font);
        game_rulesGroupBox->setFlat(false);
        rulesVBox = new QVBoxLayout(game_rulesGroupBox);
        rulesVBox->setObjectName(QString::fromUtf8("rulesVBox"));
        game_rulesHBox = new QHBoxLayout();
        game_rulesHBox->setObjectName(QString::fromUtf8("game_rulesHBox"));
        game_ruleForm = new QFormLayout();
        game_ruleForm->setObjectName(QString::fromUtf8("game_ruleForm"));
        game_ruleForm->setFieldGrowthPolicy(QFormLayout::ExpandingFieldsGrow);
        game_ruleForm->setFormAlignment(Qt::AlignLeading|Qt::AlignLeft|Qt::AlignTop);
        game_rule_idLabel = new QLabel(game_rulesGroupBox);
        game_rule_idLabel->setObjectName(QString::fromUtf8("game_rule_idLabel"));

        game_ruleForm->setWidget(0, QFormLayout::LabelRole, game_rule_idLabel);

        game_rule_idEdit = new QLineEdit(game_rulesGroupBox);
        game_rule_idEdit->setObjectName(QString::fromUtf8("game_rule_idEdit"));

        game_ruleForm->setWidget(0, QFormLayout::FieldRole, game_rule_idEdit);

        game_rule_nameLabel = new QLabel(game_rulesGroupBox);
        game_rule_nameLabel->setObjectName(QString::fromUtf8("game_rule_nameLabel"));

        game_ruleForm->setWidget(1, QFormLayout::LabelRole, game_rule_nameLabel);

        game_rule_nameEdit = new QLineEdit(game_rulesGroupBox);
        game_rule_nameEdit->setObjectName(QString::fromUtf8("game_rule_nameEdit"));

        game_ruleForm->setWidget(1, QFormLayout::FieldRole, game_rule_nameEdit);

        game_rule_pageLabel = new QLabel(game_rulesGroupBox);
        game_rule_pageLabel->setObjectName(QString::fromUtf8("game_rule_pageLabel"));

        game_ruleForm->setWidget(2, QFormLayout::LabelRole, game_rule_pageLabel);

        game_rule_pageEdit = new QLineEdit(game_rulesGroupBox);
        game_rule_pageEdit->setObjectName(QString::fromUtf8("game_rule_pageEdit"));

        game_ruleForm->setWidget(2, QFormLayout::FieldRole, game_rule_pageEdit);

        game_rule_briefLabel = new QLabel(game_rulesGroupBox);
        game_rule_briefLabel->setObjectName(QString::fromUtf8("game_rule_briefLabel"));

        game_ruleForm->setWidget(3, QFormLayout::LabelRole, game_rule_briefLabel);

        game_rule_briefEdit = new QLineEdit(game_rulesGroupBox);
        game_rule_briefEdit->setObjectName(QString::fromUtf8("game_rule_briefEdit"));

        game_ruleForm->setWidget(3, QFormLayout::FieldRole, game_rule_briefEdit);

        game_rule_fullLabel = new QLabel(game_rulesGroupBox);
        game_rule_fullLabel->setObjectName(QString::fromUtf8("game_rule_fullLabel"));

        game_ruleForm->setWidget(4, QFormLayout::LabelRole, game_rule_fullLabel);

        game_ruleSaveBox = new WarButtonBox(game_rulesGroupBox);
        game_ruleSaveBox->setObjectName(QString::fromUtf8("game_ruleSaveBox"));
        game_ruleSaveBox->setStandardButtons(QDialogButtonBox::Apply|QDialogButtonBox::Discard);
        game_ruleSaveBox->setCenterButtons(false);

        game_ruleForm->setWidget(5, QFormLayout::FieldRole, game_ruleSaveBox);

        game_rule_fullEdit = new RefPlainTextEdit(game_rulesGroupBox);
        game_rule_fullEdit->setObjectName(QString::fromUtf8("game_rule_fullEdit"));

        game_ruleForm->setWidget(4, QFormLayout::FieldRole, game_rule_fullEdit);


        game_rulesHBox->addLayout(game_ruleForm);

        game_ruleListVBox = new QVBoxLayout();
        game_ruleListVBox->setObjectName(QString::fromUtf8("game_ruleListVBox"));
        game_ruleList = new QListWidget(game_rulesGroupBox);
        game_ruleList->setObjectName(QString::fromUtf8("game_ruleList"));
        QSizePolicy sizePolicy3(QSizePolicy::Maximum, QSizePolicy::Expanding);
        sizePolicy3.setHorizontalStretch(0);
        sizePolicy3.setVerticalStretch(0);
        sizePolicy3.setHeightForWidth(game_ruleList->sizePolicy().hasHeightForWidth());
        game_ruleList->setSizePolicy(sizePolicy3);
        game_ruleList->setMaximumSize(QSize(222, 16777215));

        game_ruleListVBox->addWidget(game_ruleList);

        game_ruleListActionsHBox = new QHBoxLayout();
        game_ruleListActionsHBox->setObjectName(QString::fromUtf8("game_ruleListActionsHBox"));
        game_ruleNewButton = new QPushButton(game_rulesGroupBox);
        game_ruleNewButton->setObjectName(QString::fromUtf8("game_ruleNewButton"));
        QIcon icon6;
        icon6.addFile(QString::fromUtf8(":/icons/list-add.png"), QSize(), QIcon::Normal, QIcon::Off);
        game_ruleNewButton->setIcon(icon6);

        game_ruleListActionsHBox->addWidget(game_ruleNewButton);

        game_ruleRemoveButton = new QPushButton(game_rulesGroupBox);
        game_ruleRemoveButton->setObjectName(QString::fromUtf8("game_ruleRemoveButton"));
        QIcon icon7;
        icon7.addFile(QString::fromUtf8(":/icons/list-remove.png"), QSize(), QIcon::Normal, QIcon::Off);
        game_ruleRemoveButton->setIcon(icon7);

        game_ruleListActionsHBox->addWidget(game_ruleRemoveButton);


        game_ruleListVBox->addLayout(game_ruleListActionsHBox);


        game_rulesHBox->addLayout(game_ruleListVBox);


        rulesVBox->addLayout(game_rulesHBox);


        gameVBox->addWidget(game_rulesGroupBox);


        verticalLayout_3->addLayout(gameVBox);

        gameRaceTabWidget->addTab(gameTab, QString());
        raceTab = new QWidget();
        raceTab->setObjectName(QString::fromUtf8("raceTab"));
        verticalLayout = new QVBoxLayout(raceTab);
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        raceForm = new QFormLayout();
        raceForm->setObjectName(QString::fromUtf8("raceForm"));
        raceForm->setSizeConstraint(QLayout::SetMaximumSize);
        raceForm->setFieldGrowthPolicy(QFormLayout::ExpandingFieldsGrow);
        race_idLabel = new QLabel(raceTab);
        race_idLabel->setObjectName(QString::fromUtf8("race_idLabel"));

        raceForm->setWidget(0, QFormLayout::LabelRole, race_idLabel);

        race_idEdit = new QLineEdit(raceTab);
        race_idEdit->setObjectName(QString::fromUtf8("race_idEdit"));

        raceForm->setWidget(0, QFormLayout::FieldRole, race_idEdit);

        race_nameLabel = new QLabel(raceTab);
        race_nameLabel->setObjectName(QString::fromUtf8("race_nameLabel"));

        raceForm->setWidget(1, QFormLayout::LabelRole, race_nameLabel);

        race_nameEdit = new QLineEdit(raceTab);
        race_nameEdit->setObjectName(QString::fromUtf8("race_nameEdit"));

        raceForm->setWidget(1, QFormLayout::FieldRole, race_nameEdit);

        race_bookLabel = new QLabel(raceTab);
        race_bookLabel->setObjectName(QString::fromUtf8("race_bookLabel"));

        raceForm->setWidget(2, QFormLayout::LabelRole, race_bookLabel);

        race_bookEdit = new QLineEdit(raceTab);
        race_bookEdit->setObjectName(QString::fromUtf8("race_bookEdit"));

        raceForm->setWidget(2, QFormLayout::FieldRole, race_bookEdit);

        race_editionLabel = new QLabel(raceTab);
        race_editionLabel->setObjectName(QString::fromUtf8("race_editionLabel"));

        raceForm->setWidget(3, QFormLayout::LabelRole, race_editionLabel);

        race_editionEdit = new QLineEdit(raceTab);
        race_editionEdit->setObjectName(QString::fromUtf8("race_editionEdit"));

        raceForm->setWidget(3, QFormLayout::FieldRole, race_editionEdit);

        race_versionLabel = new QLabel(raceTab);
        race_versionLabel->setObjectName(QString::fromUtf8("race_versionLabel"));

        raceForm->setWidget(4, QFormLayout::LabelRole, race_versionLabel);

        race_versionEdit = new QLineEdit(raceTab);
        race_versionEdit->setObjectName(QString::fromUtf8("race_versionEdit"));

        raceForm->setWidget(4, QFormLayout::FieldRole, race_versionEdit);

        race_gameLabel = new QLabel(raceTab);
        race_gameLabel->setObjectName(QString::fromUtf8("race_gameLabel"));

        raceForm->setWidget(5, QFormLayout::LabelRole, race_gameLabel);

        race_gameEdit = new QLineEdit(raceTab);
        race_gameEdit->setObjectName(QString::fromUtf8("race_gameEdit"));
        race_gameEdit->setEnabled(false);

        raceForm->setWidget(5, QFormLayout::FieldRole, race_gameEdit);


        verticalLayout->addLayout(raceForm);

        raceSaveBox = new WarButtonBox(raceTab);
        raceSaveBox->setObjectName(QString::fromUtf8("raceSaveBox"));
        raceSaveBox->setStandardButtons(QDialogButtonBox::Apply|QDialogButtonBox::Discard);

        verticalLayout->addWidget(raceSaveBox);

        race_tabWidget = new QTabWidget(raceTab);
        race_tabWidget->setObjectName(QString::fromUtf8("race_tabWidget"));
        race_rulesTab = new QWidget();
        race_rulesTab->setObjectName(QString::fromUtf8("race_rulesTab"));
        horizontalLayout_2 = new QHBoxLayout(race_rulesTab);
        horizontalLayout_2->setObjectName(QString::fromUtf8("horizontalLayout_2"));
        race_ruleForm = new QFormLayout();
        race_ruleForm->setObjectName(QString::fromUtf8("race_ruleForm"));
        race_ruleForm->setFieldGrowthPolicy(QFormLayout::ExpandingFieldsGrow);
        race_rule_idEdit = new QLineEdit(race_rulesTab);
        race_rule_idEdit->setObjectName(QString::fromUtf8("race_rule_idEdit"));

        race_ruleForm->setWidget(0, QFormLayout::FieldRole, race_rule_idEdit);

        race_rule_nameLabel = new QLabel(race_rulesTab);
        race_rule_nameLabel->setObjectName(QString::fromUtf8("race_rule_nameLabel"));

        race_ruleForm->setWidget(1, QFormLayout::LabelRole, race_rule_nameLabel);

        race_rule_nameEdit = new QLineEdit(race_rulesTab);
        race_rule_nameEdit->setObjectName(QString::fromUtf8("race_rule_nameEdit"));

        race_ruleForm->setWidget(1, QFormLayout::FieldRole, race_rule_nameEdit);

        race_rule_idLabel = new QLabel(race_rulesTab);
        race_rule_idLabel->setObjectName(QString::fromUtf8("race_rule_idLabel"));

        race_ruleForm->setWidget(0, QFormLayout::LabelRole, race_rule_idLabel);

        race_rule_pageLabel = new QLabel(race_rulesTab);
        race_rule_pageLabel->setObjectName(QString::fromUtf8("race_rule_pageLabel"));

        race_ruleForm->setWidget(2, QFormLayout::LabelRole, race_rule_pageLabel);

        race_rule_pageEdit = new QLineEdit(race_rulesTab);
        race_rule_pageEdit->setObjectName(QString::fromUtf8("race_rule_pageEdit"));

        race_ruleForm->setWidget(2, QFormLayout::FieldRole, race_rule_pageEdit);

        race_rule_briefLabel = new QLabel(race_rulesTab);
        race_rule_briefLabel->setObjectName(QString::fromUtf8("race_rule_briefLabel"));

        race_ruleForm->setWidget(3, QFormLayout::LabelRole, race_rule_briefLabel);

        race_rule_briefEdit = new QLineEdit(race_rulesTab);
        race_rule_briefEdit->setObjectName(QString::fromUtf8("race_rule_briefEdit"));

        race_ruleForm->setWidget(3, QFormLayout::FieldRole, race_rule_briefEdit);

        race_rule_fullLabel = new QLabel(race_rulesTab);
        race_rule_fullLabel->setObjectName(QString::fromUtf8("race_rule_fullLabel"));

        race_ruleForm->setWidget(4, QFormLayout::LabelRole, race_rule_fullLabel);

        race_rule_fullEdit = new RefPlainTextEdit(race_rulesTab);
        race_rule_fullEdit->setObjectName(QString::fromUtf8("race_rule_fullEdit"));

        race_ruleForm->setWidget(4, QFormLayout::FieldRole, race_rule_fullEdit);

        race_ruleSaveBox = new WarButtonBox(race_rulesTab);
        race_ruleSaveBox->setObjectName(QString::fromUtf8("race_ruleSaveBox"));
        race_ruleSaveBox->setStandardButtons(QDialogButtonBox::Apply|QDialogButtonBox::Discard);

        race_ruleForm->setWidget(5, QFormLayout::FieldRole, race_ruleSaveBox);


        horizontalLayout_2->addLayout(race_ruleForm);

        race_rulesVBox = new QVBoxLayout();
        race_rulesVBox->setObjectName(QString::fromUtf8("race_rulesVBox"));
        race_ruleList = new QListWidget(race_rulesTab);
        race_ruleList->setObjectName(QString::fromUtf8("race_ruleList"));
        sizePolicy3.setHeightForWidth(race_ruleList->sizePolicy().hasHeightForWidth());
        race_ruleList->setSizePolicy(sizePolicy3);
        race_ruleList->setMaximumSize(QSize(222, 16777215));

        race_rulesVBox->addWidget(race_ruleList);

        race_ruleListActionBox = new QHBoxLayout();
        race_ruleListActionBox->setObjectName(QString::fromUtf8("race_ruleListActionBox"));
        race_ruleNewButton = new QPushButton(race_rulesTab);
        race_ruleNewButton->setObjectName(QString::fromUtf8("race_ruleNewButton"));
        race_ruleNewButton->setIcon(icon6);

        race_ruleListActionBox->addWidget(race_ruleNewButton);

        race_ruleRemoveButton = new QPushButton(race_rulesTab);
        race_ruleRemoveButton->setObjectName(QString::fromUtf8("race_ruleRemoveButton"));
        race_ruleRemoveButton->setIcon(icon7);

        race_ruleListActionBox->addWidget(race_ruleRemoveButton);


        race_rulesVBox->addLayout(race_ruleListActionBox);


        horizontalLayout_2->addLayout(race_rulesVBox);

        race_tabWidget->addTab(race_rulesTab, QString());
        race_wargearsTab = new QWidget();
        race_wargearsTab->setObjectName(QString::fromUtf8("race_wargearsTab"));
        horizontalLayout_7 = new QHBoxLayout(race_wargearsTab);
        horizontalLayout_7->setObjectName(QString::fromUtf8("horizontalLayout_7"));
        verticalLayout_7 = new QVBoxLayout();
        verticalLayout_7->setObjectName(QString::fromUtf8("verticalLayout_7"));
        race_wargearForm = new QFormLayout();
        race_wargearForm->setObjectName(QString::fromUtf8("race_wargearForm"));
        race_wargearForm->setFieldGrowthPolicy(QFormLayout::ExpandingFieldsGrow);
        race_wargear_idLabel = new QLabel(race_wargearsTab);
        race_wargear_idLabel->setObjectName(QString::fromUtf8("race_wargear_idLabel"));

        race_wargearForm->setWidget(0, QFormLayout::LabelRole, race_wargear_idLabel);

        race_wargear_idEdit = new QLineEdit(race_wargearsTab);
        race_wargear_idEdit->setObjectName(QString::fromUtf8("race_wargear_idEdit"));

        race_wargearForm->setWidget(0, QFormLayout::FieldRole, race_wargear_idEdit);

        race_wargear_nameLabel = new QLabel(race_wargearsTab);
        race_wargear_nameLabel->setObjectName(QString::fromUtf8("race_wargear_nameLabel"));

        race_wargearForm->setWidget(1, QFormLayout::LabelRole, race_wargear_nameLabel);

        race_wargear_nameEdit = new QLineEdit(race_wargearsTab);
        race_wargear_nameEdit->setObjectName(QString::fromUtf8("race_wargear_nameEdit"));

        race_wargearForm->setWidget(1, QFormLayout::FieldRole, race_wargear_nameEdit);

        race_wargear_briefLabel = new QLabel(race_wargearsTab);
        race_wargear_briefLabel->setObjectName(QString::fromUtf8("race_wargear_briefLabel"));

        race_wargearForm->setWidget(2, QFormLayout::LabelRole, race_wargear_briefLabel);

        race_wargear_briefEdit = new QLineEdit(race_wargearsTab);
        race_wargear_briefEdit->setObjectName(QString::fromUtf8("race_wargear_briefEdit"));

        race_wargearForm->setWidget(2, QFormLayout::FieldRole, race_wargear_briefEdit);

        race_wargear_fullLabel = new QLabel(race_wargearsTab);
        race_wargear_fullLabel->setObjectName(QString::fromUtf8("race_wargear_fullLabel"));

        race_wargearForm->setWidget(3, QFormLayout::LabelRole, race_wargear_fullLabel);

        race_wargear_fullEdit = new RefPlainTextEdit(race_wargearsTab);
        race_wargear_fullEdit->setObjectName(QString::fromUtf8("race_wargear_fullEdit"));

        race_wargearForm->setWidget(3, QFormLayout::FieldRole, race_wargear_fullEdit);


        verticalLayout_7->addLayout(race_wargearForm);

        race_wargearSaveBox = new WarButtonBox(race_wargearsTab);
        race_wargearSaveBox->setObjectName(QString::fromUtf8("race_wargearSaveBox"));
        race_wargearSaveBox->setStandardButtons(QDialogButtonBox::Apply|QDialogButtonBox::Discard);

        verticalLayout_7->addWidget(race_wargearSaveBox);

        race_wargear_profilesGroup = new QGroupBox(race_wargearsTab);
        race_wargear_profilesGroup->setObjectName(QString::fromUtf8("race_wargear_profilesGroup"));
        race_wargear_profileVBox = new QVBoxLayout(race_wargear_profilesGroup);
        race_wargear_profileVBox->setObjectName(QString::fromUtf8("race_wargear_profileVBox"));
        race_wargear_profileList = new QListWidget(race_wargear_profilesGroup);
        race_wargear_profileList->setObjectName(QString::fromUtf8("race_wargear_profileList"));

        race_wargear_profileVBox->addWidget(race_wargear_profileList);

        race_wargear_profileActionBox = new QHBoxLayout();
        race_wargear_profileActionBox->setObjectName(QString::fromUtf8("race_wargear_profileActionBox"));
        race_wargear_profileNewButton = new QPushButton(race_wargear_profilesGroup);
        race_wargear_profileNewButton->setObjectName(QString::fromUtf8("race_wargear_profileNewButton"));
        race_wargear_profileNewButton->setIcon(icon6);

        race_wargear_profileActionBox->addWidget(race_wargear_profileNewButton);

        race_wargear_profileEditButton = new QPushButton(race_wargear_profilesGroup);
        race_wargear_profileEditButton->setObjectName(QString::fromUtf8("race_wargear_profileEditButton"));
        QIcon icon8;
        icon8.addFile(QString::fromUtf8(":/icons/document-edit.png"), QSize(), QIcon::Normal, QIcon::Off);
        race_wargear_profileEditButton->setIcon(icon8);

        race_wargear_profileActionBox->addWidget(race_wargear_profileEditButton);

        race_wargear_profileRemoveButton = new QPushButton(race_wargear_profilesGroup);
        race_wargear_profileRemoveButton->setObjectName(QString::fromUtf8("race_wargear_profileRemoveButton"));
        race_wargear_profileRemoveButton->setIcon(icon7);

        race_wargear_profileActionBox->addWidget(race_wargear_profileRemoveButton);


        race_wargear_profileVBox->addLayout(race_wargear_profileActionBox);


        verticalLayout_7->addWidget(race_wargear_profilesGroup);


        horizontalLayout_7->addLayout(verticalLayout_7);

        race_wargearVBox = new QVBoxLayout();
        race_wargearVBox->setObjectName(QString::fromUtf8("race_wargearVBox"));
        race_wargearList = new QListWidget(race_wargearsTab);
        race_wargearList->setObjectName(QString::fromUtf8("race_wargearList"));
        sizePolicy3.setHeightForWidth(race_wargearList->sizePolicy().hasHeightForWidth());
        race_wargearList->setSizePolicy(sizePolicy3);
        race_wargearList->setMaximumSize(QSize(222, 16777215));

        race_wargearVBox->addWidget(race_wargearList);

        race_wargearListActionBox = new QHBoxLayout();
        race_wargearListActionBox->setObjectName(QString::fromUtf8("race_wargearListActionBox"));
        race_wargearNewButton = new QPushButton(race_wargearsTab);
        race_wargearNewButton->setObjectName(QString::fromUtf8("race_wargearNewButton"));
        race_wargearNewButton->setIcon(icon6);

        race_wargearListActionBox->addWidget(race_wargearNewButton);

        race_wargearRemoveButton = new QPushButton(race_wargearsTab);
        race_wargearRemoveButton->setObjectName(QString::fromUtf8("race_wargearRemoveButton"));
        race_wargearRemoveButton->setIcon(icon7);

        race_wargearListActionBox->addWidget(race_wargearRemoveButton);


        race_wargearVBox->addLayout(race_wargearListActionBox);


        horizontalLayout_7->addLayout(race_wargearVBox);

        race_tabWidget->addTab(race_wargearsTab, QString());
        race_unitsTab = new QWidget();
        race_unitsTab->setObjectName(QString::fromUtf8("race_unitsTab"));
        horizontalLayout_4 = new QHBoxLayout(race_unitsTab);
        horizontalLayout_4->setObjectName(QString::fromUtf8("horizontalLayout_4"));
        verticalLayout_5 = new QVBoxLayout();
        verticalLayout_5->setObjectName(QString::fromUtf8("verticalLayout_5"));
        race_unitForm = new QFormLayout();
        race_unitForm->setObjectName(QString::fromUtf8("race_unitForm"));
        race_unitForm->setFieldGrowthPolicy(QFormLayout::ExpandingFieldsGrow);
        race_unit_idLabel = new QLabel(race_unitsTab);
        race_unit_idLabel->setObjectName(QString::fromUtf8("race_unit_idLabel"));

        race_unitForm->setWidget(0, QFormLayout::LabelRole, race_unit_idLabel);

        race_unit_idEdit = new QLineEdit(race_unitsTab);
        race_unit_idEdit->setObjectName(QString::fromUtf8("race_unit_idEdit"));

        race_unitForm->setWidget(0, QFormLayout::FieldRole, race_unit_idEdit);

        race_unit_nameLabel = new QLabel(race_unitsTab);
        race_unit_nameLabel->setObjectName(QString::fromUtf8("race_unit_nameLabel"));

        race_unitForm->setWidget(1, QFormLayout::LabelRole, race_unit_nameLabel);

        race_unit_nameEdit = new QLineEdit(race_unitsTab);
        race_unit_nameEdit->setObjectName(QString::fromUtf8("race_unit_nameEdit"));

        race_unitForm->setWidget(1, QFormLayout::FieldRole, race_unit_nameEdit);


        verticalLayout_5->addLayout(race_unitForm);

        race_unit_profileGrid = new QGridLayout();
        race_unit_profileGrid->setObjectName(QString::fromUtf8("race_unit_profileGrid"));
        race_unit_wsLabel = new QLabel(race_unitsTab);
        race_unit_wsLabel->setObjectName(QString::fromUtf8("race_unit_wsLabel"));
        race_unit_wsLabel->setAlignment(Qt::AlignCenter);

        race_unit_profileGrid->addWidget(race_unit_wsLabel, 1, 0, 1, 1);

        race_unit_bsLabel = new QLabel(race_unitsTab);
        race_unit_bsLabel->setObjectName(QString::fromUtf8("race_unit_bsLabel"));
        race_unit_bsLabel->setAlignment(Qt::AlignCenter);

        race_unit_profileGrid->addWidget(race_unit_bsLabel, 1, 1, 1, 1);

        race_unit_sLabel = new QLabel(race_unitsTab);
        race_unit_sLabel->setObjectName(QString::fromUtf8("race_unit_sLabel"));
        race_unit_sLabel->setAlignment(Qt::AlignCenter);

        race_unit_profileGrid->addWidget(race_unit_sLabel, 1, 2, 1, 1);

        race_unit_tLabel = new QLabel(race_unitsTab);
        race_unit_tLabel->setObjectName(QString::fromUtf8("race_unit_tLabel"));
        race_unit_tLabel->setAlignment(Qt::AlignCenter);

        race_unit_profileGrid->addWidget(race_unit_tLabel, 1, 3, 1, 1);

        race_unit_wLabel = new QLabel(race_unitsTab);
        race_unit_wLabel->setObjectName(QString::fromUtf8("race_unit_wLabel"));
        race_unit_wLabel->setAlignment(Qt::AlignCenter);

        race_unit_profileGrid->addWidget(race_unit_wLabel, 1, 4, 1, 1);

        race_unit_iLabel = new QLabel(race_unitsTab);
        race_unit_iLabel->setObjectName(QString::fromUtf8("race_unit_iLabel"));
        race_unit_iLabel->setAlignment(Qt::AlignCenter);

        race_unit_profileGrid->addWidget(race_unit_iLabel, 1, 5, 1, 1);

        race_unit_aLabel = new QLabel(race_unitsTab);
        race_unit_aLabel->setObjectName(QString::fromUtf8("race_unit_aLabel"));
        race_unit_aLabel->setAlignment(Qt::AlignCenter);

        race_unit_profileGrid->addWidget(race_unit_aLabel, 1, 6, 1, 1);

        race_unit_ldLabel = new QLabel(race_unitsTab);
        race_unit_ldLabel->setObjectName(QString::fromUtf8("race_unit_ldLabel"));
        race_unit_ldLabel->setAlignment(Qt::AlignCenter);

        race_unit_profileGrid->addWidget(race_unit_ldLabel, 1, 7, 1, 1);

        race_unit_svLabel = new QLabel(race_unitsTab);
        race_unit_svLabel->setObjectName(QString::fromUtf8("race_unit_svLabel"));
        race_unit_svLabel->setAlignment(Qt::AlignCenter);

        race_unit_profileGrid->addWidget(race_unit_svLabel, 1, 8, 1, 1);

        race_unit_isvLabel = new QLabel(race_unitsTab);
        race_unit_isvLabel->setObjectName(QString::fromUtf8("race_unit_isvLabel"));
        race_unit_isvLabel->setAlignment(Qt::AlignCenter);

        race_unit_profileGrid->addWidget(race_unit_isvLabel, 1, 9, 1, 1);

        race_unit_afLabel = new QLabel(race_unitsTab);
        race_unit_afLabel->setObjectName(QString::fromUtf8("race_unit_afLabel"));
        race_unit_afLabel->setAlignment(Qt::AlignCenter);

        race_unit_profileGrid->addWidget(race_unit_afLabel, 1, 10, 1, 1);

        race_unit_asLabel = new QLabel(race_unitsTab);
        race_unit_asLabel->setObjectName(QString::fromUtf8("race_unit_asLabel"));
        race_unit_asLabel->setAlignment(Qt::AlignCenter);

        race_unit_profileGrid->addWidget(race_unit_asLabel, 1, 11, 1, 1);

        race_unit_arLabel = new QLabel(race_unitsTab);
        race_unit_arLabel->setObjectName(QString::fromUtf8("race_unit_arLabel"));
        race_unit_arLabel->setAlignment(Qt::AlignCenter);

        race_unit_profileGrid->addWidget(race_unit_arLabel, 1, 12, 1, 1);

        race_unit_profile_armourLabel = new QLabel(race_unitsTab);
        race_unit_profile_armourLabel->setObjectName(QString::fromUtf8("race_unit_profile_armourLabel"));
        race_unit_profile_armourLabel->setAlignment(Qt::AlignCenter);

        race_unit_profileGrid->addWidget(race_unit_profile_armourLabel, 0, 10, 1, 3);

        race_unit_wsEdit = new QLineEdit(race_unitsTab);
        race_unit_wsEdit->setObjectName(QString::fromUtf8("race_unit_wsEdit"));
        race_unit_wsEdit->setAlignment(Qt::AlignCenter);

        race_unit_profileGrid->addWidget(race_unit_wsEdit, 2, 0, 1, 1);

        race_unit_bsEdit = new QLineEdit(race_unitsTab);
        race_unit_bsEdit->setObjectName(QString::fromUtf8("race_unit_bsEdit"));
        race_unit_bsEdit->setAlignment(Qt::AlignCenter);

        race_unit_profileGrid->addWidget(race_unit_bsEdit, 2, 1, 1, 1);

        race_unit_sEdit = new QLineEdit(race_unitsTab);
        race_unit_sEdit->setObjectName(QString::fromUtf8("race_unit_sEdit"));
        race_unit_sEdit->setAlignment(Qt::AlignCenter);

        race_unit_profileGrid->addWidget(race_unit_sEdit, 2, 2, 1, 1);

        race_unit_tEdit = new QLineEdit(race_unitsTab);
        race_unit_tEdit->setObjectName(QString::fromUtf8("race_unit_tEdit"));
        race_unit_tEdit->setAlignment(Qt::AlignCenter);

        race_unit_profileGrid->addWidget(race_unit_tEdit, 2, 3, 1, 1);

        race_unit_wEdit = new QLineEdit(race_unitsTab);
        race_unit_wEdit->setObjectName(QString::fromUtf8("race_unit_wEdit"));
        race_unit_wEdit->setAlignment(Qt::AlignCenter);

        race_unit_profileGrid->addWidget(race_unit_wEdit, 2, 4, 1, 1);

        race_unit_iEdit = new QLineEdit(race_unitsTab);
        race_unit_iEdit->setObjectName(QString::fromUtf8("race_unit_iEdit"));
        race_unit_iEdit->setAlignment(Qt::AlignCenter);

        race_unit_profileGrid->addWidget(race_unit_iEdit, 2, 5, 1, 1);

        race_unit_aEdit = new QLineEdit(race_unitsTab);
        race_unit_aEdit->setObjectName(QString::fromUtf8("race_unit_aEdit"));
        race_unit_aEdit->setAlignment(Qt::AlignCenter);

        race_unit_profileGrid->addWidget(race_unit_aEdit, 2, 6, 1, 1);

        race_unit_ldEdit = new QLineEdit(race_unitsTab);
        race_unit_ldEdit->setObjectName(QString::fromUtf8("race_unit_ldEdit"));
        race_unit_ldEdit->setAlignment(Qt::AlignCenter);

        race_unit_profileGrid->addWidget(race_unit_ldEdit, 2, 7, 1, 1);

        race_unit_svEdit = new QLineEdit(race_unitsTab);
        race_unit_svEdit->setObjectName(QString::fromUtf8("race_unit_svEdit"));
        race_unit_svEdit->setAlignment(Qt::AlignCenter);

        race_unit_profileGrid->addWidget(race_unit_svEdit, 2, 8, 1, 1);

        race_unit_isvEdit = new QLineEdit(race_unitsTab);
        race_unit_isvEdit->setObjectName(QString::fromUtf8("race_unit_isvEdit"));
        race_unit_isvEdit->setAlignment(Qt::AlignCenter);

        race_unit_profileGrid->addWidget(race_unit_isvEdit, 2, 9, 1, 1);

        race_unit_afEdit = new QLineEdit(race_unitsTab);
        race_unit_afEdit->setObjectName(QString::fromUtf8("race_unit_afEdit"));
        race_unit_afEdit->setAlignment(Qt::AlignCenter);

        race_unit_profileGrid->addWidget(race_unit_afEdit, 2, 10, 1, 1);

        race_unit_asEdit = new QLineEdit(race_unitsTab);
        race_unit_asEdit->setObjectName(QString::fromUtf8("race_unit_asEdit"));
        race_unit_asEdit->setAlignment(Qt::AlignCenter);

        race_unit_profileGrid->addWidget(race_unit_asEdit, 2, 11, 1, 1);

        race_unit_arEdit = new QLineEdit(race_unitsTab);
        race_unit_arEdit->setObjectName(QString::fromUtf8("race_unit_arEdit"));
        race_unit_arEdit->setAlignment(Qt::AlignCenter);

        race_unit_profileGrid->addWidget(race_unit_arEdit, 2, 12, 1, 1);


        verticalLayout_5->addLayout(race_unit_profileGrid);

        race_unitSaveBox = new WarButtonBox(race_unitsTab);
        race_unitSaveBox->setObjectName(QString::fromUtf8("race_unitSaveBox"));
        race_unitSaveBox->setStandardButtons(QDialogButtonBox::Apply|QDialogButtonBox::Discard);

        verticalLayout_5->addWidget(race_unitSaveBox);

        race_unit_wargearGroup = new QGroupBox(race_unitsTab);
        race_unit_wargearGroup->setObjectName(QString::fromUtf8("race_unit_wargearGroup"));
        race_unit_wargearVBox = new QVBoxLayout(race_unit_wargearGroup);
        race_unit_wargearVBox->setObjectName(QString::fromUtf8("race_unit_wargearVBox"));
        race_unit_wargearList = new QListWidget(race_unit_wargearGroup);
        race_unit_wargearList->setObjectName(QString::fromUtf8("race_unit_wargearList"));

        race_unit_wargearVBox->addWidget(race_unit_wargearList);

        race_unit_wargearActionBox = new QHBoxLayout();
        race_unit_wargearActionBox->setObjectName(QString::fromUtf8("race_unit_wargearActionBox"));
        race_unit_wargearAddButton = new QPushButton(race_unit_wargearGroup);
        race_unit_wargearAddButton->setObjectName(QString::fromUtf8("race_unit_wargearAddButton"));
        race_unit_wargearAddButton->setIcon(icon6);

        race_unit_wargearActionBox->addWidget(race_unit_wargearAddButton);

        race_unit_wargearEditButton = new QPushButton(race_unit_wargearGroup);
        race_unit_wargearEditButton->setObjectName(QString::fromUtf8("race_unit_wargearEditButton"));
        race_unit_wargearEditButton->setIcon(icon8);

        race_unit_wargearActionBox->addWidget(race_unit_wargearEditButton);

        race_unit_wargearRemoveButton = new QPushButton(race_unit_wargearGroup);
        race_unit_wargearRemoveButton->setObjectName(QString::fromUtf8("race_unit_wargearRemoveButton"));
        race_unit_wargearRemoveButton->setIcon(icon7);

        race_unit_wargearActionBox->addWidget(race_unit_wargearRemoveButton);


        race_unit_wargearVBox->addLayout(race_unit_wargearActionBox);


        verticalLayout_5->addWidget(race_unit_wargearGroup);

        race_unit_rulesGroup = new QGroupBox(race_unitsTab);
        race_unit_rulesGroup->setObjectName(QString::fromUtf8("race_unit_rulesGroup"));
        race_unit_rulesVBox = new QVBoxLayout(race_unit_rulesGroup);
        race_unit_rulesVBox->setObjectName(QString::fromUtf8("race_unit_rulesVBox"));
        race_unit_ruleList = new QListWidget(race_unit_rulesGroup);
        race_unit_ruleList->setObjectName(QString::fromUtf8("race_unit_ruleList"));

        race_unit_rulesVBox->addWidget(race_unit_ruleList);

        race_unit_rulesActionBox = new QHBoxLayout();
        race_unit_rulesActionBox->setObjectName(QString::fromUtf8("race_unit_rulesActionBox"));
        race_unit_ruleAddButton = new QPushButton(race_unit_rulesGroup);
        race_unit_ruleAddButton->setObjectName(QString::fromUtf8("race_unit_ruleAddButton"));
        race_unit_ruleAddButton->setIcon(icon6);

        race_unit_rulesActionBox->addWidget(race_unit_ruleAddButton);

        race_unit_ruleEditButton = new QPushButton(race_unit_rulesGroup);
        race_unit_ruleEditButton->setObjectName(QString::fromUtf8("race_unit_ruleEditButton"));
        race_unit_ruleEditButton->setIcon(icon8);

        race_unit_rulesActionBox->addWidget(race_unit_ruleEditButton);

        race_unit_ruleRemoveButton = new QPushButton(race_unit_rulesGroup);
        race_unit_ruleRemoveButton->setObjectName(QString::fromUtf8("race_unit_ruleRemoveButton"));
        race_unit_ruleRemoveButton->setIcon(icon7);

        race_unit_rulesActionBox->addWidget(race_unit_ruleRemoveButton);


        race_unit_rulesVBox->addLayout(race_unit_rulesActionBox);


        verticalLayout_5->addWidget(race_unit_rulesGroup);


        horizontalLayout_4->addLayout(verticalLayout_5);

        race_unitsVBox = new QVBoxLayout();
        race_unitsVBox->setObjectName(QString::fromUtf8("race_unitsVBox"));
        race_unitList = new QListWidget(race_unitsTab);
        race_unitList->setObjectName(QString::fromUtf8("race_unitList"));
        sizePolicy3.setHeightForWidth(race_unitList->sizePolicy().hasHeightForWidth());
        race_unitList->setSizePolicy(sizePolicy3);
        race_unitList->setMinimumSize(QSize(222, 0));
        race_unitList->setMaximumSize(QSize(222, 16777215));

        race_unitsVBox->addWidget(race_unitList);

        race_unitsActionBox = new QHBoxLayout();
        race_unitsActionBox->setObjectName(QString::fromUtf8("race_unitsActionBox"));
        race_unitNewButton = new QPushButton(race_unitsTab);
        race_unitNewButton->setObjectName(QString::fromUtf8("race_unitNewButton"));
        race_unitNewButton->setIcon(icon6);

        race_unitsActionBox->addWidget(race_unitNewButton);

        race_unitRemoveButton = new QPushButton(race_unitsTab);
        race_unitRemoveButton->setObjectName(QString::fromUtf8("race_unitRemoveButton"));
        race_unitRemoveButton->setIcon(icon7);

        race_unitsActionBox->addWidget(race_unitRemoveButton);


        race_unitsVBox->addLayout(race_unitsActionBox);


        horizontalLayout_4->addLayout(race_unitsVBox);

        race_tabWidget->addTab(race_unitsTab, QString());

        verticalLayout->addWidget(race_tabWidget);

        gameRaceTabWidget->addTab(raceTab, QString());

        horizontalLayout->addWidget(gameRaceTabWidget);

        MainWindow->setCentralWidget(centralwidget);
        menubar = new QMenuBar(MainWindow);
        menubar->setObjectName(QString::fromUtf8("menubar"));
        menubar->setGeometry(QRect(0, 0, 652, 21));
        menuGame = new QMenu(menubar);
        menuGame->setObjectName(QString::fromUtf8("menuGame"));
        menuRace = new QMenu(menubar);
        menuRace->setObjectName(QString::fromUtf8("menuRace"));
        MainWindow->setMenuBar(menubar);
        QWidget::setTabOrder(gameRaceTabWidget, game_idEdit);
        QWidget::setTabOrder(game_idEdit, game_nameEdit);
        QWidget::setTabOrder(game_nameEdit, game_bookEdit);
        QWidget::setTabOrder(game_bookEdit, game_editionEdit);
        QWidget::setTabOrder(game_editionEdit, game_versionEdit);
        QWidget::setTabOrder(game_versionEdit, gameSaveBox);
        QWidget::setTabOrder(gameSaveBox, game_rule_idEdit);
        QWidget::setTabOrder(game_rule_idEdit, game_rule_nameEdit);
        QWidget::setTabOrder(game_rule_nameEdit, game_rule_pageEdit);
        QWidget::setTabOrder(game_rule_pageEdit, game_rule_briefEdit);
        QWidget::setTabOrder(game_rule_briefEdit, game_rule_fullEdit);
        QWidget::setTabOrder(game_rule_fullEdit, game_ruleSaveBox);
        QWidget::setTabOrder(game_ruleSaveBox, game_ruleList);
        QWidget::setTabOrder(game_ruleList, game_ruleNewButton);
        QWidget::setTabOrder(game_ruleNewButton, game_ruleRemoveButton);
        QWidget::setTabOrder(game_ruleRemoveButton, race_idEdit);
        QWidget::setTabOrder(race_idEdit, race_nameEdit);
        QWidget::setTabOrder(race_nameEdit, race_bookEdit);
        QWidget::setTabOrder(race_bookEdit, race_editionEdit);
        QWidget::setTabOrder(race_editionEdit, race_versionEdit);
        QWidget::setTabOrder(race_versionEdit, race_gameEdit);
        QWidget::setTabOrder(race_gameEdit, raceSaveBox);
        QWidget::setTabOrder(raceSaveBox, race_tabWidget);
        QWidget::setTabOrder(race_tabWidget, race_rule_idEdit);
        QWidget::setTabOrder(race_rule_idEdit, race_rule_nameEdit);
        QWidget::setTabOrder(race_rule_nameEdit, race_rule_pageEdit);
        QWidget::setTabOrder(race_rule_pageEdit, race_rule_briefEdit);
        QWidget::setTabOrder(race_rule_briefEdit, race_rule_fullEdit);
        QWidget::setTabOrder(race_rule_fullEdit, race_ruleSaveBox);
        QWidget::setTabOrder(race_ruleSaveBox, race_ruleList);
        QWidget::setTabOrder(race_ruleList, race_ruleNewButton);
        QWidget::setTabOrder(race_ruleNewButton, race_ruleRemoveButton);
        QWidget::setTabOrder(race_ruleRemoveButton, race_wargear_idEdit);
        QWidget::setTabOrder(race_wargear_idEdit, race_wargear_nameEdit);
        QWidget::setTabOrder(race_wargear_nameEdit, race_wargear_briefEdit);
        QWidget::setTabOrder(race_wargear_briefEdit, race_wargear_fullEdit);
        QWidget::setTabOrder(race_wargear_fullEdit, race_wargearSaveBox);
        QWidget::setTabOrder(race_wargearSaveBox, race_wargear_profileList);
        QWidget::setTabOrder(race_wargear_profileList, race_wargear_profileNewButton);
        QWidget::setTabOrder(race_wargear_profileNewButton, race_wargear_profileEditButton);
        QWidget::setTabOrder(race_wargear_profileEditButton, race_wargear_profileRemoveButton);
        QWidget::setTabOrder(race_wargear_profileRemoveButton, race_wargearList);
        QWidget::setTabOrder(race_wargearList, race_wargearNewButton);
        QWidget::setTabOrder(race_wargearNewButton, race_wargearRemoveButton);
        QWidget::setTabOrder(race_wargearRemoveButton, race_unit_idEdit);
        QWidget::setTabOrder(race_unit_idEdit, race_unit_nameEdit);
        QWidget::setTabOrder(race_unit_nameEdit, race_unit_wsEdit);
        QWidget::setTabOrder(race_unit_wsEdit, race_unit_bsEdit);
        QWidget::setTabOrder(race_unit_bsEdit, race_unit_sEdit);
        QWidget::setTabOrder(race_unit_sEdit, race_unit_tEdit);
        QWidget::setTabOrder(race_unit_tEdit, race_unit_wEdit);
        QWidget::setTabOrder(race_unit_wEdit, race_unit_iEdit);
        QWidget::setTabOrder(race_unit_iEdit, race_unit_aEdit);
        QWidget::setTabOrder(race_unit_aEdit, race_unit_ldEdit);
        QWidget::setTabOrder(race_unit_ldEdit, race_unit_svEdit);
        QWidget::setTabOrder(race_unit_svEdit, race_unit_isvEdit);
        QWidget::setTabOrder(race_unit_isvEdit, race_unit_afEdit);
        QWidget::setTabOrder(race_unit_afEdit, race_unit_asEdit);
        QWidget::setTabOrder(race_unit_asEdit, race_unit_arEdit);
        QWidget::setTabOrder(race_unit_arEdit, race_unitSaveBox);
        QWidget::setTabOrder(race_unitSaveBox, race_unit_wargearList);
        QWidget::setTabOrder(race_unit_wargearList, race_unit_wargearAddButton);
        QWidget::setTabOrder(race_unit_wargearAddButton, race_unit_wargearEditButton);
        QWidget::setTabOrder(race_unit_wargearEditButton, race_unit_wargearRemoveButton);
        QWidget::setTabOrder(race_unit_wargearRemoveButton, race_unit_ruleList);
        QWidget::setTabOrder(race_unit_ruleList, race_unit_ruleAddButton);
        QWidget::setTabOrder(race_unit_ruleAddButton, race_unit_ruleEditButton);
        QWidget::setTabOrder(race_unit_ruleEditButton, race_unit_ruleRemoveButton);
        QWidget::setTabOrder(race_unit_ruleRemoveButton, race_unitList);
        QWidget::setTabOrder(race_unitList, race_unitNewButton);
        QWidget::setTabOrder(race_unitNewButton, race_unitRemoveButton);

        menubar->addAction(menuGame->menuAction());
        menubar->addAction(menuRace->menuAction());
        menuGame->addAction(actionOpenGame);
        menuGame->addAction(actionNewGame);
        menuGame->addAction(actionSaveGame);
        menuGame->addAction(actionSaveGameAs);
        menuGame->addAction(actionPreviewGame);
        menuRace->addAction(actionOpenRace);
        menuRace->addAction(actionNewRace);
        menuRace->addAction(actionSaveRace);
        menuRace->addAction(actionSaveRaceAs);

        retranslateUi(MainWindow);

        gameRaceTabWidget->setCurrentIndex(0);
        race_tabWidget->setCurrentIndex(0);


        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        actionOpenGame->setText(QApplication::translate("MainWindow", "Open Game", 0, QApplication::UnicodeUTF8));
        actionSaveGame->setText(QApplication::translate("MainWindow", "Save Game", 0, QApplication::UnicodeUTF8));
        actionNewGame->setText(QApplication::translate("MainWindow", "New Game", 0, QApplication::UnicodeUTF8));
        actionOpenRace->setText(QApplication::translate("MainWindow", "Open Race", 0, QApplication::UnicodeUTF8));
        actionSaveRace->setText(QApplication::translate("MainWindow", "Save Race", 0, QApplication::UnicodeUTF8));
        actionNewRace->setText(QApplication::translate("MainWindow", "New Race", 0, QApplication::UnicodeUTF8));
        actionSaveGameAs->setText(QApplication::translate("MainWindow", "Save Game As", 0, QApplication::UnicodeUTF8));
        actionSaveRaceAs->setText(QApplication::translate("MainWindow", "Save Race As", 0, QApplication::UnicodeUTF8));
        actionPreviewGame->setText(QApplication::translate("MainWindow", "Preview Game", 0, QApplication::UnicodeUTF8));
        game_idLabel->setText(QApplication::translate("MainWindow", "ID*", 0, QApplication::UnicodeUTF8));
        game_nameLabel->setText(QApplication::translate("MainWindow", "Name*", 0, QApplication::UnicodeUTF8));
        game_bookLabel->setText(QApplication::translate("MainWindow", "Book*", 0, QApplication::UnicodeUTF8));
        game_editionLabel->setText(QApplication::translate("MainWindow", "Edition*", 0, QApplication::UnicodeUTF8));
        game_versionLabel->setText(QApplication::translate("MainWindow", "File Version*", 0, QApplication::UnicodeUTF8));
        game_rulesGroupBox->setTitle(QApplication::translate("MainWindow", "Rules", 0, QApplication::UnicodeUTF8));
        game_rule_idLabel->setText(QApplication::translate("MainWindow", "ID*", 0, QApplication::UnicodeUTF8));
        game_rule_nameLabel->setText(QApplication::translate("MainWindow", "Name*", 0, QApplication::UnicodeUTF8));
        game_rule_pageLabel->setText(QApplication::translate("MainWindow", "Page*", 0, QApplication::UnicodeUTF8));
        game_rule_briefLabel->setText(QApplication::translate("MainWindow", "Brief*", 0, QApplication::UnicodeUTF8));
        game_rule_fullLabel->setText(QApplication::translate("MainWindow", "Full", 0, QApplication::UnicodeUTF8));
        game_ruleNewButton->setText(QApplication::translate("MainWindow", "New", 0, QApplication::UnicodeUTF8));
        game_ruleRemoveButton->setText(QApplication::translate("MainWindow", "Remove", 0, QApplication::UnicodeUTF8));
        gameRaceTabWidget->setTabText(gameRaceTabWidget->indexOf(gameTab), QApplication::translate("MainWindow", "Game", 0, QApplication::UnicodeUTF8));
        race_idLabel->setText(QApplication::translate("MainWindow", "ID*", 0, QApplication::UnicodeUTF8));
        race_nameLabel->setText(QApplication::translate("MainWindow", "Name*", 0, QApplication::UnicodeUTF8));
        race_bookLabel->setText(QApplication::translate("MainWindow", "Book*", 0, QApplication::UnicodeUTF8));
        race_editionLabel->setText(QApplication::translate("MainWindow", "Edition*", 0, QApplication::UnicodeUTF8));
        race_versionLabel->setText(QApplication::translate("MainWindow", "File Version*", 0, QApplication::UnicodeUTF8));
        race_gameLabel->setText(QApplication::translate("MainWindow", "Game", 0, QApplication::UnicodeUTF8));
        race_rule_nameLabel->setText(QApplication::translate("MainWindow", "Name*", 0, QApplication::UnicodeUTF8));
        race_rule_idLabel->setText(QApplication::translate("MainWindow", "ID*", 0, QApplication::UnicodeUTF8));
        race_rule_pageLabel->setText(QApplication::translate("MainWindow", "Page*", 0, QApplication::UnicodeUTF8));
        race_rule_briefLabel->setText(QApplication::translate("MainWindow", "Brief*", 0, QApplication::UnicodeUTF8));
        race_rule_fullLabel->setText(QApplication::translate("MainWindow", "Full", 0, QApplication::UnicodeUTF8));
        race_ruleNewButton->setText(QApplication::translate("MainWindow", "New", 0, QApplication::UnicodeUTF8));
        race_ruleRemoveButton->setText(QApplication::translate("MainWindow", "Remove", 0, QApplication::UnicodeUTF8));
        race_tabWidget->setTabText(race_tabWidget->indexOf(race_rulesTab), QApplication::translate("MainWindow", "Rules", 0, QApplication::UnicodeUTF8));
        race_wargear_idLabel->setText(QApplication::translate("MainWindow", "ID*", 0, QApplication::UnicodeUTF8));
        race_wargear_nameLabel->setText(QApplication::translate("MainWindow", "Name*", 0, QApplication::UnicodeUTF8));
        race_wargear_briefLabel->setText(QApplication::translate("MainWindow", "Brief", 0, QApplication::UnicodeUTF8));
        race_wargear_fullLabel->setText(QApplication::translate("MainWindow", "Full", 0, QApplication::UnicodeUTF8));
        race_wargear_profilesGroup->setTitle(QApplication::translate("MainWindow", "Profiles", 0, QApplication::UnicodeUTF8));
        race_wargear_profileNewButton->setText(QApplication::translate("MainWindow", "New", 0, QApplication::UnicodeUTF8));
        race_wargear_profileEditButton->setText(QApplication::translate("MainWindow", "Edit", 0, QApplication::UnicodeUTF8));
        race_wargear_profileRemoveButton->setText(QApplication::translate("MainWindow", "Remove", 0, QApplication::UnicodeUTF8));
        race_wargearNewButton->setText(QApplication::translate("MainWindow", "Add", 0, QApplication::UnicodeUTF8));
        race_wargearRemoveButton->setText(QApplication::translate("MainWindow", "Remove", 0, QApplication::UnicodeUTF8));
        race_tabWidget->setTabText(race_tabWidget->indexOf(race_wargearsTab), QApplication::translate("MainWindow", "Wargears", 0, QApplication::UnicodeUTF8));
        race_unit_idLabel->setText(QApplication::translate("MainWindow", "ID*", 0, QApplication::UnicodeUTF8));
        race_unit_nameLabel->setText(QApplication::translate("MainWindow", "Name*", 0, QApplication::UnicodeUTF8));
        race_unit_wsLabel->setText(QApplication::translate("MainWindow", "<!DOCTYPE HTML PUBLIC \"-//W3C//DTD HTML 4.0//EN\" \"http://www.w3.org/TR/REC-html40/strict.dtd\">\n"
"<html><head><meta name=\"qrichtext\" content=\"1\" /><style type=\"text/css\">\n"
"p, li { white-space: pre-wrap; }\n"
"</style></head><body style=\" font-family:'Ubuntu'; font-size:9pt; font-weight:400; font-style:normal;\">\n"
"<p style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\"><span style=\" font-weight:600;\">WS</span></p></body></html>", 0, QApplication::UnicodeUTF8));
        race_unit_bsLabel->setText(QApplication::translate("MainWindow", "<!DOCTYPE HTML PUBLIC \"-//W3C//DTD HTML 4.0//EN\" \"http://www.w3.org/TR/REC-html40/strict.dtd\">\n"
"<html><head><meta name=\"qrichtext\" content=\"1\" /><style type=\"text/css\">\n"
"p, li { white-space: pre-wrap; }\n"
"</style></head><body style=\" font-family:'Ubuntu'; font-size:9pt; font-weight:400; font-style:normal;\">\n"
"<p style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\"><span style=\" font-weight:600;\">BS</span></p></body></html>", 0, QApplication::UnicodeUTF8));
        race_unit_sLabel->setText(QApplication::translate("MainWindow", "<!DOCTYPE HTML PUBLIC \"-//W3C//DTD HTML 4.0//EN\" \"http://www.w3.org/TR/REC-html40/strict.dtd\">\n"
"<html><head><meta name=\"qrichtext\" content=\"1\" /><style type=\"text/css\">\n"
"p, li { white-space: pre-wrap; }\n"
"</style></head><body style=\" font-family:'Ubuntu'; font-size:9pt; font-weight:400; font-style:normal;\">\n"
"<p style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\"><span style=\" font-weight:600;\">S</span></p></body></html>", 0, QApplication::UnicodeUTF8));
        race_unit_tLabel->setText(QApplication::translate("MainWindow", "<!DOCTYPE HTML PUBLIC \"-//W3C//DTD HTML 4.0//EN\" \"http://www.w3.org/TR/REC-html40/strict.dtd\">\n"
"<html><head><meta name=\"qrichtext\" content=\"1\" /><style type=\"text/css\">\n"
"p, li { white-space: pre-wrap; }\n"
"</style></head><body style=\" font-family:'Ubuntu'; font-size:9pt; font-weight:400; font-style:normal;\">\n"
"<p style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\"><span style=\" font-weight:600;\">T</span></p></body></html>", 0, QApplication::UnicodeUTF8));
        race_unit_wLabel->setText(QApplication::translate("MainWindow", "<!DOCTYPE HTML PUBLIC \"-//W3C//DTD HTML 4.0//EN\" \"http://www.w3.org/TR/REC-html40/strict.dtd\">\n"
"<html><head><meta name=\"qrichtext\" content=\"1\" /><style type=\"text/css\">\n"
"p, li { white-space: pre-wrap; }\n"
"</style></head><body style=\" font-family:'Ubuntu'; font-size:9pt; font-weight:400; font-style:normal;\">\n"
"<p style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\"><span style=\" font-weight:600;\">W</span></p></body></html>", 0, QApplication::UnicodeUTF8));
        race_unit_iLabel->setText(QApplication::translate("MainWindow", "<!DOCTYPE HTML PUBLIC \"-//W3C//DTD HTML 4.0//EN\" \"http://www.w3.org/TR/REC-html40/strict.dtd\">\n"
"<html><head><meta name=\"qrichtext\" content=\"1\" /><style type=\"text/css\">\n"
"p, li { white-space: pre-wrap; }\n"
"</style></head><body style=\" font-family:'Ubuntu'; font-size:9pt; font-weight:400; font-style:normal;\">\n"
"<p style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\"><span style=\" font-weight:600;\">I</span></p></body></html>", 0, QApplication::UnicodeUTF8));
        race_unit_aLabel->setText(QApplication::translate("MainWindow", "<!DOCTYPE HTML PUBLIC \"-//W3C//DTD HTML 4.0//EN\" \"http://www.w3.org/TR/REC-html40/strict.dtd\">\n"
"<html><head><meta name=\"qrichtext\" content=\"1\" /><style type=\"text/css\">\n"
"p, li { white-space: pre-wrap; }\n"
"</style></head><body style=\" font-family:'Ubuntu'; font-size:9pt; font-weight:400; font-style:normal;\">\n"
"<p style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\"><span style=\" font-weight:600;\">A</span></p></body></html>", 0, QApplication::UnicodeUTF8));
        race_unit_ldLabel->setText(QApplication::translate("MainWindow", "<!DOCTYPE HTML PUBLIC \"-//W3C//DTD HTML 4.0//EN\" \"http://www.w3.org/TR/REC-html40/strict.dtd\">\n"
"<html><head><meta name=\"qrichtext\" content=\"1\" /><style type=\"text/css\">\n"
"p, li { white-space: pre-wrap; }\n"
"</style></head><body style=\" font-family:'Ubuntu'; font-size:9pt; font-weight:400; font-style:normal;\">\n"
"<p style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\"><span style=\" font-weight:600;\">Ld</span></p></body></html>", 0, QApplication::UnicodeUTF8));
        race_unit_svLabel->setText(QApplication::translate("MainWindow", "<!DOCTYPE HTML PUBLIC \"-//W3C//DTD HTML 4.0//EN\" \"http://www.w3.org/TR/REC-html40/strict.dtd\">\n"
"<html><head><meta name=\"qrichtext\" content=\"1\" /><style type=\"text/css\">\n"
"p, li { white-space: pre-wrap; }\n"
"</style></head><body style=\" font-family:'Ubuntu'; font-size:9pt; font-weight:400; font-style:normal;\">\n"
"<p style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\"><span style=\" font-weight:600;\">Sv</span></p></body></html>", 0, QApplication::UnicodeUTF8));
        race_unit_isvLabel->setText(QApplication::translate("MainWindow", "<!DOCTYPE HTML PUBLIC \"-//W3C//DTD HTML 4.0//EN\" \"http://www.w3.org/TR/REC-html40/strict.dtd\">\n"
"<html><head><meta name=\"qrichtext\" content=\"1\" /><style type=\"text/css\">\n"
"p, li { white-space: pre-wrap; }\n"
"</style></head><body style=\" font-family:'Ubuntu'; font-size:9pt; font-weight:400; font-style:normal;\">\n"
"<p style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\"><span style=\" font-weight:600;\">iSv</span></p></body></html>", 0, QApplication::UnicodeUTF8));
        race_unit_afLabel->setText(QApplication::translate("MainWindow", "<!DOCTYPE HTML PUBLIC \"-//W3C//DTD HTML 4.0//EN\" \"http://www.w3.org/TR/REC-html40/strict.dtd\">\n"
"<html><head><meta name=\"qrichtext\" content=\"1\" /><style type=\"text/css\">\n"
"p, li { white-space: pre-wrap; }\n"
"</style></head><body style=\" font-family:'Ubuntu'; font-size:9pt; font-weight:400; font-style:normal;\">\n"
"<p style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\"><span style=\" font-weight:600;\">F</span></p></body></html>", 0, QApplication::UnicodeUTF8));
        race_unit_asLabel->setText(QApplication::translate("MainWindow", "<!DOCTYPE HTML PUBLIC \"-//W3C//DTD HTML 4.0//EN\" \"http://www.w3.org/TR/REC-html40/strict.dtd\">\n"
"<html><head><meta name=\"qrichtext\" content=\"1\" /><style type=\"text/css\">\n"
"p, li { white-space: pre-wrap; }\n"
"</style></head><body style=\" font-family:'Ubuntu'; font-size:9pt; font-weight:400; font-style:normal;\">\n"
"<p style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\"><span style=\" font-weight:600;\">S</span></p></body></html>", 0, QApplication::UnicodeUTF8));
        race_unit_arLabel->setText(QApplication::translate("MainWindow", "<!DOCTYPE HTML PUBLIC \"-//W3C//DTD HTML 4.0//EN\" \"http://www.w3.org/TR/REC-html40/strict.dtd\">\n"
"<html><head><meta name=\"qrichtext\" content=\"1\" /><style type=\"text/css\">\n"
"p, li { white-space: pre-wrap; }\n"
"</style></head><body style=\" font-family:'Ubuntu'; font-size:9pt; font-weight:400; font-style:normal;\">\n"
"<p style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\"><span style=\" font-weight:600;\">R</span></p></body></html>", 0, QApplication::UnicodeUTF8));
        race_unit_profile_armourLabel->setText(QApplication::translate("MainWindow", "<!DOCTYPE HTML PUBLIC \"-//W3C//DTD HTML 4.0//EN\" \"http://www.w3.org/TR/REC-html40/strict.dtd\">\n"
"<html><head><meta name=\"qrichtext\" content=\"1\" /><style type=\"text/css\">\n"
"p, li { white-space: pre-wrap; }\n"
"</style></head><body style=\" font-family:'Ubuntu'; font-size:9pt; font-weight:400; font-style:normal;\">\n"
"<p style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\"><span style=\" font-weight:600;\">ARMOUR</span></p></body></html>", 0, QApplication::UnicodeUTF8));
        race_unit_wsEdit->setText(QString());
        race_unit_bsEdit->setText(QString());
        race_unit_wargearGroup->setTitle(QApplication::translate("MainWindow", "Wargears", 0, QApplication::UnicodeUTF8));
        race_unit_wargearAddButton->setText(QApplication::translate("MainWindow", "Add", 0, QApplication::UnicodeUTF8));
        race_unit_wargearEditButton->setText(QApplication::translate("MainWindow", "Edit", 0, QApplication::UnicodeUTF8));
        race_unit_wargearRemoveButton->setText(QApplication::translate("MainWindow", "Remove", 0, QApplication::UnicodeUTF8));
        race_unit_rulesGroup->setTitle(QApplication::translate("MainWindow", "Rules", 0, QApplication::UnicodeUTF8));
        race_unit_ruleAddButton->setText(QApplication::translate("MainWindow", "Add", 0, QApplication::UnicodeUTF8));
        race_unit_ruleEditButton->setText(QApplication::translate("MainWindow", "Edit", 0, QApplication::UnicodeUTF8));
        race_unit_ruleRemoveButton->setText(QApplication::translate("MainWindow", "Remove", 0, QApplication::UnicodeUTF8));
        race_unitNewButton->setText(QApplication::translate("MainWindow", "New", 0, QApplication::UnicodeUTF8));
        race_unitRemoveButton->setText(QApplication::translate("MainWindow", "Remove", 0, QApplication::UnicodeUTF8));
        race_tabWidget->setTabText(race_tabWidget->indexOf(race_unitsTab), QApplication::translate("MainWindow", "Units", 0, QApplication::UnicodeUTF8));
        gameRaceTabWidget->setTabText(gameRaceTabWidget->indexOf(raceTab), QApplication::translate("MainWindow", "Race", 0, QApplication::UnicodeUTF8));
        menuGame->setTitle(QApplication::translate("MainWindow", "&Game", 0, QApplication::UnicodeUTF8));
        menuRace->setTitle(QApplication::translate("MainWindow", "&Race", 0, QApplication::UnicodeUTF8));
        Q_UNUSED(MainWindow);
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // GAMERACEEDITJC2475_H
