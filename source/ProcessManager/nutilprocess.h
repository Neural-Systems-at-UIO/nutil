#ifndef NUTILPROCESS_H
#define NUTILPROCESS_H

#include <QString>
#include <QDebug>
#ifndef TARGET_OS_MAC
#include <omp.h>
#else
#include "/usr/local/opt/libomp/include/omp.h"
#endif
#include "source/util/counter.h"
#include "source/ltiff/ltiff.h"
#include "source/util/util.h"
#include "source/util/counter.h"
#include "source/util/nlimage.h"
#include "source/util/area.h"
#include "source/util/lparameter.h"

class NutilProcess
{
public:
    QString m_infoText;
    NutilProcess();
    int m_id;
    float getProgress();
    Counter m_counter;
    LTiff otif;
    LParameter* m_parameters;
    QVector<Area> m_areas;

    NLImage lImage;
    bool InitializeCounter(QString inFile, bool autoClip, float thumbnailSize);
    bool TransformTiff(QString inFile, QString outFile, QString compression, float angle, QPointF scale, QColor background, int m_colorScale, bool autoClip);
    bool AutoContrast(QString inFile, QString outFile, QString compression, QColor background, QString path);
    bool GenerateThumbnail(QString inFile, QString outFile, float thumbnailSize);
    bool AutoAdjustImageLevels(QString inFile, QString outFile);


    void ClearAreaPixels();
    void ReleasePCounter();

    bool PCounter(QString inFile, QColor counter,  QVector3D colorWidth, QVector<Area>* areas, int pixelCutoff, int pMax, QString maskFile, QColor maskColor);

//    m_processes[i]->PCounter(+ pi->m_inFile, m_inputDir, m_background, pi->m_outFile, m_AtlasDir, m_labelFile);

    bool LoadAndVerifyTiff(LTiff& tif, QString filename, int& writeCompression, QString compression);
};

#endif // NUTILPROCESS_H
