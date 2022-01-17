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
#ifndef PROCESSMANAGERFACTORY_H
#define PROCESSMANAGERFACTORY_H

#include "source/ProcessManager/processmanagerpcounter.h"
#include "source/ProcessManager/processmanagertransform.h"
#include "source/ProcessManager/processmanagerautocontrast.h"
#include "source/ProcessManager/processmanagertiffcreator.h"
#include "source/ProcessManager/processmanagerresize.h"
#include "source/ProcessManager/processmanagerneuroglancer.h"

class ProcessManagerFactory {
public:
    static ProcessManager* CreateProcessManager(QString pm_type) {
        if (pm_type.toLower() == "transform")
            return new ProcessManagerTransform();
        if (pm_type.toLower() == "quantifier")
            return new ProcessManagerPCounter();
//        if (pm_type.toLower() == "quantifier_advanced")
  //          return new ProcessManagerPCounter();
        if (pm_type.toLower() == "autocontrast")
            return new ProcessManagerAutoContrast();
        if (pm_type.toLower() == "tiffcreator")
            return new ProcessManagerTiffCreator();
        if (pm_type.toLower() == "resize")
            return new ProcessManagerResize();
        if (pm_type.toLower() == "neuroglancer")
            return new ProcessManagerNeuroglancer();

        return nullptr;
    }


};


#endif // PROCESSMANAGERFACTORY_H
