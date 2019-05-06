#ifndef PROCESSMANAGERFACTORY_H
#define PROCESSMANAGERFACTORY_H

#include "source/ProcessManager/processmanagerpcounter.h"
#include "source/ProcessManager/processmanagertransform.h"
#include "source/ProcessManager/processmanagerautocontrast.h"
#include "source/ProcessManager/processmanagertiffcreator.h"

class ProcessManagerFactory {
public:
    static ProcessManager* CreateProcessManager(QString pm_type) {
        if (pm_type.toLower() == "transform")
            return new ProcessManagerTransform();
        if (pm_type.toLower() == "quantifier")
            return new ProcessManagerPCounter();
        if (pm_type.toLower() == "autocontrast")
            return new ProcessManagerAutoContrast();
        if (pm_type.toLower() == "tiffcreator")
            return new ProcessManagerTiffCreator();

        return nullptr;
    }


};


#endif // PROCESSMANAGERFACTORY_H
