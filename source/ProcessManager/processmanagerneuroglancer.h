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
#ifndef PROCESSMANAGERNEUROGLANCER_H
#define PROCESSMANAGERREUROGLANCER_H

#include "processmanager.h"
#include "processmanagertiffcreator.h"


class ProcessManagerNeuroglancer : public  ProcessManagerTiffCreator {
public:

    ProcessManagerNeuroglancer();
    ~ProcessManagerNeuroglancer() {

    }
    bool m_isPercent = false;
//    bool Build(NutilTemplate* data) override;
    void Execute() override;
    void ReadHeader(NutilTemplate* data) override;
    bool Verify() override { return true; }
    bool Build(NutilTemplate* data) override;


};

#endif // PROCESSMANAGERRESIZE_H
