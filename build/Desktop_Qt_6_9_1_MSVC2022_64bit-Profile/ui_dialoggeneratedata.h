/********************************************************************************
** Form generated from reading UI file 'dialoggeneratedata.ui'
**
** Created by: Qt User Interface Compiler version 6.9.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_DIALOGGENERATEDATA_H
#define UI_DIALOGGENERATEDATA_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QDialog>
#include <QtWidgets/QPushButton>

QT_BEGIN_NAMESPACE

class Ui_DialogGenerateData
{
public:
    QPushButton *btnClose;

    void setupUi(QDialog *DialogGenerateData)
    {
        if (DialogGenerateData->objectName().isEmpty())
            DialogGenerateData->setObjectName("DialogGenerateData");
        DialogGenerateData->resize(826, 517);
        btnClose = new QPushButton(DialogGenerateData);
        btnClose->setObjectName("btnClose");
        btnClose->setGeometry(QRect(670, 450, 92, 31));

        retranslateUi(DialogGenerateData);

        QMetaObject::connectSlotsByName(DialogGenerateData);
    } // setupUi

    void retranslateUi(QDialog *DialogGenerateData)
    {
        DialogGenerateData->setWindowTitle(QCoreApplication::translate("DialogGenerateData", "Generate data", nullptr));
        btnClose->setText(QCoreApplication::translate("DialogGenerateData", "Close", nullptr));
    } // retranslateUi

};

namespace Ui {
    class DialogGenerateData: public Ui_DialogGenerateData {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_DIALOGGENERATEDATA_H
