/********************************************************************************
** Form generated from reading UI file 'dialogtiff.ui'
**
** Created by: Qt User Interface Compiler version 6.9.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_DIALOGTIFF_H
#define UI_DIALOGTIFF_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QDialog>
#include <QtWidgets/QLabel>
#include <QtWidgets/QProgressBar>
#include <QtWidgets/QPushButton>

QT_BEGIN_NAMESPACE

class Ui_DialogTiff
{
public:
    QPushButton *btnClose;
    QPushButton *btnOpen;
    QLabel *lblImage;
    QProgressBar *prgProgress;

    void setupUi(QDialog *DialogTiff)
    {
        if (DialogTiff->objectName().isEmpty())
            DialogTiff->setObjectName("DialogTiff");
        DialogTiff->resize(898, 607);
        btnClose = new QPushButton(DialogTiff);
        btnClose->setObjectName("btnClose");
        btnClose->setGeometry(QRect(770, 550, 93, 28));
        btnOpen = new QPushButton(DialogTiff);
        btnOpen->setObjectName("btnOpen");
        btnOpen->setGeometry(QRect(10, 550, 93, 31));
        lblImage = new QLabel(DialogTiff);
        lblImage->setObjectName("lblImage");
        lblImage->setGeometry(QRect(40, 40, 651, 471));
        lblImage->setScaledContents(true);
        prgProgress = new QProgressBar(DialogTiff);
        prgProgress->setObjectName("prgProgress");
        prgProgress->setGeometry(QRect(110, 550, 611, 23));
        prgProgress->setValue(100);

        retranslateUi(DialogTiff);

        QMetaObject::connectSlotsByName(DialogTiff);
    } // setupUi

    void retranslateUi(QDialog *DialogTiff)
    {
        DialogTiff->setWindowTitle(QCoreApplication::translate("DialogTiff", "Nutil Tiff Editor", nullptr));
        btnClose->setText(QCoreApplication::translate("DialogTiff", "Close", nullptr));
        btnOpen->setText(QCoreApplication::translate("DialogTiff", "Open", nullptr));
        lblImage->setText(QString());
    } // retranslateUi

};

namespace Ui {
    class DialogTiff: public Ui_DialogTiff {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_DIALOGTIFF_H
