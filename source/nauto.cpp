#include "nauto.h"
#include <stdio.h>
#include <iostream>
#include <QDebug>
#include "source/util/util.h"
#include "source/ProcessManager/processmanagerfactory.h"
#include "source/data.h"

using namespace std;

Nauto::Nauto(QString filename, int sheetIndex)
{
    m_sheetIndex = sheetIndex;
    m_filename = filename;
}

Nauto::Nauto(QString filename)
{
    m_filename = filename;
}

Nauto::Nauto()
{

}

void Nauto::Load(QString filename)
{
    if (m_book)
        delete m_book;
    m_book = new LBookXlnt();
    m_filename = filename;
    if (!QFileInfo(filename).exists()) {
        LMessage::lMessage.Error("Could not find file " + filename);
        return;
    }
   m_book->Load(filename);
}

void Nauto::Execute()
{
    if (m_status!=Status::Idle) {
        LMessage::lMessage.Error("Cannot start new job before previous is finished");
        return;
    }


    if (!m_book) {
        LMessage::lMessage.Error("No excel document loaded.");
        return;
    }
    m_sheet = m_book->GetSheet(m_sheetIndex);
/*    if(!m_sheet)
    {
        LMessage::lMessage.Error(m_book->errorMessage());
    }
*/
    LMessage::lMessage.Log("******** Reading global header");
    ReadHeader();
    LMessage::lMessage.Log("******** Type of Nutil operation: " + m_type );

    m_status = Status::Working;
    Util::CancelSignal = false;

    if (m_pm!=nullptr)
        delete m_pm;

    m_pm = ProcessManagerFactory::CreateProcessManager(m_type);
    if (m_pm==nullptr) {
        LMessage::lMessage.Error("Unknown operation type specified in sheet: "+m_type);
        m_status = Status::Idle;
        return;
    }

    m_pm->m_numProcessors = m_numThreads;

    LMessage::lMessage.Log("******** Reading local header");
    m_pm->ReadHeader(m_sheet, m_book);
    if (Data::data.abort) {
        m_status = Status::Idle;
        return;
    }

    LMessage::lMessage.Log("******** Building");
    if (m_pm->Build(m_sheet)) {
        LMessage::lMessage.Log("******** Executing");
        m_pm->Execute();

    }
    else
        m_status = Status::Idle;

    m_status = Status::Idle;

    LMessage::lMessage.EndOK();
    // Execute stuff
    if (m_status != Status::Idle)
        m_status = Status::Finished;
}

void Nauto::ReadHeader()
{
    xlnt::column_t t;
    m_type = m_sheet->readStr(0,1);
    m_batchName = m_sheet->readStr(1,1);

}


/*void Nauto::ExecuteAutoContrast()
{
    m_pm.m_processItems.clear();
    QDirIterator it(m_inputDir, QStringList() << "*.tif", QDir::Files);
    while (it.hasNext()) {
        QString inFileFull = it.next();
        QStringList l = inFileFull.split('/');
        QString inFile = l[l.length()-1];
        m_pm.m_processItems.append(new ProcessItem(m_inputDir+  inFile, m_outputDir+ inFile, 0, 0, "", "m_outputDir"));
        qDebug() << "Added " << inFile << " for AutoContrast processing";
    }
    m_pm.ExecuteAutoContrast(m_compression, m_background);

}
*/


void Nauto::BuildInfo()
{
    if (m_status == Status::Idle) {
        m_mainInfo = "No job loaded.";
        return;
    }



    QString t = "";
    t = t + "Batch <b>'" + m_batchName + "'</b> type <b>" + m_type + "</b><br>";
//    t = t + "Converting from <b>" + m_inputDir + "</b> to <b>"  + m_outputDir + "</b> with saved compression <b>" + m_compression + "</b><br>";
//    t = t + "Background color: (" + QString::number(m_background.red()) + ", " + QString::number(m_background.green()) + ", " + QString::number(m_background.blue()) + ")<br>";

//    t = t + "Total amou: " + QString::number(m_pm.m_processes.length()) + " \n";

    t = t +"<br>";
    float total = 0;

    for (int i=0;i<m_pm->m_processes.length();i++) {
        float progress = m_pm->m_processes[i]->getProgress();
        total+=min(progress,100.0f);
        if (progress<100 && progress >0)
        {
            //float degrees = m_pm.m_processItems[i]->m_angle;
            t = t + "Worker " +QString::number(i) + ": " + m_pm->m_processItems[i]->m_inFile + " [ <b>" +  QString::number( progress, 'f', 1 ) + "% </b>] " + m_pm->m_processes[i]->m_infoText;
            t = t + "<br>";
        }
    }
    if (m_status == Status::Working)
        m_elapsedTime = Util::globalTimer.elapsed();

    total/=m_pm->m_processes.length();
    int totalTime = (m_elapsedTime )/(total/100.0);

    t+=Data::data.m_globalMessage + "<br><br>";
    t+="Total: [ <b><font size=\"+1\">"+ QString::number(total,'f', 1)+ "% </font></b>] <br>";
    t+="Elapsed: "+ Util::MilisecondToString(m_elapsedTime) +" / <b> <br>";// + Util::MilisecondToString(totalTime) + "</b> <br>";

    if (m_status == Status::Finished) {
        t+="<br>Job is finished and Nutil can be safely closed!<br>";
    }


    m_mainInfo = t;



}

void Nauto::Abort()
{
    //m_pm.Abort();
}

void Nauto::Release()
{
    if (m_book)
        delete m_book;

    m_book = nullptr;
}

QStringList Nauto::getSheetList()
{
    return m_book->sheet_titles();
}

Nauto::~Nauto()
{
    Release();
}
