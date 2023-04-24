#ifdef USE_LIBTIFF

#ifndef LTIFF_H
#define LTIFF_H

#include <QString>
#include <QDebug>
#include <QVector>

#include <tiff.h>
#include <tiffio.h>

#include <QColor>
#include "source/util/counter.h"
#include <source/util/lgraph.h>

/*
output.SetField(TiffTag.IMAGEWIDTH, width);
                    output.SetField(TiffTag.IMAGELENGTH, height);
                    output.SetField(TiffTag.SAMPLESPERPIXEL, samplesPerPixel);
                    output.SetField(TiffTag.BITSPERSAMPLE, bitsPerSample);
                    output.SetField(TiffTag.ROWSPERSTRIP, output.DefaultStripSize(0));
                    output.SetField(TiffTag.PHOTOMETRIC, photo);
                    output.SetField(TiffTag.PLANARCONFIG, PlanarConfig.CONTIG);

                    // change orientation of the image
                    output.SetField(TiffTag.ORIENTATION, Orientation.RIGHTBOT);

*/

class LTiffBuffer{
public:
    uint32 m_x, m_y;
    tdata_t m_buf;

    LTiffBuffer(tdata_t buf, uint32 x, uint32 y) {
        m_buf = buf;
        m_x = x;
        m_y = y;
    }

};

class LTiffBufferList {
public:
    QVector<LTiffBuffer*> buffers;
    QVector<LTiffBuffer*> stack;
    int m_size;
    ~LTiffBufferList() {
        Release();
    }




    void Release() {
//        qDebug() << "Releasing: " << buffers.count();
        for (int i=0;i<buffers.count();i++ ) {
            _TIFFfree(buffers[i]->m_buf);
            delete buffers[i];
        }
        buffers.clear();
        stack.clear();

    }

    void SetDefault() {
        for (int i=0;i<buffers.count();i++) {
            buffers[i]->m_x=-1;
            buffers[i]->m_y=-1;

        }

    }

    void Init(int count, uint32 size) {
        Release();
        m_size =  size;
//        qDebug() << "Initializing buffer count:" << count;
        for (int i=0;i<count;i++) {
            tdata_t buf = _TIFFmalloc(size);
            buffers.append(new LTiffBuffer(buf, -1, -1));
        }
    }

    LTiffBuffer* getFree() {
        if (buffers.size()==0) {
            qDebug() << "Error: buffers not initialized. ";
            exit(1);
        }
        for (LTiffBuffer *b : buffers)
            if (b->m_x== -1)
                return b;

//        qDebug() << "Appending new buffer.." << rand()%100;
       tdata_t buf = _TIFFmalloc(m_size);
       LTiffBuffer* tbuf = new LTiffBuffer(buf, -1, -1);
       buffers.append(tbuf);


        return tbuf;
    }

    void UpdateBuffer() {
        while (stack.length()>=buffers.length()/2) {
            // Set free flag
            LTiffBuffer* b = stack[0];
            b->m_x=-1;
            b->m_y=-1;
            stack.remove(0);
        }
    }

    LTiffBuffer* getBuffer(int x, int y, TIFF* tif) {
        //for (LTiffBuffer* tbuf : stack) {
        for (int i=stack.count()-1;i>=0;i--) {
            LTiffBuffer* tbuf = stack[i];
            if (tbuf->m_x == (uint32)x && tbuf->m_y==(uint32)y)
                return tbuf;
        }

        LTiffBuffer* b = getFree();
        if (b==nullptr) {
            qDebug() << "Error: could not find free buffer for: " << x << ", " << y;
            qDebug() << "Did you remember to call updatebuffer? (dust)";
            exit(1);
        }
        b->m_x = x;
        b->m_y = y;
        TIFFReadTile(tif, b->m_buf, x, y, 0,0);
        stack.append(b);
        return b;


    }



};

class LTiff
{
public:

    QString m_filename;
    uint32 m_width, m_height;
    uint32 m_tileWidth, m_tileHeight;
    uint32 m_noTilesX, m_noTilesY;
    TIFF* m_tif = nullptr;
    QVector<tdata_t> m_buf;
    tdata_t m_writeBuf = nullptr;
    QVector<int> m_currentTileX, m_currentTileY;
    short m_samplesPerPixel, m_bitsPerSample, m_photo, m_config, m_compression;

    const QString m_compressionTypes[11] = {"not specified", "none", "CCITT RLE", "CCITT G3", "CCITT G4", "LZW", "JPEG", "JPEG New Style", "Deflate (adobe)", "9","10"};

    static const int max_thread_num = 32;

    LTiffBufferList bufferStack;


    void UpdateBuffers();

    QVector3D m_boundsMin, m_boundsMax;

    LTiff();
    ~LTiff();


    void SetCompression(QString type);
    void GetMinMax(int count, QColor& min, QColor & max, LGraph& histogram);
    void Analyzer();
    bool Open(QString filename);
    void New(QString filename);
    void FromQIMage(QString filename, QImage& img, QString comp, int tileSize, Counter& counter);
    QImage* ToQImage();
    void WriteBuffer(int x, int y, int thread_num);
    void ReadBuffer(int x, int y, int thread_num);
    void ApplyParameters();
    void CreateFromMeta(LTiff& oTiff, short compression, float rotationAngle, QColor background, bool calculateBounds);
    void CopyAllData(LTiff& oTiff);
    void AllocateBuffers();
    void Transform(LTiff &oTiff, float angle, QPointF scale, int tx, int ty, QColor background, int colorSpread, Counter* counter);
    void AutoContrast(LTiff &oTiff,  Counter* counter, float lowerT, float middleT, float forceStartAtZero, QString path);
    QColor GetTiledRGB(int x, int y, int thread_num);
    void SetupBuffers();
    void PrintImageInfo();
    void FindBoundsOld(QColor background);
    QString ClipToCurrentBorders(short compression, QColor background, Counter* counter);
    void ReleaseBuffers();

    void Close();
};

#endif // LTIFF_H
#endif
