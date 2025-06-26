/********************************************************************************
** Form generated from reading UI file 'dialoghelp.ui'
**
** Created by: Qt User Interface Compiler version 6.9.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_DIALOGHELP_H
#define UI_DIALOGHELP_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QDialog>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QTextBrowser>
#include <QtWidgets/QVBoxLayout>

QT_BEGIN_NAMESPACE

class Ui_DialogHelp
{
public:
    QGridLayout *gridLayout;
    QVBoxLayout *verticalLayout;
    QTextBrowser *txtText;
    QHBoxLayout *horizontalLayout;
    QSpacerItem *horizontalSpacer;
    QPushButton *pushButton;

    void setupUi(QDialog *DialogHelp)
    {
        if (DialogHelp->objectName().isEmpty())
            DialogHelp->setObjectName("DialogHelp");
        DialogHelp->resize(784, 488);
        QFont font;
        font.setFamilies({QString::fromUtf8("MS Shell Dlg 2")});
        font.setPointSize(10);
        font.setBold(false);
        DialogHelp->setFont(font);
        gridLayout = new QGridLayout(DialogHelp);
        gridLayout->setObjectName("gridLayout");
        verticalLayout = new QVBoxLayout();
        verticalLayout->setObjectName("verticalLayout");
        txtText = new QTextBrowser(DialogHelp);
        txtText->setObjectName("txtText");

        verticalLayout->addWidget(txtText);

        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName("horizontalLayout");
        horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Policy::Expanding, QSizePolicy::Policy::Minimum);

        horizontalLayout->addItem(horizontalSpacer);

        pushButton = new QPushButton(DialogHelp);
        pushButton->setObjectName("pushButton");

        horizontalLayout->addWidget(pushButton);


        verticalLayout->addLayout(horizontalLayout);


        gridLayout->addLayout(verticalLayout, 0, 0, 1, 1);


        retranslateUi(DialogHelp);

        QMetaObject::connectSlotsByName(DialogHelp);
    } // setupUi

    void retranslateUi(QDialog *DialogHelp)
    {
        DialogHelp->setWindowTitle(QCoreApplication::translate("DialogHelp", "Nutil Help", nullptr));
        txtText->setHtml(QCoreApplication::translate("DialogHelp", "<!DOCTYPE HTML PUBLIC \"-//W3C//DTD HTML 4.0//EN\" \"http://www.w3.org/TR/REC-html40/strict.dtd\">\n"
"<html><head><meta name=\"qrichtext\" content=\"1\" /><style type=\"text/css\">\n"
"p, li { white-space: pre-wrap; }\n"
"</style></head><body style=\" font-family:'MS Shell Dlg 2'; font-size:10pt; font-weight:400; font-style:normal;\">\n"
"<p style=\"-qt-paragraph-type:empty; margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px; font-family:'MS Shell Dlg 2';\"><br /></p></body></html>", nullptr));
        pushButton->setText(QCoreApplication::translate("DialogHelp", "Close", nullptr));
    } // retranslateUi

};

namespace Ui {
    class DialogHelp: public Ui_DialogHelp {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_DIALOGHELP_H
