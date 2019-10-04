#ifndef PROCESSMANAGERTIFFCREATOR_H
#define PROCESSMANAGERTIFFCREATOR_H

#include "source/ProcessManager/processmanager.h"

class ProcessManagerTiffCreator : public ProcessManager {
public:
    QString m_inputDir, m_outputDir;
    QString m_compression = "jpg";
    int m_tileSize;

    ProcessManagerTiffCreator();

    bool Build(NutilTemplate* data) override;
    void Execute() override;
    void ReadHeader(NutilTemplate* data) override;
    bool Verify() override { return true; }

};

#endif // PROCESSMANAGERTIFFCREATOR_H
