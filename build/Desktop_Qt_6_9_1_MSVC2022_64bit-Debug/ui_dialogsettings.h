/********************************************************************************
** Form generated from reading UI file 'dialogsettings.ui'
**
** Created by: Qt User Interface Compiler version 6.9.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_DIALOGSETTINGS_H
#define UI_DIALOGSETTINGS_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QCheckBox>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QDialog>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QTabWidget>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_DialogSettings
{
public:
    QGridLayout *gridLayout;
    QVBoxLayout *verticalLayout;
    QTabWidget *tabWidget;
    QWidget *tab;
    QGridLayout *gridLayout_3;
    QGridLayout *gridLayout_2;
    QLabel *label_7;
    QCheckBox *chkUSSep;
    QLabel *label_3;
    QPushButton *btnPython;
    QComboBox *cmbThemes;
    QLabel *label_4;
    QComboBox *cmbComma;
    QLabel *label_5;
    QLineEdit *lePython;
    QLabel *label_6;
    QLabel *label_8;
    QLineEdit *leCustomSep;
    QWidget *tab_2;
    QComboBox *cmbFillMethod;
    QLabel *label;
    QLabel *label_2;
    QHBoxLayout *horizontalLayout;
    QSpacerItem *horizontalSpacer;
    QPushButton *pushButton;

    void setupUi(QDialog *DialogSettings)
    {
        if (DialogSettings->objectName().isEmpty())
            DialogSettings->setObjectName("DialogSettings");
        DialogSettings->resize(657, 479);
        QFont font;
        font.setPointSize(10);
        DialogSettings->setFont(font);
        gridLayout = new QGridLayout(DialogSettings);
        gridLayout->setObjectName("gridLayout");
        verticalLayout = new QVBoxLayout();
        verticalLayout->setObjectName("verticalLayout");
        tabWidget = new QTabWidget(DialogSettings);
        tabWidget->setObjectName("tabWidget");
        tabWidget->setFont(font);
        tab = new QWidget();
        tab->setObjectName("tab");
        gridLayout_3 = new QGridLayout(tab);
        gridLayout_3->setObjectName("gridLayout_3");
        gridLayout_2 = new QGridLayout();
        gridLayout_2->setObjectName("gridLayout_2");
        label_7 = new QLabel(tab);
        label_7->setObjectName("label_7");

        gridLayout_2->addWidget(label_7, 4, 0, 1, 1);

        chkUSSep = new QCheckBox(tab);
        chkUSSep->setObjectName("chkUSSep");

        gridLayout_2->addWidget(chkUSSep, 2, 1, 1, 1);

        label_3 = new QLabel(tab);
        label_3->setObjectName("label_3");

        gridLayout_2->addWidget(label_3, 0, 0, 1, 1);

        btnPython = new QPushButton(tab);
        btnPython->setObjectName("btnPython");

        gridLayout_2->addWidget(btnPython, 4, 2, 1, 1);

        cmbThemes = new QComboBox(tab);
        cmbThemes->addItem(QString());
        cmbThemes->addItem(QString());
        cmbThemes->addItem(QString());
        cmbThemes->addItem(QString());
        cmbThemes->setObjectName("cmbThemes");

        gridLayout_2->addWidget(cmbThemes, 1, 1, 1, 1);

        label_4 = new QLabel(tab);
        label_4->setObjectName("label_4");

        gridLayout_2->addWidget(label_4, 1, 0, 1, 1);

        cmbComma = new QComboBox(tab);
        cmbComma->addItem(QString());
        cmbComma->addItem(QString());
        cmbComma->setObjectName("cmbComma");

        gridLayout_2->addWidget(cmbComma, 0, 1, 1, 1);

        label_5 = new QLabel(tab);
        label_5->setObjectName("label_5");
        label_5->setWordWrap(true);

        gridLayout_2->addWidget(label_5, 1, 2, 1, 1);

        lePython = new QLineEdit(tab);
        lePython->setObjectName("lePython");

        gridLayout_2->addWidget(lePython, 4, 1, 1, 1);

        label_6 = new QLabel(tab);
        label_6->setObjectName("label_6");

        gridLayout_2->addWidget(label_6, 2, 0, 1, 1);

        label_8 = new QLabel(tab);
        label_8->setObjectName("label_8");

        gridLayout_2->addWidget(label_8, 3, 0, 1, 1);

        leCustomSep = new QLineEdit(tab);
        leCustomSep->setObjectName("leCustomSep");

        gridLayout_2->addWidget(leCustomSep, 3, 1, 1, 1);

        gridLayout_2->setColumnStretch(0, 2);
        gridLayout_2->setColumnStretch(1, 2);
        gridLayout_2->setColumnStretch(2, 1);

        gridLayout_3->addLayout(gridLayout_2, 0, 0, 1, 1);

        tabWidget->addTab(tab, QString());
        tab_2 = new QWidget();
        tab_2->setObjectName("tab_2");
        cmbFillMethod = new QComboBox(tab_2);
        cmbFillMethod->addItem(QString());
        cmbFillMethod->addItem(QString());
        cmbFillMethod->setObjectName("cmbFillMethod");
        cmbFillMethod->setGeometry(QRect(140, 20, 131, 22));
        label = new QLabel(tab_2);
        label->setObjectName("label");
        label->setGeometry(QRect(30, 20, 91, 21));
        label_2 = new QLabel(tab_2);
        label_2->setObjectName("label_2");
        label_2->setGeometry(QRect(340, 0, 261, 51));
        label_2->setWordWrap(true);
        tabWidget->addTab(tab_2, QString());

        verticalLayout->addWidget(tabWidget);


        gridLayout->addLayout(verticalLayout, 0, 0, 1, 1);

        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName("horizontalLayout");
        horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Policy::Expanding, QSizePolicy::Policy::Minimum);

        horizontalLayout->addItem(horizontalSpacer);

        pushButton = new QPushButton(DialogSettings);
        pushButton->setObjectName("pushButton");

        horizontalLayout->addWidget(pushButton);


        gridLayout->addLayout(horizontalLayout, 2, 0, 1, 1);


        retranslateUi(DialogSettings);

        tabWidget->setCurrentIndex(0);


        QMetaObject::connectSlotsByName(DialogSettings);
    } // setupUi

    void retranslateUi(QDialog *DialogSettings)
    {
        DialogSettings->setWindowTitle(QCoreApplication::translate("DialogSettings", "Settings", nullptr));
        label_7->setText(QCoreApplication::translate("DialogSettings", "Python executable", nullptr));
        chkUSSep->setText(QString());
        label_3->setText(QCoreApplication::translate("DialogSettings", "Preferred comma type", nullptr));
        btnPython->setText(QCoreApplication::translate("DialogSettings", "...", nullptr));
        cmbThemes->setItemText(0, QCoreApplication::translate("DialogSettings", "Light", nullptr));
        cmbThemes->setItemText(1, QCoreApplication::translate("DialogSettings", "Dark", nullptr));
        cmbThemes->setItemText(2, QCoreApplication::translate("DialogSettings", "Blue", nullptr));
        cmbThemes->setItemText(3, QCoreApplication::translate("DialogSettings", "Purple", nullptr));

        label_4->setText(QCoreApplication::translate("DialogSettings", "Colour theme", nullptr));
        cmbComma->setItemText(0, QCoreApplication::translate("DialogSettings", ",", nullptr));
        cmbComma->setItemText(1, QCoreApplication::translate("DialogSettings", ".", nullptr));

        label_5->setText(QCoreApplication::translate("DialogSettings", "The colour theme only applies when Nutil is restarted", nullptr));
        label_6->setText(QCoreApplication::translate("DialogSettings", "Add \"sep=;\" to csv files for US excel", nullptr));
        label_8->setText(QCoreApplication::translate("DialogSettings", "Custom separator:", nullptr));
        leCustomSep->setText(QCoreApplication::translate("DialogSettings", ";", nullptr));
        tabWidget->setTabText(tabWidget->indexOf(tab), QCoreApplication::translate("DialogSettings", "General", nullptr));
        cmbFillMethod->setItemText(0, QCoreApplication::translate("DialogSettings", "bfs", nullptr));
        cmbFillMethod->setItemText(1, QCoreApplication::translate("DialogSettings", "dfs", nullptr));

        label->setText(QCoreApplication::translate("DialogSettings", "Fill method", nullptr));
        label_2->setText(QCoreApplication::translate("DialogSettings", "dfs is original method, but crashes for large number of pixels", nullptr));
        tabWidget->setTabText(tabWidget->indexOf(tab_2), QCoreApplication::translate("DialogSettings", "Object Counter", nullptr));
        pushButton->setText(QCoreApplication::translate("DialogSettings", "Close", nullptr));
    } // retranslateUi

};

namespace Ui {
    class DialogSettings: public Ui_DialogSettings {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_DIALOGSETTINGS_H
