#ifndef PROCESSMANAGERAUTOCONTRAST_H
#define PROCESSMANAGERAUTOCONTRAST_H

#include "source/ProcessManager/processmanager.h"

class ProcessManagerAutoContrast : public ProcessManager {
public:
    QString m_inputDir, m_outputDir;
    QString m_compression = "jpg";
    float m_lowerThreshold;
    float m_middleThreshold;
    float m_forceStartZero;

    bool Build(LSheet* m_sheet) override;// {return true;}
    void Execute() override;
    void ReadHeader(LSheet* m_sheet, LBook* book) override;
    bool Verify() override { return true; }

};


#endif // PROCESSMANAGERAUTOCONTRAST_H
