#include "nutilprocess.h"

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

    otif.New(outFile);
    otif.CreateFromMeta(tif, writeCompression);


    qDebug() << "Transforming to file " << outFile << " with compression " << tif.m_compressionTypes[writeCompression];
    otif.Transform(tif, angle, scale, 0,0, background);

    tif.Close();
    otif.Close();

    return true;

}
