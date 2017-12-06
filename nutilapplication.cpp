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
#include "source/nauto.h"

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

    if (cmd == "batch") {
        ok = Batch();
    }

    if (!ok) {
        PrintUsage();
    }
}



bool NutilApplication::RotateTiff()
{
    QCoreApplication::addLibraryPath("imageformats");
    if (m_argc!=11) {
        return false;
    }
    QString inFile = m_argv[2];
    QString outFile = m_argv[3];
    QString compression = m_argv[4];
    float angle =  m_argv[5].toFloat();
    float scale =  m_argv[6].toFloat();
    QColor background = QColor(m_argv[7].toFloat(), m_argv[8].toFloat(), m_argv[9].toFloat(),m_argv[10].toFloat());

    qDebug() << "Loading tiled tiff file:" << inFile;


    LTiff tif;
    if (!tif.Open(inFile)) {
        qDebug() << "Could not open tiff file! Please check the filename and try again.";
        exit(1);
    }
    tif.PrintImageInfo();
    if (!TIFFIsTiled(tif.m_tif)) {
        qDebug() << "Error: this tiff file is not tiled. Please use the other transformation method for non-tiled tiffs.";
        exit(1);
    }


    if (!(tif.m_samplesPerPixel==3 && tif.m_bitsPerSample==8)) {
        qDebug() << "Error! For now, lutil only supports big tiffs with RGB format";
        exit(1);
    }

    tif.SetupBuffers();

    int writeCompression = 0;
    if (compression.toLower()=="jpeg")
        writeCompression = 7;
    if (compression.toLower()=="lzw")
        writeCompression = 5;
    if (compression.toLower()=="none")
        writeCompression = 1;

    if (writeCompression==0) {
        qDebug() << "Unknown compression format. Must be either jpeg, lzw or none.";
        exit(1);
    }

    LTiff otif;
    otif.New(outFile);
    otif.CreateFromMeta(tif, writeCompression);


    qDebug() << "Transforming to file " << outFile << " with compression " << tif.m_compressionTypes[writeCompression];
    otif.Transform(tif, angle, scale, 0,0, background);

    tif.Close();
    otif.Close();

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
    cout << "Nutil version 0.03" << endl << endl;
    cout << "Supported file formats: ";
    qDebug() << QImageReader::supportedImageFormats() << endl;

    cout << "Usage: "<< endl;
    cout << "  Nutil <command> <parameters>" << endl;
    cout << "  Commands: "<< endl;
    cout << "    batch [ excel file ] [ int sheet no ]" << endl;
    cout << "    transform [img input] [img output] [angle in rad] [scale] [bg col r] [bg col g] [bg col b] [bg col a]"<<endl;
    cout << "    transform_tiff [img input] [img output] [compression = none, jpeg, lzw] [angle in rad] [scale] [bg col b] [bg col g] [bg col r] [bg col a]" << endl;
    cout << " " << endl;
    cout << "If anything crashes or acts naughy, don't hesitate contacting leuat@irio.co.uk" << endl;
    cout << "" << endl;
    cout << "" << endl;

}

bool NutilApplication::Batch()
{
    if (m_argc!=4) {
        return false;
    }
    QString inFile = m_argv[2];
    int sheetIndex =  m_argv[3].toInt();
    Nauto n(inFile, sheetIndex);
    n.Execute();

    return true;
}
