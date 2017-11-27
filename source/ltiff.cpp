#include "ltiff.h"
#include <QDebug>

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

    m_currentTileX = -1;
    m_currentTileY = -1;

    m_noTilesX = m_width/m_tileWidth;
    m_noTilesY = m_height/m_tileHeight;

    AllocateBuffer();
    bufferStack.Init(100, TIFFTileSize(m_tif));
    return true;
}

void LTiff::New(QString filename)
{
    m_tif = TIFFOpen(filename.toStdString().c_str(), "w");
    m_currentTileX = -1;
    m_currentTileY = -1;

}

void LTiff::WriteBuffer(int x, int y)
{
    TIFFWriteTile(m_tif, m_buf, x, y, 0,0);

}

void LTiff::ReadBuffer(int x, int y)
{
    TIFFReadTile(m_tif, m_buf, x, y, 0,0);

    m_currentTileX = (int)((x/(float)m_tileWidth));
    m_currentTileY = (int)((y/(float)m_tileHeight));


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
    TIFFSetField(m_tif, TIFFTAG_COMPRESSION, COMPRESSION_JPEG);

    //    TIFFSetField(m_tif, TIFFTAG_PHOTOMETRIC, PHOTOMETRIC_RGB);

    qDebug() << "sppix:  "<< m_samplesPerPixel;
    qDebug() << "dim: "<< m_width << ", " << m_height;
    qDebug() << "tile : " << m_tileWidth << ", " << m_tileHeight;
    qDebug() << "bps: " << m_bitsPerSample;
    qDebug() << "photo : " << m_photo;
}



void LTiff::CreateFromMeta(LTiff &oTiff)
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

    ApplyParameters();
    AllocateBuffer();

}

void LTiff::CopyAllData(LTiff &oTiff)
{
    float length = m_height/(float)m_tileHeight;
    float width = m_width/(float)m_tileWidth;

    Counter counter = Counter((int)(length*width),"Copying tiff ", false);

    for (int y = 0; y < m_height; y += m_tileHeight)
        for (int x = 0; x < m_width; x += m_tileWidth) {
            oTiff.ReadBuffer(x,y);
            m_buf = oTiff.m_buf;
            //qDebug() << x << ", " << y;
            WriteBuffer(x,y);
            counter.Tick();

        }

    cout << "\nDone!" << endl;
}

QColor LTiff::GetTiledRGB(int x, int y) {

    int xtile = (int)((x/(float)m_tileWidth));
    int ytile = (int)((y/(float)m_tileHeight));

    if (xtile != m_currentTileX || ytile!=m_currentTileY) {
        //        qDebug() << "Reading NEW: " << xtile*m_tileWidth << " , " << ytile*m_tileHeight;
        //ReadBuffer(xtile*m_tileWidth, ytile*m_tileHeight);
        LTiffBuffer* buf = bufferStack.getBuffer(xtile*m_tileWidth, ytile*m_tileHeight,m_tif);
        m_currentTileX = (int)((x/(float)m_tileWidth));
        m_currentTileY = (int)((y/(float)m_tileHeight));
        m_buf = buf->m_buf;

    }

    QColor c;
    int i = x - m_currentTileX*m_tileWidth;
    int j = y - m_currentTileY*m_tileHeight;
    uint pos = 3*(i + j*m_tileWidth);

    if (pos>3*m_tileWidth*m_tileHeight) {
        qDebug() << "OUT OF BONDS Trying to read: "<< i << ", " << j;
        qDebug() << "Mest sannsynlig Nicolaas sin feil. Kontakt!";
        exit(1);
    }

    c.setRed(((unsigned char*)m_buf)[pos + 2]);
    c.setGreen(((unsigned char*)m_buf)[pos + 1]);
    c.setBlue(((unsigned char*)m_buf)[pos + 0]);
    return c;

}

void LTiff::Transform(LTiff &oTiff, float angle, float scale, int tx, int ty, QColor background)
{
    float length = m_height/(float)m_tileHeight;
    float width = m_width/(float)m_tileWidth;

    Counter counter = Counter((int)(length*width),"Copying tiff ", false);
    AllocateBuffer();

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
                        color =  oTiff.GetTiledRGB(xr,yr);
                    }

                    //                    QColor col = oTiff.GetTiledRGB(x+i,y+j);

                    ((unsigned char *)m_buf)[3*(i + j*m_tileWidth) + 2] = color.red();
                    ((unsigned char *)m_buf)[3*(i + j*m_tileWidth) + 1] = color.green();
                    ((unsigned char *)m_buf)[3*(i + j*m_tileWidth) + 0] = color.blue();
                }

            WriteBuffer(x,y);
            counter.Tick();

        }

    }

    cout << "\nDone!" << endl;
}


void LTiff::AllocateBuffer()
{
    m_buf = _TIFFmalloc(TIFFTileSize(m_tif));
}

void LTiff::Close()
{
    TIFFClose(m_tif);
    //    if (m_buf)
    //      _TIFFfree(m_buf);
}
