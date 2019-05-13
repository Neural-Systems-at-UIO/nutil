#ifndef PROCESSMANAGERPCOUNTER_H
#define PROCESSMANAGERPCOUNTER_H

#include "source/ProcessManager/processmanager.h"
#include "source/IO/xmlanchor.h"

class ProcessManagerPCounter : public ProcessManager {

public:

    AtlasLabels m_labels;

    QString m_inputDir, m_outputDir;
    QString m_atlasDir;
    QString m_labelFile;
    QString m_anchorFile;
    QString m_reportSheetName;
    QString m_units = "mm";

    int m_pixelCutoff;
    int m_pixelCutoffMax;
    float m_areaScale = 1;

    float m_niftiSize;
    float m_xyzScale;


    bool m_outputNifti = false;
    bool m_output3DPoints = false;


    QVector3D m_colorThreshold  = QVector3D(255,255,255);
    QVector3D m_customMaskInclusionColors  = QVector3D(255,255,255);

    bool m_useCustomMask = false;

    QString m_reportType ="all";

    float m_areaSplitting = 0;

    Reports reports;

    XMLAnchor m_xmlAnchor;

    void LoadXML();
    bool Build(LSheet* m_sheet) override;
    void Execute() override; //(QString compression, QColor background, bool autoClip, int thumbnailSize, QString thumbType);
    void ReadHeader(LSheet* m_sheet, LBook* book) override;

    void GenerateReports(LSheet* m_sheet);
    bool Verify() override { return true; }

};


#endif // PROCESSMANAGERPCOUNTER_H
