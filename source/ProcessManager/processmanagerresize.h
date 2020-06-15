#ifndef PROCESSMANAGERRESIZE_H
#define PROCESSMANAGERRESIZE_H

#include "processmanager.h"
#include "processmanagertiffcreator.h"


class ProcessManagerResize : public ProcessManagerTiffCreator {
public:

    ProcessManagerResize();
    ~ProcessManagerResize() {

    }
    bool m_isPercent = false;
//    bool Build(NutilTemplate* data) override;
    void Execute() override;
    void ReadHeader(NutilTemplate* data) override;
    bool Verify() override { return true; }

};

#endif // PROCESSMANAGERRESIZE_H
