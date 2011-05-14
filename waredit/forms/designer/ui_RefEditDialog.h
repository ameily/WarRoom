/********************************************************************************
** Form generated from reading UI file 'RefEditDialogtX1858.ui'
**
** Created: Sat May 14 13:55:40 2011
**      by: Qt User Interface Compiler version 4.7.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef REFEDITDIALOGTX1858_H
#define REFEDITDIALOGTX1858_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QDialog>
#include <QtGui/QDialogButtonBox>
#include <QtGui/QHBoxLayout>
#include <QtGui/QHeaderView>
#include <QtGui/QLabel>
#include <QtGui/QLineEdit>
#include <QtGui/QListWidget>
#include <QtGui/QPushButton>
#include <QtGui/QVBoxLayout>
#include <widgets/SearchLineEdit.h>

QT_BEGIN_NAMESPACE

class Ui_RefEditDialog
{
public:
    QVBoxLayout *verticalLayout;
    QHBoxLayout *searchHBox;
    SearchLineEdit *searchEdit;
    QPushButton *searchButton;
    QListWidget *refList;
    QHBoxLayout *nameHBox;
    QLabel *nameLabel;
    QLineEdit *nameEdit;
    QDialogButtonBox *saveBox;

    void setupUi(QDialog *RefEditDialog)
    {
        if (RefEditDialog->objectName().isEmpty())
            RefEditDialog->setObjectName(QString::fromUtf8("RefEditDialog"));
        RefEditDialog->setWindowModality(Qt::ApplicationModal);
        RefEditDialog->resize(254, 294);
        verticalLayout = new QVBoxLayout(RefEditDialog);
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        searchHBox = new QHBoxLayout();
        searchHBox->setObjectName(QString::fromUtf8("searchHBox"));
        searchEdit = new SearchLineEdit(RefEditDialog);
        searchEdit->setObjectName(QString::fromUtf8("searchEdit"));

        searchHBox->addWidget(searchEdit);

        searchButton = new QPushButton(RefEditDialog);
        searchButton->setObjectName(QString::fromUtf8("searchButton"));
        QIcon icon;
        icon.addFile(QString::fromUtf8(":/icons/edit-find.png"), QSize(), QIcon::Normal, QIcon::Off);
        searchButton->setIcon(icon);

        searchHBox->addWidget(searchButton);


        verticalLayout->addLayout(searchHBox);

        refList = new QListWidget(RefEditDialog);
        refList->setObjectName(QString::fromUtf8("refList"));

        verticalLayout->addWidget(refList);

        nameHBox = new QHBoxLayout();
        nameHBox->setObjectName(QString::fromUtf8("nameHBox"));
        nameLabel = new QLabel(RefEditDialog);
        nameLabel->setObjectName(QString::fromUtf8("nameLabel"));

        nameHBox->addWidget(nameLabel);

        nameEdit = new QLineEdit(RefEditDialog);
        nameEdit->setObjectName(QString::fromUtf8("nameEdit"));

        nameHBox->addWidget(nameEdit);


        verticalLayout->addLayout(nameHBox);

        saveBox = new QDialogButtonBox(RefEditDialog);
        saveBox->setObjectName(QString::fromUtf8("saveBox"));
        saveBox->setStandardButtons(QDialogButtonBox::Cancel|QDialogButtonBox::Ok);

        verticalLayout->addWidget(saveBox);


        retranslateUi(RefEditDialog);

        QMetaObject::connectSlotsByName(RefEditDialog);
    } // setupUi

    void retranslateUi(QDialog *RefEditDialog)
    {
        RefEditDialog->setWindowTitle(QApplication::translate("RefEditDialog", "Edit Reference", 0, QApplication::UnicodeUTF8));
        searchEdit->setPlaceholderText(QApplication::translate("RefEditDialog", "Search", 0, QApplication::UnicodeUTF8));
        searchButton->setText(QApplication::translate("RefEditDialog", "Search", 0, QApplication::UnicodeUTF8));
        nameLabel->setText(QApplication::translate("RefEditDialog", "Name", 0, QApplication::UnicodeUTF8));
    } // retranslateUi

};

namespace Ui {
    class RefEditDialog: public Ui_RefEditDialog {};
} // namespace Ui

QT_END_NAMESPACE

#endif // REFEDITDIALOGTX1858_H
