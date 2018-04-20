#include "nutilprocess.h"
#include "source/util/lmessage.h"
#include "source/data.h"

NutilProcess::NutilProcess()
{

}

float NutilProcess::getProgress()
{
    return m_counter.m_progress;
}

bool NutilProcess::InitializeCounter(QString inFile, bool autoClip, int thumbnailSize)
{

    int totalOperations = 0;
    LTiff tif;
    if (!tif.Open(inFile)) {

        QString s = "";
        if (!QFile::exists(inFile))
            s="(file does not exist)";
        else
            s="TIFF file is corrupted!";
        LMessage::lMessage.Error("Could not open tiff file + '"+inFile + "' ! Please check the filename and try again. " + s);

        Data::data.abort=true;
        Util::CancelSignal=true;
        return false;
    }

    float length = (int)(tif.m_height/(float)tif.m_tileHeight);
    float width = (int)(tif.m_width/(float)tif.m_tileWidth);

  //  Counter counter = Counter((int)(length*width),"Copying tiff ", false);

 //   qDebug() << length << " , " << width;

    totalOperations += (int)(length*width);
    if (autoClip) {
        totalOperations +=(int)(length*width);
    }

    if (thumbnailSize>0) {
        float aspectRatio = 1.0/(float)(tif.m_width/(float)tif.m_height);

        int tx = thumbnailSize;

        int ty = (int)(thumbnailSize*aspectRatio);
        totalOperations+=tx;//*ty;
    }

    m_counter = Counter(totalOperations, "Transforming", false);
    return true;
}

bool NutilProcess::TransformTiff(QString inFile, QString outFile, QString compression, float angle, QPointF scale, QColor background, bool autoClip)
{


    qDebug() << "Loading tiled tiff file:" << inFile;

    LTiff tif;
    int writeCompression;
    if (!LoadAndVerifyTiff(tif, inFile, writeCompression, compression))
        return false;

    otif.m_boundsMin = QVector3D(0,0,0);
    otif.m_boundsMax = QVector3D(tif.m_width, tif.m_height, 0);

    otif.New(outFile);
    otif.CreateFromMeta(tif, writeCompression, angle, background, false);

    //qDebug() << "Finding bounds..";
    //tif.FindBounds(background);


    qDebug() << "Transforming to file " << outFile << " with compression " << tif.m_compressionTypes[writeCompression];

    m_infoText =  "rotating " + QString::number(angle/(2*M_PI)*360,'f',2) + " degrees" ;
    otif.Transform(tif, angle, scale, 0,0, background, &m_counter);

    tif.Close();
    QString renameFile = "";
    if (autoClip) {
        m_infoText =  "Clipping whitespace" ;
        renameFile = otif.ClipToCurrentBorders(writeCompression, background,&m_counter);
    }
    otif.Close();

    if (autoClip && renameFile!="") {
        qDebug() << "Renaming from " << renameFile << " to "  << outFile;
        QFile file (outFile);
        file.remove();
        QFile::rename(renameFile, outFile);
    }
    return true;

}

bool NutilProcess::AutoContrast(QString inFile, QString outFile, QString compression, QColor background, float std)
{
    LTiff tif;
    int writeCompression;
    if (!LoadAndVerifyTiff(tif, inFile, writeCompression, compression))
        return false;



    otif.New(outFile);
    otif.CreateFromMeta(tif, writeCompression, 0, background, true);

    qDebug() << "Width: " << otif.m_width;

    //qDebug() << "Finding bounds..";
    //tif.FindBounds(background);


    qDebug() << "Autocontrasting to file " << outFile;;

    m_infoText =  "Autocontrasting ";
    otif.AutoContrast(tif,  &m_counter, std);
    otif.Close();

    return true;
}

bool NutilProcess::GenerateThumbnail(QString inFile, QString outFile, int thumbnailSize)
{
    LTiff tif;
    if (!tif.Open(inFile))
        return false;

    tif.SetupBuffers();
    float aspectRatio = 1.0/(float)(tif.m_width/(float)tif.m_height);

    int tx = thumbnailSize;

    int ty = (int)(thumbnailSize*aspectRatio);
    m_infoText = "Creating thumbnail";
    unsigned char* pixels = new unsigned char[tx*ty*4];

    m_counter = Counter((int)(tx*ty),"Clipping tiff ", false);


    for (int i=0;i<tx;i++) {
        for (int j=0;j<ty;j++) {
            if (Data::data.abort ||Util::CancelSignal)
                break;
            int x = (int)((float)i/(float)tx * tif.m_width);
            int y = (int)((float)j/(float)ty * tif.m_height);
            QColor c = tif.GetTiledRGB(x,y,omp_get_thread_num());
            int p = i + j*tx;
            pixels[p*4 + 0] = c.red();
            pixels[p*4 + 1] = c.green();
            pixels[p*4 + 2] = c.blue();
            pixels[p*4 + 3] = c.alpha();

            tif.bufferStack.UpdateBuffer();
            m_counter.Tick();
            //otif.m_progress = m_counter.percent;


        }

    }

    QImage img(pixels, tx, ty, QImage::Format_RGB32); //640,480 size picture.
    img.save(outFile);
    tif.Close();
    delete[] pixels;
    return true;
}

bool NutilProcess::AutoAdjustImageLevels(QString inFile, QString outFile)
{
    return true;
}

void NutilProcess::ClearAreaPixels()
{
    for (Area& a: m_areas) {
        a.m_points.clear();
    }
}

void NutilProcess::ReleasePCounter()
{
    lImage.Release();
    ClearAreaPixels();
}

bool NutilProcess::PCounter(QString inFile, QColor testColor, QVector<Area>* areas, int pixelCutoff)
{
    qDebug() << inFile;
    lImage.Load(inFile);

    m_infoText = "Finding areas";
    lImage.FindAreas(testColor, &m_counter, areas, pixelCutoff);

    return true;
}

bool NutilProcess::LoadAndVerifyTiff(LTiff &tif, QString inFile, int &writeCompression, QString compression)
{
    qDebug() << "Loading tiled tiff file:" << inFile;

    if (!tif.Open(inFile)) {
        QString s = "";
        if (!QFile::exists(inFile))
            s="File does not exist! Please check the filename and try again. ";
        else
            s="TIFF file is corrupted!";
        LMessage::lMessage.Error("Could not open tiff file + '"+inFile + "'! " + s);
        Data::data.abort=true;
        Util::CancelSignal=true;

        return false;
    }
    tif.PrintImageInfo();
    if (!TIFFIsTiled(tif.m_tif)) {
        LMessage::lMessage.Error("Error: this tiff file is not tiled. Please use the other transformation method for non-tiled tiffs.");
        return false;
    }
//    else qDebug() << "IS TILED";




    if (!(tif.m_samplesPerPixel==3 && tif.m_bitsPerSample==8)) {
        LMessage::lMessage.Error("Error! For now, lutil only supports big tiffs with RGB format");
        return false;
    }

    tif.SetupBuffers();

    writeCompression = 0;

    if (compression.toLower()=="jpeg")
        writeCompression = 7;
    if (compression.toLower()=="lzw")
        writeCompression = 5;
    if (compression.toLower()=="none")
        writeCompression = 1;

    if (writeCompression==0) {
        //qDebug() << "Unknown compression format. Must be either jpeg, lzw or none.";
        LMessage::lMessage.Error("Unknown compression format. Must be either jpeg, lzw or none.");
        return false;
    }

    return true;
}

