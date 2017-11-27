#include "nutilapplication.h"
#include <stdio.h>
#include <iostream>
#include <QImage>
#include <QFile>
#include <QImageReader>
#include <QImageWriter>
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

    if (cmd == "transform")
        ok = Transform();

    if (cmd == "transform_tiff")
        ok = RotateTiff();

    if (!ok) {
        PrintUsage();
    }
}



bool NutilApplication::RotateTiff()
{
    QCoreApplication::addLibraryPath("imageformats");
    if (m_argc!=10) {
        return false;
    }
    QString inFile = m_argv[2];
    QString outFile = m_argv[3];
    float angle =  m_argv[4].toFloat();
    float scale =  m_argv[5].toFloat();
    QColor background = QColor(m_argv[6].toFloat(), m_argv[7].toFloat(), m_argv[8].toFloat(),m_argv[9].toFloat());

    //cout << "infile: "  << inFile.toStdString() << endl;
    //cout << "angle: "  << angle << endl;
    qDebug() << "Loading heavy tiff file for transformation " << inFile;


    LTiff tif;
    if (!tif.Open(inFile)) {
        qDebug() << "Could not open tiff file!";
        exit(1);
    }
    LTiff otif;
    otif.New(outFile);
    otif.CreateFromMeta(tif);
    qDebug() << "Image size: " << tif.m_width << ", " <<  tif.m_height;
    qDebug() << "Image tiles:"<< tif.m_tileWidth << ", " << tif.m_tileHeight;

//    otif.CopyAllData(tif);
    otif.Transform(tif, angle, scale, 0,0, background);


    tif.Close();
    otif.Close();

    exit(1);
    
/*    float centerx = (image.width()/2);
    float centery = (image.height()/2);

    //QRgb background = qRgb(0,0,255);
    Q_TIMER_START();


    Counter counter = Counter(image.width()*image.height(),"Rotating ", false);
#pragma omp parallel for
    for (int i=0;i<image.width();i++) {
        //        cout<<"threads="<<omp_get_num_threads()<<endl;
        for (int j=0;j<image.height();j++) {

            float x = (i - centerx)*scale;
            float y = (j - centery)*scale;

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
    //QFile file(outFile);
    QImageWriter   imageWriter( outFile );

    //    imageWriter.setOptimize( true );
    //    imageWriter.setProgressive( true );
    if (outFile.contains("tif"))
        imageWriter.setCompression(1);

    qDebug() << "Saving...";
    Q_TIMER_START();
    if (imageWriter.write( copy )) {
        qDebug() << "Image empty, cannot save ";
    }
    //    imageWriter.close();
    Q_TIMER_ELAPSED("Saving");
*/
    return true;

}

bool NutilApplication::Transform()
{
    QCoreApplication::addLibraryPath("imageformats");
    if (m_argc!=10) {
        return false;
    }
    QString inFile = m_argv[2];
    QString outFile = m_argv[3];
    float angle =  m_argv[4].toFloat();
    float scale =  m_argv[5].toFloat();
    QColor background = QColor(m_argv[6].toFloat(), m_argv[7].toFloat(), m_argv[8].toFloat(),m_argv[9].toFloat());

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

            float x = (i - centerx)*scale;
            float y = (j - centery)*scale;

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
    //QFile file(outFile);
    QImageWriter   imageWriter( outFile );

    //    imageWriter.setOptimize( true );
    //    imageWriter.setProgressive( true );
    if (outFile.contains("tif"))
        imageWriter.setCompression(1);

    qDebug() << "Saving...";
    Q_TIMER_START();
    if (imageWriter.write( copy )) {
        qDebug() << "Image empty, cannot save ";
    }
    //    imageWriter.close();
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
    cout << "    transform [img input] [img output] [angle in rad] [scale] [bg col r] [bg col g] [bg col b] [bg col a]"<<endl;
    cout << "    transform_tiff [img input] [img output] [angle in rad] [scale] [bg col r] [bg col g] [bg col b] [bg col a]" << endl;
    cout << "" << endl;
    cout << "" << endl;

}
