/********************************************************************************
** Form generated from reading UI file 'ArmouryWindowfp5056.ui'
**
** Created: Sat May 14 23:27:34 2011
**      by: Qt User Interface Compiler version 4.7.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef ARMOURYWINDOWFP5056_H
#define ARMOURYWINDOWFP5056_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QHeaderView>
#include <QtGui/QMainWindow>
#include <QtGui/QMenu>
#include <QtGui/QMenuBar>
#include <QtGui/QVBoxLayout>
#include <QtGui/QWidget>
#include <widgets/WarPageViewer.h>

QT_BEGIN_NAMESPACE

class Ui_MainArmouryWindow
{
public:
    QAction *actionOpenFile;
    QAction *actionQuit;
    QWidget *centralwidget;
    QVBoxLayout *verticalLayout;
    WarPageViewer *pageViewer;
    QMenuBar *menubar;
    QMenu *menuF_ile;

    void setupUi(QMainWindow *MainArmouryWindow)
    {
        if (MainArmouryWindow->objectName().isEmpty())
            MainArmouryWindow->setObjectName(QString::fromUtf8("MainArmouryWindow"));
        MainArmouryWindow->resize(631, 545);
        QIcon icon;
        icon.addFile(QString::fromUtf8(":/icons/sword-preview.png"), QSize(), QIcon::Normal, QIcon::Off);
        MainArmouryWindow->setWindowIcon(icon);
        actionOpenFile = new QAction(MainArmouryWindow);
        actionOpenFile->setObjectName(QString::fromUtf8("actionOpenFile"));
        QIcon icon1;
        icon1.addFile(QString::fromUtf8(":/icons/document-open.png"), QSize(), QIcon::Normal, QIcon::Off);
        actionOpenFile->setIcon(icon1);
        actionQuit = new QAction(MainArmouryWindow);
        actionQuit->setObjectName(QString::fromUtf8("actionQuit"));
        QIcon icon2;
        icon2.addFile(QString::fromUtf8(":/icons/application-exit.png"), QSize(), QIcon::Normal, QIcon::Off);
        actionQuit->setIcon(icon2);
        centralwidget = new QWidget(MainArmouryWindow);
        centralwidget->setObjectName(QString::fromUtf8("centralwidget"));
        verticalLayout = new QVBoxLayout(centralwidget);
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        pageViewer = new WarPageViewer(centralwidget);
        pageViewer->setObjectName(QString::fromUtf8("pageViewer"));

        verticalLayout->addWidget(pageViewer);

        MainArmouryWindow->setCentralWidget(centralwidget);
        menubar = new QMenuBar(MainArmouryWindow);
        menubar->setObjectName(QString::fromUtf8("menubar"));
        menubar->setGeometry(QRect(0, 0, 631, 21));
        menuF_ile = new QMenu(menubar);
        menuF_ile->setObjectName(QString::fromUtf8("menuF_ile"));
        MainArmouryWindow->setMenuBar(menubar);

        menubar->addAction(menuF_ile->menuAction());
        menuF_ile->addAction(actionOpenFile);
        menuF_ile->addAction(actionQuit);

        retranslateUi(MainArmouryWindow);

        QMetaObject::connectSlotsByName(MainArmouryWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainArmouryWindow)
    {
        MainArmouryWindow->setWindowTitle(QString());
        actionOpenFile->setText(QApplication::translate("MainArmouryWindow", "&Open File", 0, QApplication::UnicodeUTF8));
        actionQuit->setText(QApplication::translate("MainArmouryWindow", "&Quit", 0, QApplication::UnicodeUTF8));
        menuF_ile->setTitle(QApplication::translate("MainArmouryWindow", "&File", 0, QApplication::UnicodeUTF8));
    } // retranslateUi

};

namespace Ui {
    class MainArmouryWindow: public Ui_MainArmouryWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // ARMOURYWINDOWFP5056_H
