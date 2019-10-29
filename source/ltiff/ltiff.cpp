#ifdef USE_LIBTIFF
#include "ltiff.h"
#include <QDebug>
#include <omp.h>
#include "source/util/lmessage.h"
#include "source/util/random.h"

LTiff::LTiff()
{

}




LTiff::~LTiff()
{
    Close();
}

void LTiff::SetCompression(QString type)
{
    for (int i=0;i<m_compressionTypes->length();i++)
        if (type.toLower()==m_compressionTypes[i].toLower())
            m_compression=i;
}

void LTiff::GetMinMax(int count, QColor &minCol, QColor &maxCol, LGraph& hist)
{
    //*counter = Counter((int)(length*width),"GetMinMax ", false);
    AllocateBuffers();
    minCol = QColor(255,255,255);
    maxCol = QColor(0,0,0);
    float minVal = 1E30;
    float maxVal = 0;

    hist.Initialize(40,0,255);
    int cnt = 0;
//   for (int i=0;i<count;i++) { { {
    for (int y = 0; y < m_height; y += m_tileHeight) {
        for (int x = 0; x < m_width; x += m_tileWidth) {

            for (int i=0;i<m_tileWidth*m_tileHeight/10;i++) {

                float xx = rand()%m_tileWidth + x;
                float yy = rand()%m_tileHeight + y;

                //float xx = rand()%m_width;
                //float yy = rand()%m_height;

                QColor color =  GetTiledRGB(xx,yy,omp_get_thread_num());


                hist.m_avg=hist.m_avg+ 1/3.0 * (color.red()+color.green()+color.blue());
                float len = Util::ColorLength(color) / sqrt(3);
  //              if (len>255)
//                qDebug() << len;
                if (len>1 && len<255)
                {
                hist.add(len,1);
/*                if (rand()%1000==0) {
                    qDebug() << len;
                }*/

                if (len<minVal) {
                    minVal = len;
                    minCol = color;
                }
                if (len>minVal) {
                    maxVal = len;
                    maxCol = color;
                }
                }
                //hist.Add(len);
                if (i%10==0) bufferStack.UpdateBuffer();
                if (Util::CancelSignal) {
                    return;
                }
                cnt++;
            }
        }

    }
    hist.m_avg/=cnt;

}

void LTiff::AutoContrast(LTiff &oTiff, Counter *counter, float lowerT, float middleT, float forceStartAtZero, QString path)
{
    float length = m_height/(float)m_tileHeight;
    float width = m_width/(float)m_tileWidth;

    *counter = Counter((int)(length*width),"AutoContrast ", false);
    AllocateBuffers();
    LGraph hist, gauss;
    QColor min_c, max_c;
    oTiff.GetMinMax(50000,min_c, max_c, hist);
    hist.Normalize();

    QString f = oTiff.m_filename.split("\\").last().split(".")[0];
//    qDebug() << "File: " << f;
    hist.SaveText(path+"/histogram"+f+".plt");

    hist.Mean();
    hist.Std();


//    float std = 2*hist.FitGaussStd(hist.m_meanY,2, 150, 200);
  //  float mean = hist.m_meanY;


    // Try another thing:


    int x0, x1;
  //  qDebug() << "LOWER MIDDLE: " << lowerT << "," << middleT;
    hist.SignalFind2(x0,x1, lowerT, middleT);
    if (forceStartAtZero==1) x0=0;
    //gauss.CopyFrom(hist);
  //  gauss.RenderGauss(mean, std);
    //gauss.SaveText("gauss_"+f+".plt");

    qDebug() << "x0: " << x0;
    qDebug() << "x1: " << x1;

    /*mean = (x1+x0)/2;
    std = (x1-x0)/2;


    qDebug() << "meanY :" << mean;
    qDebug() << "std :" << std;
*/



//    std = hist.m_std;

//    std = hist.m_stdY;

    for (uint y = 0; y < m_height; y += m_tileHeight) {
        for (uint x = 0; x < m_width; x += m_tileWidth) {
           // qDebug() << x;
            for (uint i = 0;i<m_tileWidth;i++)
                for (uint j=0;j<m_tileHeight;j++) {

                    float xx = x+i;
                    float yy = y+j;

                    QColor color =  oTiff.GetTiledRGB(xx,yy,omp_get_thread_num());

//                    color = Util::colorScale(color, mean, std);
                    color = Util::colorScale2(color, x0, x1);

                    ((unsigned char *)m_writeBuf)[3*(i + j*m_tileWidth) + 2] = color.red();
                    ((unsigned char *)m_writeBuf)[3*(i + j*m_tileWidth) + 1] = color.green();
                    ((unsigned char *)m_writeBuf)[3*(i + j*m_tileWidth) + 0] = color.blue();
            }


            WriteBuffer(x,y,0);
            counter->Tick();
            //m_progress = counter->percent;
            oTiff.bufferStack.UpdateBuffer();


            if (Util::CancelSignal) {
                return;
            }

        }

    }

    //    cout << "\nDone!" << endl;
}



void LTiff::Analyzer()
{

}

bool LTiff::Open(QString filename)
{
    if (!QFile::exists(filename)) {
        qDebug() << "ERROR: Could not find tiff file " << filename;
        LMessage::lMessage.Error("ERROR: Could not find tiff file " + filename);
        return false;
    }

    m_filename = filename;
    m_tif = TIFFOpen(filename.toStdString().c_str(), "r");
    if (!m_tif) {
        qDebug() << "CANNOT OPEN TIFF FILE : " << filename;
        return false;
    }
    TIFFGetField(m_tif, TIFFTAG_IMAGEWIDTH, &m_width);
    TIFFGetField(m_tif, TIFFTAG_IMAGELENGTH, &m_height);
    TIFFGetField(m_tif, TIFFTAG_TILEWIDTH, &m_tileWidth);
    TIFFGetField(m_tif, TIFFTAG_TILELENGTH, &m_tileHeight);

    TIFFGetField(m_tif, TIFFTAG_SAMPLESPERPIXEL, &m_samplesPerPixel);
    TIFFGetField(m_tif, TIFFTAG_BITSPERSAMPLE, &m_bitsPerSample);
    TIFFGetField(m_tif, TIFFTAG_PHOTOMETRIC,&m_photo);
    TIFFGetField(m_tif, TIFFTAG_PLANARCONFIG,&m_config);;
    TIFFGetField(m_tif, TIFFTAG_COMPRESSION,&m_compression);;


    if (TIFFIsTiled(m_tif)) {
        m_noTilesX = m_width/m_tileWidth;
        m_noTilesY = m_height/m_tileHeight;
    }

    return true;
}

void LTiff::New(QString filename)
{
    m_filename = filename;
    m_tif = TIFFOpen(filename.toStdString().c_str(), "w");

}

void LTiff::FromQIMage(QString filename, QImage &img, QString comp, int tileSize, Counter& counter)
{
    New(filename);
    SetCompression(comp);
    m_width = img.width();
    m_height = img.height();
    m_tileWidth = tileSize;
    m_tileHeight = tileSize;
    m_samplesPerPixel = 3;
    m_bitsPerSample = 8;
    m_photo = 2;
    m_config =1;

    qDebug() << "From QImage: " << filename;

    ApplyParameters();
    SetupBuffers();
    AllocateBuffers();
    counter.Init(m_tileWidth*m_tileHeight);
    for (int y = 0; y < m_height; y += m_tileHeight) {
        for (int x = 0; x < m_width; x += m_tileWidth) {

            //oTiff.ReadBuffer(x,y);

            for (int i = 0;i<m_tileWidth;i++)
                for (int j=0;j<m_tileHeight;j++) {
                    float xx = (x+i);
                    float yy = (y+j);
                    if (xx<m_width && yy<m_height) {
                        QColor color = img.pixel(xx,yy);

                        ((unsigned char *)m_writeBuf)[3*(i + j*m_tileWidth) + 2] = color.red();
                        ((unsigned char *)m_writeBuf)[3*(i + j*m_tileWidth) + 1] = color.green();
                        ((unsigned char *)m_writeBuf)[3*(i + j*m_tileWidth) + 0] = color.blue();

                    }
               }

            WriteBuffer(x,y,0);
            counter.Tick();
            bufferStack.UpdateBuffer();

        }
    }

    Close();



}

void LTiff::WriteBuffer(int x, int y, int thread_num)
{
    TIFFWriteTile(m_tif, m_writeBuf, x, y, 0,0);

}

void LTiff::ReadBuffer(int x, int y, int thread_num)
{
    TIFFReadTile(m_tif, m_buf[thread_num], x, y, 0,0);

    m_currentTileX[thread_num] = (int)((x/(float)m_tileWidth));
    m_currentTileY[thread_num] = (int)((y/(float)m_tileHeight));


}

void LTiff::PrintImageInfo()
{
    qDebug() << "TIFF image info: ";
    qDebug() << "  Image size:" << m_width << "," <<  m_height;
    qDebug() << "  Image tiles:"<< m_tileWidth << "," << m_tileHeight;
    qDebug() << "  Samples per pixel:"<< m_samplesPerPixel;
    qDebug() << "  Bits per pixel:" << m_bitsPerSample;
    qDebug() << "  photometric: " << m_photo;
    qDebug() << "  planar: " << m_config;

    if (m_compression>=0 && m_compression<11)
        qDebug() << "  Compression:" << m_compressionTypes[m_compression];
    else qDebug() << "UKNOWN COMPRESSION TYPE : "<< m_compression;
    qDebug() << "";

}

void LTiff::FindBoundsOld(QColor background)
{
    int N = 1000;
    float M = 1E30f;
    m_boundsMin = QVector3D(m_width,m_height,0);
    m_boundsMax = QVector3D(0, 0,0);

    qDebug() << "Finding bounds..." << endl;
    for (int i=0;i<N;i++) {
        float x = rand()%m_width;
        float y = rand()%m_height;
        qDebug() << "Testing.. " << x << ", " << y;
        QColor c = GetTiledRGB(x,y,omp_get_thread_num());
        if (c.red() == background.red() && c.green() == background.green() && c.blue() == background.blue()) {

        }
        else {
            m_boundsMax.setX(max(m_boundsMax.x(), x));
            m_boundsMax.setY(max(m_boundsMax.y(), y));
            m_boundsMin.setX(min(m_boundsMin.x(), x));
            m_boundsMin.setY(min(m_boundsMin.y(), y));
        }
        bufferStack.UpdateBuffer();
    }
    qDebug() << "Bounds found: ";
    qDebug() << "  Min: " << m_boundsMin;
    qDebug() << "  Max: " << m_boundsMax;
}

/*
 * BOUNDS MUST BE SET
 * */
QString LTiff::ClipToCurrentBorders(short compression, QColor background, Counter* counter)
{
    QStringList split = m_filename.split('.');

    LTiff otif;
    QString filename = split[0] + "_clip" + "." + split[1];
    otif.New(filename);
    otif.m_boundsMax = m_boundsMax;
    otif.m_boundsMin = m_boundsMin;
    otif.CreateFromMeta(*this, compression, 0, background, false);




/*
    qDebug() << "new bounds (in): " << m_boundsMin << ", " << m_boundsMax;
    qDebug() << "new bounds (out): " << otif.m_boundsMin << ", " << otif.m_boundsMax;


    qDebug() << "new width (in): " << m_width << ", " << m_height;
    qDebug() << "new width (out): " << otif.m_width << ", " << otif.m_height;

    qDebug() << "Calling setupBuffers: " << m_filename;*/
    SetupBuffers();
//    qDebug() << "Calling oTiff: setupBuffers: " << m_filename;
    otif.SetupBuffers();
  //  qDebug() << "Calling allocateBuffers " << m_filename;
    otif.AllocateBuffers();

    *counter = Counter((int)(otif.m_width*otif.m_height/otif.m_tileHeight/otif.m_tileWidth),"Clipping tiff ", false);
    //counter->current = 0;
    for (int y = 0; y < otif.m_height; y += otif.m_tileHeight) {
        for (int x = 0; x < otif.m_width; x += otif.m_tileWidth) {

            //oTiff.ReadBuffer(x,y);

            for (int i = 0;i<otif.m_tileWidth;i++)
                for (int j=0;j<otif.m_tileHeight;j++) {
                    float xx = (x+i) + m_boundsMin.x();
                    float yy = (y+j)+ m_boundsMin.y();
                    QColor color = QColor(0,0,0,255);
                    if (xx>=0 && xx<otif.m_width)
                        if (yy>=0 && yy<otif.m_height)
                            color = GetTiledRGB(xx,yy,omp_get_thread_num());

                    ((unsigned char *)otif.m_writeBuf)[3*(i + j*otif.m_tileWidth) + 2] = color.red();
                    ((unsigned char *)otif.m_writeBuf)[3*(i + j*otif.m_tileWidth) + 1] = color.green();
                    ((unsigned char *)otif.m_writeBuf)[3*(i + j*otif.m_tileWidth) + 0] = color.blue();


               }
            
            otif.WriteBuffer(x,y,0);
           // counter.Tick();
            bufferStack.UpdateBuffer();
            counter->Tick();
            //m_progress = counter->percent;
            //m_progress = rand()%100;
            if (Util::CancelSignal) {
                return "";
            }

        }
    }

    otif.Close();
    return filename;
}

void LTiff::ReleaseBuffers()
{
/*    for (int i=0;i<m_buf.size();i++) {
        _TIFFfree(m_buf[i]);
    }*/
    m_buf.clear();
    if (m_writeBuf!=nullptr)
        _TIFFfree(m_writeBuf);

        //        delete m_writeBuf;

    m_writeBuf = nullptr;

}


void LTiff::ApplyParameters()
{
    TIFFSetField(m_tif, TIFFTAG_SAMPLESPERPIXEL, m_samplesPerPixel);
    TIFFSetField(m_tif, TIFFTAG_IMAGEWIDTH, m_width );
    TIFFSetField(m_tif, TIFFTAG_IMAGELENGTH, m_height);
    TIFFSetField(m_tif, TIFFTAG_TILEWIDTH, m_tileWidth );
    TIFFSetField(m_tif, TIFFTAG_TILELENGTH, m_tileHeight);
    TIFFSetField(m_tif, TIFFTAG_BITSPERSAMPLE, m_bitsPerSample);
    //TIFFSetField(m_tif, TIFFTAG_ROWSPERSTRIP, m_output.DefaultStripSize(0));
    TIFFSetField(m_tif, TIFFTAG_PHOTOMETRIC, m_photo);
    TIFFSetField(m_tif, TIFFTAG_PLANARCONFIG, m_config);
    TIFFSetField(m_tif, TIFFTAG_COMPRESSION, m_compression);
    //    TIFFSetField(m_tif, TIFFTAG_PHOTOMETRIC, PHOTOMETRIC_RGB);

}




void LTiff::CreateFromMeta(LTiff &oTiff, short compression, float rotationAngle, QColor background, bool calculateBounds)
{
    m_width = oTiff.m_width;
    m_height = oTiff.m_height;
    m_tileWidth = oTiff.m_tileWidth;
    m_tileHeight = oTiff.m_tileHeight;
    m_bitsPerSample = oTiff.m_bitsPerSample;
    m_samplesPerPixel = oTiff.m_samplesPerPixel;
    m_photo = oTiff.m_photo;
    m_config = oTiff.m_config;



    // Switch with boundary box! whoo!

//    qDebug() << "size: " << m_width << ", " << m_height;
   // oTiff.AllocateBuffers();
    //oTiff.FindBoundsOld(background);


    //m_boundsMax = oTiff.m_boundsMax;
    //m_boundsMin = oTiff.m_boundsMin;
    if (!calculateBounds) {

        QVector3D c1 = QVector3D(m_boundsMin.x(),m_boundsMin.y(),0);
        QVector3D c2 = QVector3D(m_boundsMin.x(),m_boundsMax.y(),0);
        QVector3D c3 = QVector3D(m_boundsMax.x(),m_boundsMax.y(),0);
        QVector3D c4 = QVector3D(m_boundsMax.x(),m_boundsMin.y(),0);

        QVector3D center = c3/2;

        c1 = Util::Rotate2D(c1, center, rotationAngle);
        c2 = Util::Rotate2D(c2, center, rotationAngle);
        c3 = Util::Rotate2D(c3, center, rotationAngle);
        c4 = Util::Rotate2D(c4, center, rotationAngle);

        QVector3D newMin, newMax;
        m_boundsMax.setX(max(c1.x(), c2.x()));
        m_boundsMax.setX(max(m_boundsMax.x(), c3.x()));
        m_boundsMax.setX(max(m_boundsMax.x(), c4.x()));
        m_boundsMax.setY(max(c1.y(), c2.y()));
        m_boundsMax.setY(max(m_boundsMax.y(), c3.y()));
        m_boundsMax.setY(max(m_boundsMax.y(), c4.y()));

        m_boundsMin.setX(min(c1.x(), c2.x()));
        m_boundsMin.setX(min(m_boundsMin.x(), c3.x()));
        m_boundsMin.setX(min(m_boundsMin.x(), c4.x()));
        m_boundsMin.setY(min(c1.y(), c2.y()));
        m_boundsMin.setY(min(m_boundsMin.y(), c3.y()));
        m_boundsMin.setY(min(m_boundsMin.y(), c4.y()));



        m_width = m_boundsMax.x() - m_boundsMin.x();
        m_height = m_boundsMax.y() - m_boundsMin.y();

    }
    else {
       // m_boundsMax = oTiff.m_boundsMax;
       // m_boundsMin = oTiff.m_boundsMin;

        /*m_boundsMin.setX(0);
        m_boundsMin.setY(0);
        m_boundsMax.setX(m_width);
        m_boundsMax.setY(m_height);*/
    }
//    qDebug() << "New size: " << m_width << ", " << m_height;

//    exit(1);



    m_compression = compression;

    m_noTilesX = m_width/m_tileWidth;
    m_noTilesY = m_height/m_tileHeight;

    ApplyParameters();
    AllocateBuffers();

}




void LTiff::CopyAllData(LTiff &oTiff)
{
    float length = m_height/(float)m_tileHeight;
    float width = m_width/(float)m_tileWidth;

  //  Counter counter = Counter((int)(length*width),"Copying tiff ", false);

    for (int y = 0; y < m_height; y += m_tileHeight)
        for (int x = 0; x < m_width; x += m_tileWidth) {
            oTiff.ReadBuffer(x,y,0);
            m_buf = oTiff.m_buf;
            //qDebug() << x << ", " << y;
            WriteBuffer(x,y,0);
//            counter->Tick();

        }

    cout << "\nDone!" << endl;
}

QColor LTiff::GetTiledRGB(int x, int y, int thread_num) {

    int xtile = (int)((x/(float)m_tileWidth));
    int ytile = (int)((y/(float)m_tileHeight));

    if (xtile != m_currentTileX[thread_num] || ytile!=m_currentTileY[thread_num]) {
        LTiffBuffer* buf = bufferStack.getBuffer(xtile*m_tileWidth, ytile*m_tileHeight,m_tif);
        m_currentTileX[thread_num] = (int)((x/(float)m_tileWidth));
        m_currentTileY[thread_num] = (int)((y/(float)m_tileHeight));
        if (buf==nullptr) {
            qDebug() << "Buffer not initialized!";
            exit(1);
        }
        m_buf[thread_num] = (buf->m_buf);

    }

    QColor c;
    int i = x - m_currentTileX[thread_num]*m_tileWidth;
    int j = y - m_currentTileY[thread_num]*m_tileHeight;
    uint pos = 3*(i + j*m_tileWidth);

    if (pos>3*m_tileWidth*m_tileHeight) {
        qDebug() << "OUT OF BONDS Trying to read: "<< i << ", " << j;
        qDebug() << "Mest sannsynlig Nicolaas sin feil. Kontakt!";
        exit(1);
    }
    c.setRed(((unsigned char*)m_buf[thread_num])[pos + 2]);
    c.setGreen(((unsigned char*)m_buf[thread_num])[pos + 1]);
    c.setBlue(((unsigned char*)m_buf[thread_num])[pos + 0]);
    return c;

}



void LTiff::SetupBuffers()
{
    AllocateBuffers();
    bufferStack.Init(32, TIFFTileSize(m_tif));

}


void LTiff::Transform(LTiff &oTiff, float angle, QPointF scale, int tx, int ty, QColor background, int colorSpread,Counter* counter)
{
    float length = m_height/(float)m_tileHeight;
    float width = m_width/(float)m_tileWidth;

    *counter = Counter((int)(length*width),"Copying tiff ", false);
    AllocateBuffers();
    int centerx = m_width/2;
    int centery = m_height/2;

    int ocenterx = oTiff.m_width/2;
    int ocentery = oTiff.m_height/2;

    // Find new bounds as well

    m_boundsMax = QVector3D(0,0,0);
    m_boundsMin = QVector3D(m_width, m_height,0 );
    float t = 2 + colorSpread;
    float scaleDebug = 1;
    for (int y = 0; y < m_height; y += m_tileHeight) {
        for (int x = 0; x < m_width; x += m_tileWidth) {

            //oTiff.ReadBuffer(x,y);

            for (int i = 0;i<m_tileWidth/scaleDebug;i++)
                for (int j=0;j<m_tileHeight/scaleDebug;j++) {

                    //byte c1 = oTiff.getTiledPixel
                    //                    qDebug() << "Getting at " << x+i << " , " << y+j << endl;

                    float xx = (x+i - centerx)/scale.x();
                    float yy = (y+j - centery)/scale.y();

                    float xr = xx*cos(angle)-yy*sin(angle) + ocenterx + tx;
                    float yr = yy*cos(angle)+xx*sin(angle) + ocentery + ty;
                    QColor color = background;
                    if (xr>=0 && xr<oTiff.m_width && yr>=0 && yr<oTiff.m_height) {
                        color =  oTiff.GetTiledRGB(xr,yr,omp_get_thread_num());
                    };// else qDebug() << "OUTSIDE";


                    //if (rand()%100==0)
                    {
                       /* float v = abs(color.red()-background.red())+ abs(color.green()-background.green()) + abs(color.blue()-background.blue());
                        if (v>0 && xx+centerx<5)
                            qDebug() << v << " at " << QString::number(xx + centerx) << ", " << QString::number(yy+centery);
                            */
                    }

                    if (abs(color.red()-background.red())<t && abs(color.green()-background.green())<t && abs(color.blue()-background.blue())<t) {

                    }
                    else {
                           //dy =  yy + centery
                        float dx = x+i;//(xx + centerx)*scale.x();
                        float dy = y+j;//(xx + centerx)*scale.x();

/*                        if (scale.x()<0) {
                            m_width-(xx + centerx);
                        }*/
                        m_boundsMax.setX(max(m_boundsMax.x(), dx));
                        m_boundsMin.setX(min(m_boundsMin.x(), dx));
                        m_boundsMax.setY(max(m_boundsMax.y(), dy));
                        m_boundsMin.setY(min(m_boundsMin.y(), dy));
                    }

                    ((unsigned char *)m_writeBuf)[3*(i + j*m_tileWidth) + 2] = color.red();
                    ((unsigned char *)m_writeBuf)[3*(i + j*m_tileWidth) + 1] = color.green();
                    ((unsigned char *)m_writeBuf)[3*(i + j*m_tileWidth) + 0] = color.blue();
                }



            WriteBuffer(x,y,0);
            counter->Tick();
            //m_progress = counter->percent;
            oTiff.bufferStack.UpdateBuffer();

//            qDebug() << "Updated bounds: " << m_boundsMin << " , " << m_boundsMax;

            if (Util::CancelSignal) {
                return;
            }

        }

    }

    //    cout << "\nDone!" << endl;
}




void LTiff::AllocateBuffers()
{
    ReleaseBuffers();
    for (int i=0;i<max_thread_num;i++) {
 //      tdata_t buf = _TIFFmalloc(TIFFTileSize(m_tif));
        m_buf.append(nullptr);
    }

    m_writeBuf = _TIFFmalloc(TIFFTileSize(m_tif));


    m_currentTileX.clear();
    m_currentTileY.clear();

    for (int i=0;i<max_thread_num;i++) {
        m_currentTileX.append(-1);
        m_currentTileY.append(-1);
    }

}

void LTiff::Close()
{
    ReleaseBuffers();
    if (m_tif!=nullptr)
        TIFFClose(m_tif);
    m_tif = nullptr;
}
#endif
