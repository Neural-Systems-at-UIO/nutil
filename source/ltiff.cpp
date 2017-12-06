#include "ltiff.h"
#include <QDebug>
#include <omp.h>

LTiff::LTiff()
{

}




LTiff::~LTiff()
{

}

bool LTiff::Open(QString filename)
{
    m_tif = TIFFOpen(filename.toStdString().c_str(), "r");
    if (!m_tif) {
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


    if (m_tileWidth!=0) {
        m_noTilesX = m_width/m_tileWidth;
        m_noTilesY = m_height/m_tileHeight;
    }

    return true;
}

void LTiff::New(QString filename)
{
    m_tif = TIFFOpen(filename.toStdString().c_str(), "w");

}

void LTiff::WriteBuffer(int x, int y, int thread_num)
{
    TIFFWriteTile(m_tif, m_buf[thread_num], x, y, 0,0);

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
    qDebug() << "  Compression:" << m_compressionTypes[m_compression];
    qDebug() << "";

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




void LTiff::CreateFromMeta(LTiff &oTiff, short compression)
{
    m_width = oTiff.m_width;
    m_height = oTiff.m_height;
    m_tileWidth = oTiff.m_tileWidth;
    m_tileHeight = oTiff.m_tileHeight;
    m_bitsPerSample = oTiff.m_bitsPerSample;
    m_samplesPerPixel = oTiff.m_samplesPerPixel;
    m_photo = oTiff.m_photo;
    m_config = oTiff.m_config;

    m_noTilesX = m_width/m_tileWidth;
    m_noTilesY = m_height/m_tileHeight;

    m_compression = compression;

    ApplyParameters();
    AllocateBuffers();

}

void LTiff::CopyAllData(LTiff &oTiff)
{
    float length = m_height/(float)m_tileHeight;
    float width = m_width/(float)m_tileWidth;

    Counter counter = Counter((int)(length*width),"Copying tiff ", false);

    for (int y = 0; y < m_height; y += m_tileHeight)
        for (int x = 0; x < m_width; x += m_tileWidth) {
            oTiff.ReadBuffer(x,y,0);
            m_buf = oTiff.m_buf;
            //qDebug() << x << ", " << y;
            WriteBuffer(x,y,0);
            counter.Tick();

        }

    cout << "\nDone!" << endl;
}

QColor LTiff::GetTiledRGB(int x, int y, int thread_num) {

    int xtile = (int)((x/(float)m_tileWidth));
    int ytile = (int)((y/(float)m_tileHeight));

    if (xtile != m_currentTileX[thread_num] || ytile!=m_currentTileY[thread_num]) {
        //        qDebug() << "Reading NEW: " << xtile*m_tileWidth << " , " << ytile*m_tileHeight;
        //ReadBuffer(xtile*m_tileWidth, ytile*m_tileHeight);
        LTiffBuffer* buf = bufferStack.getBuffer(xtile*m_tileWidth, ytile*m_tileHeight,m_tif);
        m_currentTileX[thread_num] = (int)((x/(float)m_tileWidth));
        m_currentTileY[thread_num] = (int)((y/(float)m_tileHeight));
        m_buf[thread_num] = buf->m_buf;

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
    bufferStack.Init(60, TIFFTileSize(m_tif));

}


void LTiff::Transform(LTiff &oTiff, float angle, float scale, int tx, int ty, QColor background)
{
    float length = m_height/(float)m_tileHeight;
    float width = m_width/(float)m_tileWidth;

    Counter counter = Counter((int)(length*width),"Copying tiff ", false);
    AllocateBuffers();

    int centerx = m_width/2;
    int centery = m_height/2;



    for (int y = 0; y < m_height; y += m_tileHeight) {
        for (int x = 0; x < m_width; x += m_tileWidth) {

            //oTiff.ReadBuffer(x,y);

            for (int i = 0;i<m_tileWidth;i++)
                for (int j=0;j<m_tileHeight;j++) {

                    //byte c1 = oTiff.getTiledPixel
                    //                    qDebug() << "Getting at " << x+i << " , " << y+j << endl;

                    float xx = (x+i - centerx)*scale;
                    float yy = (y+j - centery)*scale;

                    float xr = xx*cos(angle)-yy*sin(angle) + centerx + tx;
                    float yr = yy*cos(angle)+xx*sin(angle) + centery + ty;
                    QColor color = background;
                    if (xr>=0 && xr<m_width && yr>=0 && yr<m_height) {
                        color =  oTiff.GetTiledRGB(xr,yr,omp_get_thread_num());
                    };// else qDebug() << "OUTSIDE";


                    ((unsigned char *)m_buf[0])[3*(i + j*m_tileWidth) + 2] = color.red();
                    ((unsigned char *)m_buf[0])[3*(i + j*m_tileWidth) + 1] = color.green();
                    ((unsigned char *)m_buf[0])[3*(i + j*m_tileWidth) + 0] = color.blue();
                }

            WriteBuffer(x,y,0);
            counter.Tick();
            m_progress = counter.percent;
            oTiff.bufferStack.UpdateBuffer();

        }

    }

    cout << "\nDone!" << endl;
}


void LTiff::AllocateBuffers()
{
    m_buf.clear();
    for (int i=0;i<max_thread_num;i++) {
       tdata_t buf = _TIFFmalloc(TIFFTileSize(m_tif));
        m_buf.append(buf);
    }

    m_currentTileX.clear();
    m_currentTileY.clear();

    for (int i=0;i<max_thread_num;i++) {
        m_currentTileX.append(-1);
        m_currentTileY.append(-1);
    }

}

void LTiff::Close()
{
    TIFFClose(m_tif);
    //    if (m_buf)
    //      _TIFFfree(m_buf);
}
