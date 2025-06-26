/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 6.9.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QListWidget>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenu>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QScrollArea>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QTabWidget>
#include <QtWidgets/QTextBrowser>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QAction *actionQuit;
    QAction *actionAbout_Nutil;
    QAction *actionSettings;
    QAction *actionGenerate_validation_data;
    QAction *actionNutil_Duplicator;
    QWidget *centralwidget;
    QVBoxLayout *verticalLayout_2;
    QHBoxLayout *horizontalLayout_3;
    QLabel *lblMain_2;
    QLabel *lblMain;
    QLabel *lblNewt;
    QTabWidget *tabMain;
    QWidget *tab_4;
    QGridLayout *gridLayout;
    QTextBrowser *textBrowser;
    QWidget *tab_2;
    QHBoxLayout *horizontalLayout;
    QVBoxLayout *verticalLayout;
    QGridLayout *gridLayout_4;
    QPushButton *btnNew;
    QPushButton *btnClearList;
    QPushButton *btnLoad_2;
    QPushButton *btnSaveAs;
    QPushButton *btnClearData;
    QPushButton *pushButton;
    QPushButton *btnSave;
    QListWidget *lstRecent;
    QScrollArea *scrollArea;
    QWidget *scrollAreaWidgetContents;
    QWidget *layoutWidget;
    QGridLayout *gridTemplate;
    QSpacerItem *horizontalSpacer;
    QWidget *tab;
    QGridLayout *gridLayout_3;
    QTextBrowser *txtInfo;
    QTextBrowser *txtError;
    QWidget *Output;
    QWidget *tab_3;
    QGridLayout *gridLayout_2;
    QTextBrowser *txtAbout;
    QHBoxLayout *horizontalLayout_2;
    QPushButton *btnStart;
    QPushButton *btnStop;
    QPushButton *btnUserdocs;
    QLineEdit *leProcessors;
    QLabel *label;
    QPushButton *btnOpenFolder;
    QHBoxLayout *horizontalLayout_4;
    QLabel *lblElapsedTime;
    QMenuBar *menubar;
    QMenu *menuTest;
    QMenu *menuJadda;
    QStatusBar *statusbar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName("MainWindow");
        MainWindow->resize(1404, 898);
        actionQuit = new QAction(MainWindow);
        actionQuit->setObjectName("actionQuit");
        actionAbout_Nutil = new QAction(MainWindow);
        actionAbout_Nutil->setObjectName("actionAbout_Nutil");
        actionSettings = new QAction(MainWindow);
        actionSettings->setObjectName("actionSettings");
        actionGenerate_validation_data = new QAction(MainWindow);
        actionGenerate_validation_data->setObjectName("actionGenerate_validation_data");
        actionNutil_Duplicator = new QAction(MainWindow);
        actionNutil_Duplicator->setObjectName("actionNutil_Duplicator");
        centralwidget = new QWidget(MainWindow);
        centralwidget->setObjectName("centralwidget");
        verticalLayout_2 = new QVBoxLayout(centralwidget);
        verticalLayout_2->setObjectName("verticalLayout_2");
        horizontalLayout_3 = new QHBoxLayout();
        horizontalLayout_3->setObjectName("horizontalLayout_3");
        lblMain_2 = new QLabel(centralwidget);
        lblMain_2->setObjectName("lblMain_2");
        QFont font;
        font.setFamilies({QString::fromUtf8("MS Shell Dlg 2")});
        font.setPointSize(32);
        lblMain_2->setFont(font);

        horizontalLayout_3->addWidget(lblMain_2);

        lblMain = new QLabel(centralwidget);
        lblMain->setObjectName("lblMain");
        QFont font1;
        font1.setPointSize(10);
        font1.setBold(true);
        lblMain->setFont(font1);

        horizontalLayout_3->addWidget(lblMain);

        lblNewt = new QLabel(centralwidget);
        lblNewt->setObjectName("lblNewt");
        lblNewt->setMaximumSize(QSize(199, 64));
        lblNewt->setScaledContents(true);

        horizontalLayout_3->addWidget(lblNewt);


        verticalLayout_2->addLayout(horizontalLayout_3);

        tabMain = new QTabWidget(centralwidget);
        tabMain->setObjectName("tabMain");
        tabMain->setMaximumSize(QSize(16777215, 600));
        QFont font2;
        font2.setPointSize(10);
        font2.setBold(false);
        tabMain->setFont(font2);
        tab_4 = new QWidget();
        tab_4->setObjectName("tab_4");
        gridLayout = new QGridLayout(tab_4);
        gridLayout->setObjectName("gridLayout");
        textBrowser = new QTextBrowser(tab_4);
        textBrowser->setObjectName("textBrowser");

        gridLayout->addWidget(textBrowser, 0, 0, 1, 1);

        tabMain->addTab(tab_4, QString());
        tab_2 = new QWidget();
        tab_2->setObjectName("tab_2");
        QSizePolicy sizePolicy(QSizePolicy::Policy::Preferred, QSizePolicy::Policy::Preferred);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(tab_2->sizePolicy().hasHeightForWidth());
        tab_2->setSizePolicy(sizePolicy);
        tab_2->setMaximumSize(QSize(16777215, 100000));
        horizontalLayout = new QHBoxLayout(tab_2);
        horizontalLayout->setObjectName("horizontalLayout");
        verticalLayout = new QVBoxLayout();
        verticalLayout->setObjectName("verticalLayout");
        gridLayout_4 = new QGridLayout();
        gridLayout_4->setObjectName("gridLayout_4");
        btnNew = new QPushButton(tab_2);
        btnNew->setObjectName("btnNew");
        btnNew->setFont(font1);

        gridLayout_4->addWidget(btnNew, 1, 0, 1, 1);

        btnClearList = new QPushButton(tab_2);
        btnClearList->setObjectName("btnClearList");
        btnClearList->setFont(font1);

        gridLayout_4->addWidget(btnClearList, 3, 1, 1, 1);

        btnLoad_2 = new QPushButton(tab_2);
        btnLoad_2->setObjectName("btnLoad_2");
        btnLoad_2->setFont(font1);

        gridLayout_4->addWidget(btnLoad_2, 1, 1, 1, 1);

        btnSaveAs = new QPushButton(tab_2);
        btnSaveAs->setObjectName("btnSaveAs");
        btnSaveAs->setFont(font1);

        gridLayout_4->addWidget(btnSaveAs, 2, 1, 1, 1);

        btnClearData = new QPushButton(tab_2);
        btnClearData->setObjectName("btnClearData");
        btnClearData->setFont(font1);

        gridLayout_4->addWidget(btnClearData, 3, 0, 1, 1);

        pushButton = new QPushButton(tab_2);
        pushButton->setObjectName("pushButton");
        pushButton->setFont(font1);

        gridLayout_4->addWidget(pushButton, 4, 1, 1, 1);

        btnSave = new QPushButton(tab_2);
        btnSave->setObjectName("btnSave");
        btnSave->setFont(font1);

        gridLayout_4->addWidget(btnSave, 2, 0, 1, 1);


        verticalLayout->addLayout(gridLayout_4);

        lstRecent = new QListWidget(tab_2);
        lstRecent->setObjectName("lstRecent");
        lstRecent->setFont(font1);

        verticalLayout->addWidget(lstRecent);


        horizontalLayout->addLayout(verticalLayout);

        scrollArea = new QScrollArea(tab_2);
        scrollArea->setObjectName("scrollArea");
        scrollArea->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOn);
        scrollArea->setWidgetResizable(true);
        scrollAreaWidgetContents = new QWidget();
        scrollAreaWidgetContents->setObjectName("scrollAreaWidgetContents");
        scrollAreaWidgetContents->setGeometry(QRect(0, 0, 1059, 390));
        layoutWidget = new QWidget(scrollAreaWidgetContents);
        layoutWidget->setObjectName("layoutWidget");
        layoutWidget->setGeometry(QRect(0, 0, 976, 513));
        gridTemplate = new QGridLayout(layoutWidget);
        gridTemplate->setObjectName("gridTemplate");
        gridTemplate->setContentsMargins(0, 0, 0, 0);
        horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Policy::Expanding, QSizePolicy::Policy::Minimum);

        gridTemplate->addItem(horizontalSpacer, 0, 1, 1, 1);

        scrollArea->setWidget(scrollAreaWidgetContents);

        horizontalLayout->addWidget(scrollArea);

        horizontalLayout->setStretch(0, 2);
        horizontalLayout->setStretch(1, 8);
        tabMain->addTab(tab_2, QString());
        tab = new QWidget();
        tab->setObjectName("tab");
        gridLayout_3 = new QGridLayout(tab);
        gridLayout_3->setObjectName("gridLayout_3");
        txtInfo = new QTextBrowser(tab);
        txtInfo->setObjectName("txtInfo");

        gridLayout_3->addWidget(txtInfo, 0, 0, 1, 1);

        txtError = new QTextBrowser(tab);
        txtError->setObjectName("txtError");

        gridLayout_3->addWidget(txtError, 1, 0, 1, 1);

        gridLayout_3->setRowStretch(0, 2);
        gridLayout_3->setRowStretch(1, 1);
        tabMain->addTab(tab, QString());
        Output = new QWidget();
        Output->setObjectName("Output");
        tabMain->addTab(Output, QString());
        tab_3 = new QWidget();
        tab_3->setObjectName("tab_3");
        gridLayout_2 = new QGridLayout(tab_3);
        gridLayout_2->setObjectName("gridLayout_2");
        txtAbout = new QTextBrowser(tab_3);
        txtAbout->setObjectName("txtAbout");
        QFont font3;
        font3.setFamilies({QString::fromUtf8("MS Sans Serif")});
        font3.setPointSize(10);
        font3.setBold(false);
        txtAbout->setFont(font3);
        txtAbout->setFocusPolicy(Qt::NoFocus);

        gridLayout_2->addWidget(txtAbout, 0, 0, 1, 1);

        tabMain->addTab(tab_3, QString());

        verticalLayout_2->addWidget(tabMain);

        horizontalLayout_2 = new QHBoxLayout();
        horizontalLayout_2->setObjectName("horizontalLayout_2");
        btnStart = new QPushButton(centralwidget);
        btnStart->setObjectName("btnStart");
        btnStart->setFont(font1);

        horizontalLayout_2->addWidget(btnStart);

        btnStop = new QPushButton(centralwidget);
        btnStop->setObjectName("btnStop");
        btnStop->setFont(font1);

        horizontalLayout_2->addWidget(btnStop);

        btnUserdocs = new QPushButton(centralwidget);
        btnUserdocs->setObjectName("btnUserdocs");
        btnUserdocs->setFont(font1);

        horizontalLayout_2->addWidget(btnUserdocs);

        leProcessors = new QLineEdit(centralwidget);
        leProcessors->setObjectName("leProcessors");

        horizontalLayout_2->addWidget(leProcessors);

        label = new QLabel(centralwidget);
        label->setObjectName("label");
        QFont font4;
        font4.setPointSize(10);
        label->setFont(font4);

        horizontalLayout_2->addWidget(label);

        btnOpenFolder = new QPushButton(centralwidget);
        btnOpenFolder->setObjectName("btnOpenFolder");

        horizontalLayout_2->addWidget(btnOpenFolder);


        verticalLayout_2->addLayout(horizontalLayout_2);

        horizontalLayout_4 = new QHBoxLayout();
        horizontalLayout_4->setObjectName("horizontalLayout_4");
        lblElapsedTime = new QLabel(centralwidget);
        lblElapsedTime->setObjectName("lblElapsedTime");
        lblElapsedTime->setFont(font4);

        horizontalLayout_4->addWidget(lblElapsedTime);


        verticalLayout_2->addLayout(horizontalLayout_4);

        verticalLayout_2->setStretch(0, 5);
        verticalLayout_2->setStretch(2, 1);
        verticalLayout_2->setStretch(3, 1);
        MainWindow->setCentralWidget(centralwidget);
        menubar = new QMenuBar(MainWindow);
        menubar->setObjectName("menubar");
        menubar->setGeometry(QRect(0, 0, 1404, 26));
        menuTest = new QMenu(menubar);
        menuTest->setObjectName("menuTest");
        menuJadda = new QMenu(menubar);
        menuJadda->setObjectName("menuJadda");
        MainWindow->setMenuBar(menubar);
        statusbar = new QStatusBar(MainWindow);
        statusbar->setObjectName("statusbar");
        MainWindow->setStatusBar(statusbar);

        menubar->addAction(menuTest->menuAction());
        menubar->addAction(menuJadda->menuAction());
        menuTest->addAction(actionSettings);
        menuTest->addAction(actionQuit);
        menuJadda->addAction(actionAbout_Nutil);

        retranslateUi(MainWindow);

        tabMain->setCurrentIndex(0);


        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QCoreApplication::translate("MainWindow", "NeSys Utilities", nullptr));
        actionQuit->setText(QCoreApplication::translate("MainWindow", "Quit", nullptr));
        actionAbout_Nutil->setText(QCoreApplication::translate("MainWindow", "About Nutil", nullptr));
        actionSettings->setText(QCoreApplication::translate("MainWindow", "Settings", nullptr));
        actionGenerate_validation_data->setText(QCoreApplication::translate("MainWindow", "Generate validation data", nullptr));
        actionNutil_Duplicator->setText(QCoreApplication::translate("MainWindow", "Nutil Duplicator", nullptr));
        lblMain_2->setText(QCoreApplication::translate("MainWindow", "Nutil ", nullptr));
        lblMain->setText(QCoreApplication::translate("MainWindow", "Version", nullptr));
        lblNewt->setText(QString());
        textBrowser->setHtml(QCoreApplication::translate("MainWindow", "<!DOCTYPE HTML PUBLIC \"-//W3C//DTD HTML 4.0//EN\" \"http://www.w3.org/TR/REC-html40/strict.dtd\">\n"
"<html><head><meta name=\"qrichtext\" content=\"1\" /><meta charset=\"utf-8\" /><style type=\"text/css\">\n"
"p, li { white-space: pre-wrap; }\n"
"hr { height: 1px; border-width: 0; }\n"
"li.unchecked::marker { content: \"\\2610\"; }\n"
"li.checked::marker { content: \"\\2612\"; }\n"
"</style></head><body style=\" font-family:'Segoe UI'; font-size:10pt; font-weight:400; font-style:normal;\">\n"
"<p style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\"><span style=\" font-family:'MS Shell Dlg 2'; font-weight:600;\">Nutil </span><span style=\" font-family:'MS Shell Dlg 2';\">is part of the </span><span style=\" font-family:'MS Shell Dlg 2'; font-weight:600;\">QUINT workflow,</span><span style=\" font-family:'MS Shell Dlg 2';\"> https://quint-workflow.readthedocs.io</span></p>\n"
"<p style=\"-qt-paragraph-type:empty; margin-top:0px; margin-bottom:0px"
                        "; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px; font-family:'MS Shell Dlg 2'; text-decoration: underline;\"><br /></p>\n"
"<p style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\"><span style=\" font-family:'MS Shell Dlg 2'; text-decoration: underline;\">To start:</span></p>\n"
"<p style=\"-qt-paragraph-type:empty; margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px; font-family:'MS Shell Dlg 2';\"><br /></p>\n"
"<p style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\"><span style=\" font-family:'MS Shell Dlg 2';\">1. Go to the </span><span style=\" font-family:'MS Shell Dlg 2'; font-weight:600;\">Operation</span><span style=\" font-family:'MS Shell Dlg 2';\"> tab. </span></p>\n"
"<p style=\"-qt-paragraph-type:empty; margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; "
                        "text-indent:0px; font-family:'MS Shell Dlg 2';\"><br /></p>\n"
"<p style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\"><span style=\" font-family:'MS Shell Dlg 2';\">2. Press </span><span style=\" font-family:'MS Shell Dlg 2'; font-weight:600;\">New</span><span style=\" font-family:'MS Shell Dlg 2';\"> and select </span><span style=\" font-family:'MS Shell Dlg 2'; font-weight:600;\">Quantifier.</span></p>\n"
"<p style=\"-qt-paragraph-type:empty; margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px; font-family:'MS Shell Dlg 2';\"><br /></p>\n"
"<p style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\"><span style=\" font-family:'MS Shell Dlg 2';\">3. Fill in the fields, press </span><span style=\" font-family:'MS Shell Dlg 2'; font-weight:600;\">Save As</span><span style=\" font-family:'MS Shell Dlg 2';\">, then </span><span style="
                        "\" font-family:'MS Shell Dlg 2'; font-weight:600;\">Start</span><span style=\" font-family:'MS Shell Dlg 2';\">.</span></p>\n"
"<p style=\"-qt-paragraph-type:empty; margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px; font-family:'MS Shell Dlg 2';\"><br /></p>\n"
"<p style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\"><span style=\" font-family:'MS Shell Dlg 2';\">4. The results are saved in the specified output folder.  </span></p>\n"
"<p style=\"-qt-paragraph-type:empty; margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px; font-family:'MS Shell Dlg 2';\"><br /></p>\n"
"<p style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\"><span style=\" font-family:'MS Shell Dlg 2'; text-decoration: underline;\">Operations:</span></p>\n"
"<p style=\"-qt-paragraph-type:empty; margin-top:0p"
                        "x; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px; font-family:'MS Shell Dlg 2';\"><br /></p>\n"
"<p style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\"><span style=\" font-family:'MS Shell Dlg 2'; font-weight:600;\">Quantifier</span><span style=\" font-family:'MS Shell Dlg 2';\">: Quantify labelling in the context of brain regions defined by a reference atlas. </span></p>\n"
"<p style=\"-qt-paragraph-type:empty; margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\"><br /></p>\n"
"<p style=\"-qt-paragraph-type:empty; margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\"><br /></p>\n"
"<p style=\"-qt-paragraph-type:empty; margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\"><br /></p></body></html>", nullptr));
        tabMain->setTabText(tabMain->indexOf(tab_4), QCoreApplication::translate("MainWindow", "Quick start", nullptr));
        btnNew->setText(QCoreApplication::translate("MainWindow", "New", nullptr));
        btnClearList->setText(QCoreApplication::translate("MainWindow", "Clear list", nullptr));
        btnLoad_2->setText(QCoreApplication::translate("MainWindow", "Load", nullptr));
        btnSaveAs->setText(QCoreApplication::translate("MainWindow", "Save As", nullptr));
        btnClearData->setText(QCoreApplication::translate("MainWindow", "Clear data", nullptr));
        pushButton->setText(QCoreApplication::translate("MainWindow", "Quit", nullptr));
        btnSave->setText(QCoreApplication::translate("MainWindow", "Save", nullptr));
        tabMain->setTabText(tabMain->indexOf(tab_2), QCoreApplication::translate("MainWindow", "Operation", nullptr));
        tabMain->setTabText(tabMain->indexOf(tab), QCoreApplication::translate("MainWindow", "Process output", nullptr));
        tabMain->setTabText(tabMain->indexOf(Output), QCoreApplication::translate("MainWindow", "Output", nullptr));
        txtAbout->setHtml(QCoreApplication::translate("MainWindow", "<!DOCTYPE HTML PUBLIC \"-//W3C//DTD HTML 4.0//EN\" \"http://www.w3.org/TR/REC-html40/strict.dtd\">\n"
"<html><head><meta name=\"qrichtext\" content=\"1\" /><meta charset=\"utf-8\" /><style type=\"text/css\">\n"
"p, li { white-space: pre-wrap; }\n"
"hr { height: 1px; border-width: 0; }\n"
"li.unchecked::marker { content: \"\\2610\"; }\n"
"li.checked::marker { content: \"\\2612\"; }\n"
"</style></head><body style=\" font-family:'MS Sans Serif'; font-size:10pt; font-weight:400; font-style:normal;\">\n"
"<p style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\"><span style=\" font-family:'MS Shell Dlg 2'; font-weight:600;\">About	</span></p>\n"
"<p style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\"><span style=\" font-family:'MS Shell Dlg 2';\">Nutil aims to simplify and streamline the mechanism of pre-and-post processing 2D brain image data from mouse and rat. It is an integral part of"
                        " the QUINT workflow for regional quantification of objects such as cells.</span></p>\n"
"<p style=\"-qt-paragraph-type:empty; margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px; font-family:'MS Shell Dlg 2';\"><br /></p>\n"
"<p style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\"><span style=\" font-family:'MS Shell Dlg 2'; font-weight:600;\">Developers		</span></p>\n"
"<p style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\"><span style=\" font-family:'MS Shell Dlg 2';\">Nutil is developed by the Nutil team at Neural Systems Laboratory, Institute of Basic Medical Sciences, University of Oslo. Nutil team: Nicolaas Groeneboom, Sharon C Yates, Maja A Puchades, Jan Bjaalie.</span></p>\n"
"<p style=\"-qt-paragraph-type:empty; margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px; fo"
                        "nt-family:'MS Shell Dlg 2'; font-weight:600;\"><br /></p>\n"
"<p style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\"><span style=\" font-family:'MS Shell Dlg 2'; font-weight:600;\">Licence</span></p>\n"
"<p style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\"><span style=\" font-family:'MS Shell Dlg 2';\">GNU General Public Licence version 3	</span></p>\n"
"<p style=\"-qt-paragraph-type:empty; margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px; font-family:'MS Shell Dlg 2';\"><br /></p>\n"
"<p style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\"><span style=\" font-family:'MS Shell Dlg 2'; font-weight:600;\">Funding</span></p>\n"
"<p style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\"><span style=\""
                        " font-family:'MS Shell Dlg 2';\">Nutil was developed with support from the EBRAINS research infrastructure with funding from the European Union's Horizon 2020 Framework Programme for Research and Innovation under the Framework Partnership Agreement No. 650003 (HBP FPA). 		</span></p>\n"
"<p style=\"-qt-paragraph-type:empty; margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px; font-family:'MS Shell Dlg 2';\"><br /></p>\n"
"<p style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\"><span style=\" font-family:'MS Shell Dlg 2'; font-weight:600;\">Documentation		</span><span style=\" font-family:'Times New Roman','serif'; font-size:12pt;\"> </span></p>\n"
"<p style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\"><span style=\" font-family:'Times New Roman','serif'; font-size:12pt;\">https://quint-workflow.readthedocs.io, https://nutil.rea"
                        "dthedocs.io</span></p>\n"
"<p style=\"-qt-paragraph-type:empty; margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px; font-family:'MS Shell Dlg 2';\"><br /></p>\n"
"<p style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\"><span style=\" font-family:'MS Shell Dlg 2'; font-weight:600;\">Report issues and user support</span></p>\n"
"<p style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\"><span style=\" font-family:'MS Shell Dlg 2';\">Report issues: https://github.com/Neural-Systems-at-UIO/nutil/issues</span></p>\n"
"<p style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\"><span style=\" font-family:'MS Shell Dlg 2';\">EBRAINS support: support@ebrains.eu</span></p>\n"
"<p style=\"-qt-paragraph-type:empty; margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px"
                        "; -qt-block-indent:0; text-indent:0px; font-family:'MS Shell Dlg 2';\"><br /></p>\n"
"<p style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\"><span style=\" font-family:'MS Shell Dlg 2'; font-weight:600;\">How to cite the tool</span></p>\n"
"<p style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\"><span style=\" font-family:'MS Shell Dlg 2';\">Nutil: Groeneboom NE, Yates SC, Puchades MA and Bjaalie JG (2020). Nutil: A Pre- and Post-processing Toolbox for Histological Rodent Brain Section Images. Front. Neuroinform. 14:37. doi: 10.3389/fninf.2020.00037</span></p>\n"
"<p style=\"-qt-paragraph-type:empty; margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px; font-family:'MS Shell Dlg 2'; font-weight:600;\"><br /></p>\n"
"<p style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0"
                        "px;\"><span style=\" font-family:'MS Shell Dlg 2';\">QUINT: Yates S.C., Groeneboom N.E., Coello C., Lichtenthaler S.F., Kuhn P.H., Demuth H.U., Hartlage-Rubsamen M., Rossner S., Leergaard T.B., Kreshuk A., Puchades M.A., Bjaalie J.G. (2019). QUINT: workflow for quantification and spatial analysis of features in histological images from rodent brain. Front of Neuroinform. doi: 10.3389/fninf. 2019.00075.</span></p>\n"
"<p style=\"-qt-paragraph-type:empty; margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px; font-family:'MS Shell Dlg 2';\"><br /></p>\n"
"<p style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\"><span style=\" font-family:'MS Shell Dlg 2'; font-weight:600;\">Nutil Quantifier can be used with the following reference atlases: </span></p>\n"
"<p style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\"><span style=\" font-fami"
                        "ly:'MS Shell Dlg 2';\">Allen Mouse Brain Atlas version 3 2015</span></p>\n"
"<p style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\"><span style=\" font-family:'MS Shell Dlg 2';\">Allen Mouse Brain Atlas version 3 2017</span></p>\n"
"<p style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\"><span style=\" font-family:'MS Shell Dlg 2';\">Kim Unified Mouse Atlas 2019</span></p>\n"
"<p style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\"><span style=\" font-family:'MS Shell Dlg 2';\">Waxholm Space Atlas of the Sprague Dawley rat v2</span></p>\n"
"<p style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\"><span style=\" font-family:'MS Shell Dlg 2';\">Waxholm Space Atlas of the Sprague Dawley rat v3</span></p>\n"
"<p style=\" margin-top:0px; margin-bottom:0px; mar"
                        "gin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\"><span style=\" font-family:'MS Shell Dlg 2';\">Waxholm Space Atlas of the Sprague Dawley rat v4</span></p>\n"
"<p style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\"><span style=\" font-family:'MS Shell Dlg 2';\">Developmental Mouse Brain Atlas (DeMBA)</span></p>\n"
"<p style=\"-qt-paragraph-type:empty; margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px; font-family:'MS Shell Dlg 2';\"><br /></p>\n"
"<p style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\"><span style=\" font-family:'MS Shell Dlg 2'; font-weight:600;\">Cite the reference atlases</span></p>\n"
"<p style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\"><span style=\" font-family:'MS Shell Dlg 2';\">Allen Mouse Brain Atlas: Wang et a"
                        "l., 202. The Allen Mouse Brain Common Coordinate Framework: A 3D Refererence Atlas. Cell.</span></p>\n"
"<p style=\"-qt-paragraph-type:empty; margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px; font-family:'MS Shell Dlg 2';\"><br /></p>\n"
"<p style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\"><span style=\" font-family:'MS Shell Dlg 2';\">Waxholm Space Atlas of the Sprague Dawley rat brain version 2, 3 and 4 (RRID: SCR_017124): Papp et al., NeuroImage 97, 374-386, 2014; Papp et al., NeuroImage 105, 561-562, 2015, Kjonigsen et al., NeuroImage 108, 441-449, 2015; Osen et al., NeuroImage 199, 38-56, 2019; Kleven et al., 2023.</span></p>\n"
"<p style=\"-qt-paragraph-type:empty; margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px; font-family:'MS Shell Dlg 2';\"><br /></p>\n"
"<p style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; m"
                        "argin-right:0px; -qt-block-indent:0; text-indent:0px;\"><span style=\" font-family:'MS Shell Dlg 2';\">Kim Unified Mouse Atlas 2019: Chon U et al., 2019. Enhanced and unified anatomical labeling for a common mouse brain atlas. Nat Commun.</span></p>\n"
"<p style=\"-qt-paragraph-type:empty; margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px; font-family:'MS Shell Dlg 2';\"><br /></p>\n"
"<p style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\">Developmental Mouse Brain Atlas</p>\n"
"<p style=\"-qt-paragraph-type:empty; margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px; font-family:'MS Shell Dlg 2';\"><br /></p></body></html>", nullptr));
        tabMain->setTabText(tabMain->indexOf(tab_3), QCoreApplication::translate("MainWindow", "About", nullptr));
        btnStart->setText(QCoreApplication::translate("MainWindow", "Start", nullptr));
        btnStop->setText(QCoreApplication::translate("MainWindow", "Stop", nullptr));
        btnUserdocs->setText(QCoreApplication::translate("MainWindow", "User documentation", nullptr));
        label->setText(QCoreApplication::translate("MainWindow", "# threads", nullptr));
        btnOpenFolder->setText(QCoreApplication::translate("MainWindow", "Open folder", nullptr));
        lblElapsedTime->setText(QCoreApplication::translate("MainWindow", "Elapsed time:", nullptr));
        menuTest->setTitle(QCoreApplication::translate("MainWindow", "File", nullptr));
        menuJadda->setTitle(QCoreApplication::translate("MainWindow", "Help", nullptr));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
