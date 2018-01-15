#include "nutilprocess.h"
#include "source/util/lmessage.h"

NutilProcess::NutilProcess()
{

}

float NutilProcess::getProgress()
{
   return otif.m_progress;
}

bool NutilProcess::TransformTiff(QString inFile, QString outFile, QString compression, float angle, float scale, QColor background)
{


    qDebug() << "Loading tiled tiff file:" << inFile;

    LTiff tif;
    if (!tif.Open(inFile)) {
        LMessage::lMessage.Error("Could not open tiff file + '"+inFile + "' ! Please check the filename and try again.");
        return false;
    }
    tif.PrintImageInfo();
    if (!TIFFIsTiled(tif.m_tif)) {
        LMessage::lMessage.Error("Error: this tiff file is not tiled. Please use the other transformation method for non-tiled tiffs.");
        return false;
    }
    else qDebug() << "IS TILED";




    if (!(tif.m_samplesPerPixel==3 && tif.m_bitsPerSample==8)) {
        LMessage::lMessage.Error("Error! For now, lutil only supports big tiffs with RGB format");
        return false;
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

    otif.m_boundsMin = QVector3D(0,0,0);
    otif.m_boundsMax = QVector3D(tif.m_width, tif.m_height, 0);

    otif.New(outFile);
    otif.CreateFromMeta(tif, writeCompression, angle, background);

    //qDebug() << "Finding bounds..";
    //tif.FindBounds(background);

    qDebug() << "Transforming to file " << outFile << " with compression " << tif.m_compressionTypes[writeCompression];

    m_infoText =  "rotating " + QString::number(angle/(2*M_PI)*360,'f',2) + " degrees" ;
    otif.Transform(tif, angle, scale, 0,0, background);
    m_infoText =  "Clipping whitespace" ;
    otif.ClipToCurrentBorders(writeCompression, background);

    tif.Close();
    otif.Close();

    return true;

}

