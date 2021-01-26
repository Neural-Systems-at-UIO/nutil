#include "nutilapplication.h"
#include <stdio.h>
#include <iostream>
#include <QImage>
#include <QFile>
#include <QImageReader>
#include <QImageWriter>
#include <QDebug>
#include "source/util/util.h"
#ifndef TARGET_OS_MAC
#include <omp.h>
#else
#include <omp.h>
//#include "/usr/local/opt/libomp/include/omp.h"
#endif
#include "source/util/counter.h"
#include "source/nauto.h"
//#include <tiffio.h>

#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <algorithm>
#include <iostream>

NutilApplication::NutilApplication(int argc, char *argv[])
{
    m_argc = argc;
    for (int i=0;i<argc;i++)
        m_argv.append(QString(argv[i]));
}

bool Execute(QString fileName, int numThreads) {
    try {
        Data::data.isConsole = true;
        NutilTemplate nt;
        nt.Load(fileName);
        Nauto nauto;
        nauto.m_data = &nt;
        nauto.m_numThreads = numThreads;
        nauto.m_filename = fileName;
        QElapsedTimer t;
        t.start();
        nauto.Execute();
        //   qDebug() << "Operation complete in "<<Util::;

    }
    catch (QString e) {
        return false;
    }

    return true;
}


void NutilApplication::exec()
{
    bool ok = false;

    if (m_argc==1) {
        PrintUsage();
        exit(1);
    }

    if (m_argv[1].toLower() == "validate") {
        /*        if (m_argv.count()>=2) {
            std::cout << "Nutil Self-Validtor requires a specifically set-up directory as parameter 2";
            exit(1);
        }*/
        Validator();
        return;
    }


    QString file = m_argv[1];

    int numThreads = omp_get_max_threads();
    if (m_argv.count()>2)
        numThreads = m_argv[2].toInt();

    ok = Execute(file, numThreads);

    if (!ok) {
        PrintUsage();
    }
}



bool NutilApplication::RotateTiff()
{
/*    QCoreApplication::addLibraryPath("imageformats");
    if (m_argc!=11) {
        return false;
    }
    QString inFile = m_argv[2];
    QString outFile = m_argv[3];
    QString compression = m_argv[4];
    float angle =  m_argv[5].toFloat();
    float scale =  m_argv[6].toFloat();
    QColor background = QColor(m_argv[7].toFloat(), m_argv[8].toFloat(), m_argv[9].toFloat(),m_argv[10].toFloat());

    //    qDebug() << "Loading tiled tiff file:" << inFile;


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
    otif.CreateFromMeta(tif, writeCompression, angle, background, true);


    qDebug() << "Transforming to file " << outFile << " with compression " << tif.m_compressionTypes[writeCompression];
    //    otif.Transform(tif, angle, scale, 0,0, background, m_);

    tif.Close();
    otif.Close();
*/
    return true;

}

bool NutilApplication::Transform()
{
  /*  QCoreApplication::addLibraryPath("imageformats");
    if (m_argc!=10) {
        return false;
    }
    QString inFile = m_argv[2];
    QString outFile = m_argv[3];
    float angle =  m_argv[4].toFloat();
    float scale =  m_argv[5].toFloat();
    QColor background = QColor(m_argv[6].toFloat(), m_argv[7].toFloat(), m_argv[8].toFloat(),m_argv[9].toFloat());

    //std::cout << "infile: "  << inFile.toStdString() << std::endl;
    //std::cout << "angle: "  << angle << std::endl;
    //    qDebug() << "LOADING " << inFile;
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
        //        std::cout<<"threads="<<omp_get_num_threads()<<std::endl;
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
    std::cout << std::endl;
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

void NutilApplication::PrintUsage()
{
    std::cout << "Welcome to Nutil" << std::endl << std::endl;
    std::cout << "Supported file formats: ";
    qDebug() << QImageReader::supportedImageFormats();

    std::cout << "Usage: "<< std::endl;
    std::cout << "  Nutil <file>" << std::endl;
    std::cout << " " << std::endl;
    //    std::cout << "    batch [ excel file ] [ int sheet no ]" << std::endl;
    //    std::cout << "    transform [img input] [img output] [angle in rad] [scale] [bg col r] [bg col g] [bg col b] [bg col a]"<<std::endl;
    //    std::cout << "    transform_tiff [img input] [img output] [compression = none, jpeg, lzw] [angle in rad] [scale] [bg col b] [bg col g] [bg col r] [bg col a]" << std::endl;
    std::cout << " " << std::endl;
    std::cout << "If anything crashes or acts naughy, don't hesitate contacting leuat@irio.co.uk" << std::endl;
    std::cout << "" << std::endl;
    std::cout << "" << std::endl;

}

bool NutilApplication::Batch()
{
    if (m_argc!=4) {
        return false;
    }
    QString inFile = m_argv[2];
    int sheetIndex =  m_argv[3].toInt();
    //    Nauto n(inFile, sheetIndex);
    //    n.Execute();

    return true;
}


void NutilApplication::PrintFailure() {
    std::cout<<"    ▓█████  ██▓███   ██▓ ▄████▄       █████▒▄▄▄       ██▓ ██▓     "<<std::endl;
    std::cout<<"    ▓█   ▀ ▓██░  ██▒▓██▒▒██▀ ▀█     ▓██   ▒▒████▄    ▓██▒▓██▒    "<<std::endl;
    std::cout<<"    ▒███   ▓██░ ██▓▒▒██▒▒▓█    ▄    ▒████ ░▒██  ▀█▄  ▒██▒▒██░    "<<std::endl;
    std::cout<<"    ▒▓█  ▄ ▒██▄█▓▒ ▒░██░▒▓▓▄ ▄██▒   ░▓█▒  ░░██▄▄▄▄██ ░██░▒██░    "<<std::endl;
    std::cout<<"    ░▒████▒▒██▒ ░  ░░██░▒ ▓███▀ ░   ░▒█░    ▓█   ▓██▒░██░░██████▒"<<std::endl;
    std::cout<<"    ░░ ▒░ ░▒▓▒░ ░  ░░▓  ░ ░▒ ▒  ░    ▒ ░    ▒▒   ▓▒█░░▓  ░ ▒░▓  ░"<<std::endl;
    std::cout<<"     ░ ░  ░░▒ ░      ▒ ░  ░  ▒       ░       ▒   ▒▒ ░ ▒ ░░ ░ ▒  ░"<<std::endl;
    std::cout<<"       ░   ░░        ▒ ░░            ░ ░     ░   ▒    ▒ ░  ░ ░   "<<std::endl;
    std::cout<<"       ░  ░          ░  ░ ░                      ░  ░ ░      ░  ░"<<std::endl;
    std::cout << std::endl;
    std::cout << "Nutil self-validator failed. Please check the file comparisons for errors!"<<std::endl<<std::endl;;

}

void NutilApplication::PrintSuccess()
{
    std::cout<<"    .▄▄ · ▄• ▄▌ ▄▄·  ▄▄· ▄▄▄ ..▄▄ · .▄▄ · ▄▄ "<<std::endl;
    std::cout<<"    ▐█ ▀. █▪██▌▐█ ▌▪▐█ ▌▪▀▄.▀·▐█ ▀. ▐█ ▀. ██▌"<<std::endl;
    std::cout<<"    ▄▀▀▀█▄█▌▐█▌██ ▄▄██ ▄▄▐▀▀▪▄▄▀▀▀█▄▄▀▀▀█▄▐█·"<<std::endl;
    std::cout<<"    ▐█▄▪▐█▐█▄█▌▐███▌▐███▌▐█▄▄▌▐█▄▪▐█▐█▄▪▐█.▀ "<<std::endl;
    std::cout<<"     ▀▀▀▀  ▀▀▀ ·▀▀▀ ·▀▀▀  ▀▀▀  ▀▀▀▀  ▀▀▀▀  ▀ "<<std::endl;
    std::cout << std::endl;
    std::cout << "Everything seems to be in order. Go ahead an publish, Sharon!" << std::endl;
}


void NutilApplication::Validator()
{
    std::cout << "Welcome to the Nutil Self-validator!" <<std::endl;


    // First, got through transform files
    std::cout<<" _____                     __  "<<std::endl;
    std::cout<<"|_   _| __ __ _ _ __  ___ / _| ___  _ __ _ __ ___  "<<std::endl;
    std::cout<<"  | || '__/ _` | '_ \\/ __| |_ / _ \\| '__| '_ ` _ \\ "<<std::endl;
    std::cout<<"  | || | | (_| | | | \\__ \\  _| (_) | |  | | | | | |"<<std::endl;
    std::cout<<"  |_||_|  \\__,_|_| |_|___/_|  \\___/|_|  |_| |_| |_|"<<std::endl<<std::endl;
    Data::data.quiet = true;
    std::cout << "Executing TRANSFORM..."<<std::endl;
    Execute("T/batch.nut",4);
    if (!CompareFiles("T/out","png")) {
        PrintFailure();
        return;
    }
    if (!CompareFiles("T/out","tif")) {
        PrintFailure();
        return;
    }
    std::cout << std::endl << std::endl;
    PrintSuccess();

}

bool NutilApplication::CompareFiles(QString directory, QString extension)
{
    QStringList lst;
    Util::findFilesInSubDirectories(&lst, directory, extension, true);
    for (QString f : lst) {
        QString comp = f;
        comp = comp.replace("out","correct");
        QString f1 = comp;
        QString f2 = f;
        std::cout << "Comparing '" << f1.remove(QDir().currentPath()).toStdString() << "' and '"<<f2.remove(QDir().currentPath()).toStdString()<<"' : ";
        bool ret = Util::CompareIdenticalFiles(comp,f);
        QString r = ret?"true":"false";
        std::cout << r.toStdString() <<std::endl;
        if (ret == false) {
            std::cout << "************ ERROR : Files are not identical! Aborting... " << std::endl;
            return false;
        }
    }
    return true;
}
