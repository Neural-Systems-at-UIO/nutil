#ifndef PROCESSMANAGERPCOUNTER_H
#define PROCESSMANAGERPCOUNTER_H

#include "source/ProcessManager/processmanager.h"

class ProcessManagerPCounter : public ProcessManager {

public:

    AtlasLabels m_labels;

    QString m_inputDir, m_outputDir;
    QString m_atlasDir;
    QString m_labelFile;

    int m_pixelCutoff;
    float m_areaScale = 1;

    Reports reports;


    bool Build(LSheet* m_sheet) override;
    void Execute() override; //(QString compression, QColor background, bool autoClip, int thumbnailSize, QString thumbType);
    void ReadHeader(LSheet* m_sheet) override;

    void GenerateReports(LSheet* m_sheet);
    bool Verify() override { return true; }

};


#endif // PROCESSMANAGERPCOUNTER_H
