#ifndef PROCESSMANAGERPCOUNTER_H
#define PROCESSMANAGERPCOUNTER_H

#include "source/ProcessManager/processmanager.h"
#include "source/IO/xmlanchor.h"
#include <QRegularExpression>

class ProcessManagerPCounter : public ProcessManager {

public:

    AtlasLabels m_labels;

    QString m_inputDir, m_outputDir;
    QString m_atlasDir;
    QString m_labelFile;
    QString m_anchorFile;
    QString m_reportSheetName;
    QString m_units = "mm";
    QString m_patternType;
    QStringList m_files;


    QString m_reportDirectory = "Reports";
    QString m_imageDirectory = "Images";
    QString m_coordinateDirectory = "Coordinates";

    int m_pixelCutoff;
    int m_pixelCutoffMax;
    float m_areaScale = 1;

    float m_niftiSize;
    float m_xyzScale = 1.0;


    bool m_outputNifti = false;
    QString m_output3DPoints = "no";
    QString m_outputFileType = "xlsx";

    QString m_dataType="quicknii";

    QVector3D m_colorThreshold  = QVector3D(255,255,255);
    QColor m_customMaskInclusionColors  = QColor(255,255,255,255);

    bool m_useCustomMask = false;

    QString m_reportType ="all";

    float m_areaSplitting = 0;

    Reports reports;

    float CalculateRamNeededInGB() override;

    XMLAnchor m_xmlAnchor;

    void LoadXML();
    bool Build(NutilTemplate* data) override;
    void Execute() override; //(QString compression, QColor background, bool autoClip, int thumbnailSize, QString thumbType);
    void ReadHeader(NutilTemplate* data) override;

    void GenerateReports(LSheet* m_sheet);
    bool Verify() override { return true; }

};


#endif // PROCESSMANAGERPCOUNTER_H
