#ifndef NUTILPROCESS_H
#define NUTILPROCESS_H

#include <QString>
#include <QDebug>
#include <omp.h>
#include "source/util/counter.h"
#include "source/ltiff/ltiff.h"
#include "source/util/util.h"
#include "source/util/counter.h"
#include "source/util/limage.h"
#include "source/util/area.h"

class NutilProcess
{
public:
    QString m_infoText;
    NutilProcess();
    int m_id;
    float getProgress();
    Counter m_counter;
    LTiff otif;


    QVector<Area> m_areas;

    NLImage lImage;
    bool InitializeCounter(QString inFile, bool autoClip, int thumbnailSize);
    bool TransformTiff(QString inFile, QString outFile, QString compression, float angle, QPointF scale, QColor background, bool autoClip);
    bool AutoContrast(QString inFile, QString outFile, QString compression, QColor background, float std);
    bool GenerateThumbnail(QString inFile, QString outFile, int thumbnailSize);
    bool AutoAdjustImageLevels(QString inFile, QString outFile);


    void ClearAreaPixels();
    void ReleasePCounter();

    bool PCounter(QString inFile, QColor counter, QVector<Area>* areas, int pixelCutoff, int pMax);

//    m_processes[i]->PCounter(+ pi->m_inFile, m_inputDir, m_background, pi->m_outFile, m_AtlasDir, m_labelFile);

    bool LoadAndVerifyTiff(LTiff& tif, QString filename, int& writeCompression, QString compression);
};

#endif // NUTILPROCESS_H
