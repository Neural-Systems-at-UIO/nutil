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
#include "source/Validator/nutilvalidator.h"
#include "source/data.h"

#pragma comment(linker,"/STACK:18000000");
#pragma comment(linker,"/HEAP:18000000");



void setDarkPalette(QApplication& a) {
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
    Data::data.warningColor = Qt::yellow;
    a.setStyleSheet("QToolTip { color: #ffffff; background-color: #2a82da; border: 1px solid white; }");
}

void setSharonPalette(QApplication& a,float r, float g, float b) {
    a.setStyle(QStyleFactory::create("Fusion"));
    QPalette darkPalette;

    darkPalette.setColor(QPalette::Window, QColor(220*r,220*g,220*b));
//    darkPalette.setColor(QPalette::WindowText, Qt::black);
//    darkPalette.setColor(QPalette::Base, QColor(255*r,255*g,255*b));
    darkPalette.setColor(QPalette::AlternateBase, QColor(220*r,220*g,220*b));
  //  darkPalette.setColor(QPalette::ToolTipBase, Qt::black);
  //  darkPalette.setColor(QPalette::ToolTipText, Qt::black);
  //  darkPalette.setColor(QPalette::Text, Qt::black);
    darkPalette.setColor(QPalette::Button, QColor(220*r,220*g,220*b));
  //  darkPalette.setColor(QPalette::ButtonText, Qt::black);
  //  darkPalette.setColor(QPalette::BrightText, Qt::red);
  //  darkPalette.setColor(QPalette::Link, QColor(42*r, 130*g, 218*b));

    //darkPalette.setColor(QPalette::Highlight, QColor(42*r, 130*g, 218*b));
   // darkPalette.setColor(QPalette::HighlightedText, Qt::black);

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


void ApplyPalette(QString value, QApplication& a) {
    if (value.toLower()=="dark")
        setDarkPalette(a);
    else
    if (value.toLower()=="blue")
        setSharonPalette(a,0.7,0.8,1.0);
    else
    if (value.toLower()=="purple")
        setSharonPalette(a,1,0.7,0.9);



}


void CreateValidator() {
    NutilValidator v;
    v.CreateSegmentedImage("test",1280,1024, 16, QColor(0,0,255,255));
    v.CreateSlicedMask("test_mask.png",1280,1024, 0.5, Qt::white, Qt::black);
}


void SharonImageTest(int px, int py, int width, int height) {






    QImage img(1024,768, QImage::Format_ARGB32);
    img.fill(Qt::red);


    for (int y=0;y<height;y++) {
        for (int x=0;x<width;x++) {

            float ourBlue = (x/(float)width)*255;

            QColor col = QColor(0,0,0,255);
            col.setBlue(ourBlue);
            img.setPixelColor(x+px, y+py, col);
        }
    }



    img.save("sharonTest.png");
}


void Fractal() {
    NLIQImage img;
    img.Load("/Users/leuat/Downloads/uk.png");
    img.FractalAnalyze();
//    img.m_image = new QImage();
  //  img.m_image->Load("~/Downloads/uk.png");
    //QImage img("~/Downloads/uk.png");

}



int main(int argc, char *argv[])
{
#ifndef IGNORE_DOWNLOAD
    CheckVersion();
#endif


   // Fractal();

    //QImageReader::setAllocationLimit(4096);

    if (argc == 1)  {
        QApplication a(argc, argv);
        MainWindow window;
        ApplyPalette(window.m_settings.getString("color_theme"),a);
        window.show();
        return a.exec();
    }
    else {
        NutilApplication a(argc, argv);
        a.exec();
    }
}










