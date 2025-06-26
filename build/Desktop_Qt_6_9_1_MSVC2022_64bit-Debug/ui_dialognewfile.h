/********************************************************************************
** Form generated from reading UI file 'dialognewfile.ui'
**
** Created by: Qt User Interface Compiler version 6.9.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_DIALOGNEWFILE_H
#define UI_DIALOGNEWFILE_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QDialog>
#include <QtWidgets/QPushButton>

QT_BEGIN_NAMESPACE

class Ui_DialogNewFile
{
public:
    QPushButton *btnClose;
    QComboBox *cmbNew;
    QPushButton *btnOK;

    void setupUi(QDialog *DialogNewFile)
    {
        if (DialogNewFile->objectName().isEmpty())
            DialogNewFile->setObjectName("DialogNewFile");
        DialogNewFile->resize(457, 193);
        btnClose = new QPushButton(DialogNewFile);
        btnClose->setObjectName("btnClose");
        btnClose->setGeometry(QRect(330, 140, 80, 21));
        cmbNew = new QComboBox(DialogNewFile);
        cmbNew->addItem(QString());
        cmbNew->setObjectName("cmbNew");
        cmbNew->setGeometry(QRect(100, 60, 261, 31));
        QFont font;
        font.setPointSize(10);
        cmbNew->setFont(font);
        btnOK = new QPushButton(DialogNewFile);
        btnOK->setObjectName("btnOK");
        btnOK->setGeometry(QRect(240, 140, 80, 21));

        retranslateUi(DialogNewFile);

        QMetaObject::connectSlotsByName(DialogNewFile);
    } // setupUi

    void retranslateUi(QDialog *DialogNewFile)
    {
        DialogNewFile->setWindowTitle(QCoreApplication::translate("DialogNewFile", "Create new file", nullptr));
        btnClose->setText(QCoreApplication::translate("DialogNewFile", "Cancel", nullptr));
        cmbNew->setItemText(0, QCoreApplication::translate("DialogNewFile", "Quantifier", nullptr));

        btnOK->setText(QCoreApplication::translate("DialogNewFile", "Ok", nullptr));
    } // retranslateUi

};

namespace Ui {
    class DialogNewFile: public Ui_DialogNewFile {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_DIALOGNEWFILE_H
