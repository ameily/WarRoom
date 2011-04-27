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

#ifndef WARGEARPROFILEEDITMY2288_H
#define WARGEARPROFILEEDITMY2288_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QDialog>
#include <QtGui/QDialogButtonBox>
#include <QtGui/QFormLayout>
#include <QtGui/QGroupBox>
#include <QtGui/QHBoxLayout>
#include <QtGui/QHeaderView>
#include <QtGui/QLabel>
#include <QtGui/QLineEdit>
#include <QtGui/QListWidget>
#include <QtGui/QPushButton>
#include <QtGui/QVBoxLayout>

QT_BEGIN_NAMESPACE

class Ui_WargearProfileEditDialog
{
public:
    QVBoxLayout *verticalLayout;
    QFormLayout *formLayout;
    QLabel *wargearLabel;
    QLineEdit *wargearEdit;
    QLabel *nameLabel;
    QLineEdit *nameEdit;
    QLabel *rangeLabel;
    QLineEdit *rangeEdit;
    QLabel *strengthLabel;
    QLineEdit *strengthEdit;
    QLabel *apLabel;
    QLineEdit *apEdit;
    QGroupBox *rulesGroup;
    QVBoxLayout *verticalLayout_3;
    QListWidget *ruleList;
    QHBoxLayout *horizontalLayout;
    QPushButton *addButton;
    QPushButton *editButton;
    QPushButton *removeButton;
    QDialogButtonBox *saveBox;

    void setupUi(QDialog *WargearProfileEditDialog)
    {
        if (WargearProfileEditDialog->objectName().isEmpty())
            WargearProfileEditDialog->setObjectName(QString::fromUtf8("WargearProfileEditDialog"));
        WargearProfileEditDialog->resize(320, 421);
        verticalLayout = new QVBoxLayout(WargearProfileEditDialog);
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        formLayout = new QFormLayout();
        formLayout->setObjectName(QString::fromUtf8("formLayout"));
        formLayout->setFieldGrowthPolicy(QFormLayout::ExpandingFieldsGrow);
        wargearLabel = new QLabel(WargearProfileEditDialog);
        wargearLabel->setObjectName(QString::fromUtf8("wargearLabel"));

        formLayout->setWidget(0, QFormLayout::LabelRole, wargearLabel);

        wargearEdit = new QLineEdit(WargearProfileEditDialog);
        wargearEdit->setObjectName(QString::fromUtf8("wargearEdit"));
        wargearEdit->setEnabled(false);

        formLayout->setWidget(0, QFormLayout::FieldRole, wargearEdit);

        nameLabel = new QLabel(WargearProfileEditDialog);
        nameLabel->setObjectName(QString::fromUtf8("nameLabel"));

        formLayout->setWidget(1, QFormLayout::LabelRole, nameLabel);

        nameEdit = new QLineEdit(WargearProfileEditDialog);
        nameEdit->setObjectName(QString::fromUtf8("nameEdit"));

        formLayout->setWidget(1, QFormLayout::FieldRole, nameEdit);

        rangeLabel = new QLabel(WargearProfileEditDialog);
        rangeLabel->setObjectName(QString::fromUtf8("rangeLabel"));

        formLayout->setWidget(2, QFormLayout::LabelRole, rangeLabel);

        rangeEdit = new QLineEdit(WargearProfileEditDialog);
        rangeEdit->setObjectName(QString::fromUtf8("rangeEdit"));

        formLayout->setWidget(2, QFormLayout::FieldRole, rangeEdit);

        strengthLabel = new QLabel(WargearProfileEditDialog);
        strengthLabel->setObjectName(QString::fromUtf8("strengthLabel"));

        formLayout->setWidget(3, QFormLayout::LabelRole, strengthLabel);

        strengthEdit = new QLineEdit(WargearProfileEditDialog);
        strengthEdit->setObjectName(QString::fromUtf8("strengthEdit"));

        formLayout->setWidget(3, QFormLayout::FieldRole, strengthEdit);

        apLabel = new QLabel(WargearProfileEditDialog);
        apLabel->setObjectName(QString::fromUtf8("apLabel"));

        formLayout->setWidget(4, QFormLayout::LabelRole, apLabel);

        apEdit = new QLineEdit(WargearProfileEditDialog);
        apEdit->setObjectName(QString::fromUtf8("apEdit"));

        formLayout->setWidget(4, QFormLayout::FieldRole, apEdit);


        verticalLayout->addLayout(formLayout);

        rulesGroup = new QGroupBox(WargearProfileEditDialog);
        rulesGroup->setObjectName(QString::fromUtf8("rulesGroup"));
        verticalLayout_3 = new QVBoxLayout(rulesGroup);
        verticalLayout_3->setObjectName(QString::fromUtf8("verticalLayout_3"));
        ruleList = new QListWidget(rulesGroup);
        ruleList->setObjectName(QString::fromUtf8("ruleList"));

        verticalLayout_3->addWidget(ruleList);

        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        addButton = new QPushButton(rulesGroup);
        addButton->setObjectName(QString::fromUtf8("addButton"));
        QIcon icon;
        icon.addFile(QString::fromUtf8(":/icons/list-add.png"), QSize(), QIcon::Normal, QIcon::Off);
        addButton->setIcon(icon);

        horizontalLayout->addWidget(addButton);

        editButton = new QPushButton(rulesGroup);
        editButton->setObjectName(QString::fromUtf8("editButton"));
        QIcon icon1;
        icon1.addFile(QString::fromUtf8(":/icons/document-edit.png"), QSize(), QIcon::Normal, QIcon::Off);
        editButton->setIcon(icon1);

        horizontalLayout->addWidget(editButton);

        removeButton = new QPushButton(rulesGroup);
        removeButton->setObjectName(QString::fromUtf8("removeButton"));
        QIcon icon2;
        icon2.addFile(QString::fromUtf8(":/icons/list-remove.png"), QSize(), QIcon::Normal, QIcon::Off);
        removeButton->setIcon(icon2);

        horizontalLayout->addWidget(removeButton);


        verticalLayout_3->addLayout(horizontalLayout);

        saveBox = new QDialogButtonBox(rulesGroup);
        saveBox->setObjectName(QString::fromUtf8("saveBox"));
        saveBox->setStandardButtons(QDialogButtonBox::Cancel|QDialogButtonBox::Ok);

        verticalLayout_3->addWidget(saveBox);


        verticalLayout->addWidget(rulesGroup);


        retranslateUi(WargearProfileEditDialog);

        QMetaObject::connectSlotsByName(WargearProfileEditDialog);
    } // setupUi

    void retranslateUi(QDialog *WargearProfileEditDialog)
    {
        WargearProfileEditDialog->setWindowTitle(QApplication::translate("WargearProfileEditDialog", "Dialog", 0, QApplication::UnicodeUTF8));
        wargearLabel->setText(QApplication::translate("WargearProfileEditDialog", "Wargear", 0, QApplication::UnicodeUTF8));
        nameLabel->setText(QApplication::translate("WargearProfileEditDialog", "Name*", 0, QApplication::UnicodeUTF8));
        rangeLabel->setText(QApplication::translate("WargearProfileEditDialog", "Range*", 0, QApplication::UnicodeUTF8));
        strengthLabel->setText(QApplication::translate("WargearProfileEditDialog", "Strength*", 0, QApplication::UnicodeUTF8));
        apLabel->setText(QApplication::translate("WargearProfileEditDialog", "AP*", 0, QApplication::UnicodeUTF8));
        rulesGroup->setTitle(QApplication::translate("WargearProfileEditDialog", "Rules", 0, QApplication::UnicodeUTF8));
        addButton->setText(QApplication::translate("WargearProfileEditDialog", "Add", 0, QApplication::UnicodeUTF8));
        editButton->setText(QApplication::translate("WargearProfileEditDialog", "Edit", 0, QApplication::UnicodeUTF8));
        removeButton->setText(QApplication::translate("WargearProfileEditDialog", "Remove", 0, QApplication::UnicodeUTF8));
    } // retranslateUi

};

namespace Ui {
    class WargearProfileEditDialog: public Ui_WargearProfileEditDialog {};
} // namespace Ui

QT_END_NAMESPACE

#endif // WARGEARPROFILEEDITMY2288_H
