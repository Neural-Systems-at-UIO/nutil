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
