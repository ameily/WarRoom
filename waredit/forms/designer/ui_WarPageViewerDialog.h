/********************************************************************************
** Form generated from reading UI file 'WarPageViewerDialogpb5883.ui'
**
** Created: Sat Apr 30 00:22:58 2011
**      by: Qt User Interface Compiler version 4.7.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef WARPAGEVIEWERDIALOGPB5883_H
#define WARPAGEVIEWERDIALOGPB5883_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QDialog>
#include <QtGui/QDialogButtonBox>
#include <QtGui/QHeaderView>
#include <QtGui/QVBoxLayout>
#include "WarPageViewer.h"

QT_BEGIN_NAMESPACE

class Ui_WarPageViewerDialog
{
public:
    QVBoxLayout *verticalLayout;
    WarPageViewer *tabWidget;
    QDialogButtonBox *buttonBox;

    void setupUi(QDialog *WarPageViewerDialog)
    {
        if (WarPageViewerDialog->objectName().isEmpty())
            WarPageViewerDialog->setObjectName(QString::fromUtf8("WarPageViewerDialog"));
        WarPageViewerDialog->resize(631, 545);
        verticalLayout = new QVBoxLayout(WarPageViewerDialog);
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        tabWidget = new WarPageViewer(WarPageViewerDialog);
        tabWidget->setObjectName(QString::fromUtf8("tabWidget"));

        verticalLayout->addWidget(tabWidget);

        buttonBox = new QDialogButtonBox(WarPageViewerDialog);
        buttonBox->setObjectName(QString::fromUtf8("buttonBox"));
        buttonBox->setStandardButtons(QDialogButtonBox::Ok);

        verticalLayout->addWidget(buttonBox);


        retranslateUi(WarPageViewerDialog);
        QObject::connect(buttonBox, SIGNAL(accepted()), WarPageViewerDialog, SLOT(accept()));

        QMetaObject::connectSlotsByName(WarPageViewerDialog);
    } // setupUi

    void retranslateUi(QDialog *WarPageViewerDialog)
    {
        WarPageViewerDialog->setWindowTitle(QApplication::translate("WarPageViewerDialog", "War Page Viewer", 0, QApplication::UnicodeUTF8));
    } // retranslateUi

};

namespace Ui {
    class WarPageViewerDialog: public Ui_WarPageViewerDialog {};
} // namespace Ui

QT_END_NAMESPACE

#endif // WARPAGEVIEWERDIALOGPB5883_H
