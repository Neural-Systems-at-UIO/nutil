#ifndef PROCESSMANAGERNG_H
#define PROCESSMANAGERNG_H

#include "processmanager.h"
#include "processmanagertiffcreator.h"


class ProcessManagerNG : public ProcessManagerTiffCreator {
public:

    ProcessManagerNG();
    ~ProcessManagerNG() {

    }
    bool m_isPercent = false;
//    bool Build(NutilTemplate* data) override;
    void Execute() override;
    void ReadHeader(NutilTemplate* data) override;
    bool Verify() override { return true; }

};

#endif // PROCESSMANAGERNG_H
