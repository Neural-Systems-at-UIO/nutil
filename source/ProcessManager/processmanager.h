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
#ifndef PROCESSMANAGER_H
#define PROCESSMANAGER_H

#include <QVector>
#include "source/ProcessManager/nutilprocess.h"
//#include "libxl.h"
#include "source/util/lmessage.h"
#include "source/util/atlaslabel.h"
#include "source/ProcessManager/report.h"
#include "source/ProcessManager/processitem.h"
#include "source/util/lparameter.h"
#include "source/IO/nutiltemplate.h"
#include <QDirIterator>

class ProcessManager
{
public:
    ProcessManager();
    virtual ~ProcessManager() {

    }
    LParameter m_parameters;

    bool m_processFinished;

    QVector<QSharedPointer<ProcessItem>> m_processItems;
    QVector<QSharedPointer<NutilProcess>> m_processes;


    QString m_excelInputFilename="";
    Counter m_mainCounter;
    QColor m_background = QColor(255,255,255,255);

    int m_numProcessors = -1;

 //   QString m_globalMessage = "";

    virtual bool Build(NutilTemplate* data) = 0;
    virtual void Execute() = 0;
    virtual void ReadHeader(NutilTemplate* data) { }
    virtual float CalculateRamNeededInGB()  { return 0;}





    virtual bool Verify() = 0;
//    void ExecuteAutoContrast(QString compression, QColor background);

    void ClearProcesses();
    void ClearItems();
    void SetParameters();


    void Abort() {
        ClearProcesses();
        ClearItems();

    }

};






#endif // PROCESSMANAGER_H
