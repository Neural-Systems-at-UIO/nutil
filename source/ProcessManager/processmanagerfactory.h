#ifndef PROCESSMANAGERFACTORY_H
#define PROCESSMANAGERFACTORY_H

#include "source/ProcessManager/processmanagerpcounter.h"
#include "source/ProcessManager/processmanagertransform.h"
#include "source/ProcessManager/processmanagerautocontrast.h".h"

class ProcessManagerFactory {
public:
    static ProcessManager* CreateProcessManager(QString pm_type) {
        if (pm_type.toLower() == "rotation")
            return new ProcessManagerTransform();
        if (pm_type.toLower() == "objectcounter")
            return new ProcessManagerPCounter();
        if (pm_type.toLower() == "autocontrast")
            return new ProcessManagerAutoContrast();

        return nullptr;
    }


};


#endif // PROCESSMANAGERFACTORY_H
