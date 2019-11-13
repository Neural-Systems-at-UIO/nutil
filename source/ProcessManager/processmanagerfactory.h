#ifndef PROCESSMANAGERFACTORY_H
#define PROCESSMANAGERFACTORY_H

#include "source/ProcessManager/processmanagerpcounter.h"
#include "source/ProcessManager/processmanagertransform.h"
#include "source/ProcessManager/processmanagerautocontrast.h"
#include "source/ProcessManager/processmanagertiffcreator.h"
#include "source/ProcessManager/processmanagerresize.h"

class ProcessManagerFactory {
public:
    static ProcessManager* CreateProcessManager(QString pm_type) {
        if (pm_type.toLower() == "transform")
            return new ProcessManagerTransform();
        if (pm_type.toLower() == "quantifier_basic")
            return new ProcessManagerPCounter();
        if (pm_type.toLower() == "quantifier_advanced")
            return new ProcessManagerPCounter();
        if (pm_type.toLower() == "autocontrast")
            return new ProcessManagerAutoContrast();
        if (pm_type.toLower() == "tiffcreator")
            return new ProcessManagerTiffCreator();
        if (pm_type.toLower() == "resize")
            return new ProcessManagerResize();

        return nullptr;
    }


};


#endif // PROCESSMANAGERFACTORY_H
