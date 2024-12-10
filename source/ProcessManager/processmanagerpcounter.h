/*
Nutil - Neuroimaging utilities - aims to both simplify and streamline the mechanism of
pre-and-post processing 2D brain image data. Nutil is developed as a stand-alone application
that runs on all operating systems with a minimalistic user interface requiring little-to-no
experience to execute.

Copyright (C) 2020 nicolaas.groeneboom@gmail.com

This program is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 3 of the License, or
(at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/
#ifndef PROCESSMANAGERPCOUNTER_H
#define PROCESSMANAGERPCOUNTER_H

#include "source/ProcessManager/processmanager.h"
#include "source/IO/xmlanchor.h"
#include <QRegularExpression>

class ProcessManagerPCounter : public ProcessManager {

public:
    ~ProcessManagerPCounter() {

    }

    AtlasLabels m_labels;

    QString m_inputDir, m_outputDir, m_maskDir;
    QString m_atlasDir;
    QString m_labelFile;
    QString m_labelType;
    QString m_anchorFile;
    QString m_regexp;
    QString m_reportSheetName;
    QString m_units = "mm";
    QString m_patternType;
    QString m_overrideLabelFile="";
    QStringList m_files;
    QString m_prefix ="";

    double m_coordinateRandomSpread = 0.0;


    QMap<QString, QString> atlasQuickniiMap{
        {"ABA_Mouse_CCFv3_2015_25um", "Allen Mouse Brain Atlas CCFv3 (2015)"},
        {"ABA_Mouse_CCFv3_2017_25um", "Allen Mouse Brain Atlas CCFv3 (2017)"},
        {"WHS_SD_Rat_v2_39um", "WHS Atlas Rat v2"},
        {"WHS_SD_Rat_v3_39um", "WHS Atlas Rat v3"},
        {"WHS_SD_Rat_v4_39um", "WHS Atlas Rat v4"},
        {"WHS_Rat_v2_39um", "WHS Atlas Rat v2"},
        {"WHS_Rat_v3_39um", "WHS Atlas Rat v3"},
        {"WHS_Rat_v4_39um", "WHS Atlas Rat v4"},
        {"WHS_Rat_v4_39um", "WHS Atlas Rat v4"},
        {"Kim_UnifiedMouse_v1_20x100um", "Kim Unified Adult Mouse Brain Atlas (2019)"},
        };


    QString m_reportDirectory = "Reports";
    QString m_plotsDirectory = "Plots";
    QString m_imageDirectory = "Images";
    QString m_coordinateDirectory = "Coordinates";
    QString m_scriptDirectory = "Scripts";

    int m_pixelCutoff;
    int m_pixelCutoffMax;
    float m_areaScale = 1;
    bool m_coordinates_single_point = false;

    float m_niftiSize;
    float m_xyzScale = 1.0;
    bool m_outputRegionNumbers = true;

    bool m_outputNifti = false;
    QString m_output3DPoints = "no";
    QString m_outputFileType = "xlsx";
    bool m_displayLabelID = false;

    enum DataType {QUINT, NONE };
    DataType m_dataType=QUINT;
    enum ReportType {REPORTTYPE_ALL, REPORTTYPE_NONE };
    ReportType m_reportType = REPORTTYPE_ALL;

//    QString m_dataType="quint";

    QVector3D m_colorThreshold  = QVector3D(255,255,255);
    QColor m_customMaskInclusionColors  = QColor(255,255,255,255);

    bool m_useCustomMask = false;

//    QString m_reportType ="all";
    QString m_customRegionType;

    float m_areaSplitting = 0;

    Reports reports;

    float CalculateRamNeededInGB() override;




    AbstractAnchor* m_xmlAnchor = nullptr;
    void LoadXML(NutilTemplate* data);
    bool Build(NutilTemplate* data) override;
    void Execute() override; //(QString compression, QColor background, bool autoClip, int thumbnailSize, QString thumbType);
    void ReadHeader(NutilTemplate* data) override;
    void SetupFakeReports();
    void CleanupFakeReports();
    void BuildReports();
    void BuildWithMasks();
    void GenerateReports(QSharedPointer<LSheet> m_sheet);
    bool Verify() override { return true; }
    void GeneratePythonPlots();
    void CallPythonPlot(QString file, QString type, QString outputFile);
    void SaveCustomReportColors(QSharedPointer<LSheet> sheet, QString fname);
    void setupLabelFiles(NutilTemplate* data);

};


#endif // PROCESSMANAGERPCOUNTER_H
