#ifndef AREAFINDER3D_H
#define AREAFINDER3D_H

#include "source/ProcessManager/processmanager.h"




class AreaFinder3D : public ProcessManager {

public:

    AtlasLabels m_labels;

    QString m_inputDir, m_outputDir;
    QString m_atlasNifti;
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


#endif // AREAFINDER3D_H
