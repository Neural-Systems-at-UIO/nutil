#include "nutilapplication.h"
#include <stdio.h>
#include <iostream>
#include <QImage>
#include <QFile>
#include <QImageReader>
#include <QDebug>
#include "source/util/util.h"
#include <omp.h>
#include "source/util/counter.h"
//#include <tiffio.h>

using namespace std;

NutilApplication::NutilApplication(int argc, char *argv[])
{
    m_argc = argc;
    for (int i=0;i<argc;i++)
        m_argv.append(QString(argv[i]));
}

void NutilApplication::exec()
{
    bool ok = false;

    if (m_argc==1) {
        PrintUsage();
        exit(1);
    }
    QString cmd = m_argv[1];

    if (cmd == "rotate")
        ok = RotateTiff();

    if (!ok) {
        PrintUsage();
    }
}



bool NutilApplication::RotateTiff()
{
    QCoreApplication::addLibraryPath("imageformats");
    if (m_argc!=9) {
        return false;
    }
    QString inFile = m_argv[2];
    QString outFile = m_argv[3];
    float angle =  m_argv[4].toFloat();
    QColor background = QColor(m_argv[5].toFloat(), m_argv[6].toFloat(), m_argv[7].toFloat(),m_argv[8].toFloat());

    //cout << "infile: "  << inFile.toStdString() << endl;
    //cout << "angle: "  << angle << endl;
    qDebug() << "LOADING " << inFile;
    QImage image(inFile);
    if (image.isNull()) {
        qDebug() << "COULD NOT LOAD FILE";
        exit(1);
    }

    QImage copy(image.width(), image.height(),image.format());

    
    
    float centerx = (image.width()/2);
    float centery = (image.height()/2);

    //QRgb background = qRgb(0,0,255);
    Q_TIMER_START();


    Counter counter = Counter(image.width()*image.height(),"Rotating ", false);
#pragma omp parallel for
    for (int i=0;i<image.width();i++) {
//        cout<<"threads="<<omp_get_num_threads()<<endl;
        for (int j=0;j<image.height();j++) {

            float x = (i - centerx);
            float y = (j - centery);

            float xr = x*cos(angle)-y*sin(angle) + centerx;
            float yr = y*cos(angle)+x*sin(angle) + centery;
            QRgb color = background.rgba();
            if (xr>=0 && xr<copy.width() && yr>=0 && yr<copy.height()) {
                color = image.pixel((int)xr,(int)yr);
            }
            copy.setPixel(i,j,color);
            counter.Tick();
        }
    }
    cout << endl;
    Q_TIMER_ELAPSED("Rotation");
    QFile file(outFile);
    qDebug() << "Saving...";
    Q_TIMER_START();
    if (!copy.save(&file)) {
        qDebug() << "Image empty, cannot save ";
    }
    file.close();
    Q_TIMER_ELAPSED("Saving");

     return true;

}

void NutilApplication::PrintUsage()
{
    cout << "Nutil version 0.01" << endl << endl;
    cout << "Supported file formats: ";
    qDebug() << QImageReader::supportedImageFormats() << endl;

    cout << "Usage: "<< endl;
    cout << "  Nutil <command> <parameters>" << endl;
    cout << "  Commands: "<< endl;
    cout << "    rotate [img input] [img output] [angle in rad] [bg col r] [bg col g] [bg col b] [bg col a]";
    cout << "" << endl;
    cout << "" << endl;

}
