#include <QApplication>
#include <QtPlugin>
#include "nutilapplication.h"
#include "mainwindow.h"
#include <xlnt/xlnt.hpp>
#include "source/unittest.h"
#include <QStyleFactory>
#include <QNetworkAccessManager>
#include <QNetworkRequest>
#include <QNetworkReply>
#include "source/util/updater.h"

#pragma comment(linker,"/STACK:2000000");
#pragma comment(linker,"/HEAP:2000000");


void setPalette(QApplication& a) {
    a.setStyle(QStyleFactory::create("Fusion"));

    QPalette darkPalette;
    darkPalette.setColor(QPalette::Window, QColor(53,53,53));
    darkPalette.setColor(QPalette::WindowText, Qt::white);
    darkPalette.setColor(QPalette::Base, QColor(25,25,25));
    darkPalette.setColor(QPalette::AlternateBase, QColor(53,53,53));
    darkPalette.setColor(QPalette::ToolTipBase, Qt::white);
    darkPalette.setColor(QPalette::ToolTipText, Qt::white);
    darkPalette.setColor(QPalette::Text, Qt::white);
    darkPalette.setColor(QPalette::Button, QColor(53,53,53));
    darkPalette.setColor(QPalette::ButtonText, Qt::white);
    darkPalette.setColor(QPalette::BrightText, Qt::red);
    darkPalette.setColor(QPalette::Link, QColor(42, 130, 218));

    darkPalette.setColor(QPalette::Highlight, QColor(42, 130, 218));
    darkPalette.setColor(QPalette::HighlightedText, Qt::black);

    a.setPalette(darkPalette);

    a.setStyleSheet("QToolTip { color: #ffffff; background-color: #2a82da; border: 1px solid white; }");


}

void CheckVersion() {
    Updater u;
    u.Initialize();
    if (!u.CheckVersionOK(MainWindow::Version)) {
        qDebug() << "New version of Nutil (" + QString::number(u.m_newVersion) +") released, downloading...";
        u.FetchNewVersion();
        exit(1);
    }
    else qDebug() << "No new version. Continuing.";
}


int main(int argc, char *argv[])
{




    CheckVersion();


    if (argc == 1)  {
        QApplication a(argc, argv);
        setPalette(a);
        MainWindow window;
        window.show();
        return a.exec();
    }
    else {
        NutilApplication a(argc, argv);
        a.exec();
    }
}










