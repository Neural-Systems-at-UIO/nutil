#ifndef NUTILPROCESS_H
#define NUTILPROCESS_H

#include <QString>
#include <QDebug>
#include <omp.h>
#include "source/util/counter.h"
#include "source/ltiff.h"
#include "source/util/util.h"

class NutilProcess
{
public:
    NutilProcess();
    int m_id;
    float getProgress();
    LTiff otif;

    bool TransformTiff(QString inFile, QString outFile, QString compression, float angle, float scale, QColor background);

};

#endif // NUTILPROCESS_H
