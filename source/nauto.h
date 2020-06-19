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
#ifndef NAUTO_H
#define NAUTO_H

#include <QString>
#include <QColor>
#include <QStringList>
//#include "libxl.h"
#include "source/ProcessManager/processmanager.h"
#include "source/util/lmessage.h"
#include "source/LBook/lbook.h"
#include "source/LBook/lbookxlnt.h"
#include "source/IO/nutiltemplate.h"
#include <QSharedPointer>

//using namespace libxl;

class Nauto
{
private:

public:

    enum Status { Idle, Working, Finished };

/*      Book* m_book = nullptr;

    Sheet* m_sheet = nullptr;*/
//    LBook *m_book = nullptr;
//    LSheet* m_sheet = nullptr;
    NutilTemplate* m_data;



    QString m_filename;
    QString m_sheetIndex;
    int m_elapsedTime;
    QSharedPointer<ProcessManager> m_pm = nullptr;

    Counter m_mainCounter;

    int m_numThreads=1;

    Status m_status = Status::Idle;
    QString m_type;
    QString m_batchName;


    QString m_mainInfo;


/*    Nauto(QString filename, int shee);
    Nauto(QString filename);*/
    Nauto();
    Nauto(NutilTemplate* temp);


//    void Load(QString filename);
    void Execute();
    void ExecuteTransformation();
//    void ExecuteAutoContrast();
    void ExecutePCounter();
    void ReadHeader();
    void BuildInfo();
    void Abort();
    void Release();
 //   QStringList getSheetList();
    ~Nauto();
};

#endif // NAUTO_H
