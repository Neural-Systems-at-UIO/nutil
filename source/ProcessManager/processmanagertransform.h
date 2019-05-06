#ifndef PROCESSMANAGERTRANSFORM_H
#define PROCESSMANAGERTRANSFORM_H

#include "source/ProcessManager/processmanager.h"

class ProcessManagerTransform : public ProcessManager {

public:

    QString m_inputDir, m_outputDir;
    QString m_compression = "jpg";
    QString m_thumbType;
    QString m_autoClip;
    int m_colorSpread = 1;
    bool m_onlyThumbs = false;
    float m_thumbnailSize;

    bool Build(LSheet* m_sheet) override;
    void Execute() override; //(QString compression, QColor background, bool autoClip, int thumbnailSize, QString thumbType);
    void ReadHeader(LSheet* m_sheet, LBook* book) override;
    bool Verify() override;

};

#endif // PROCESSMANAGERTRANSFORM_H
