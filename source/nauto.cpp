#include "nauto.h"
#include <stdio.h>
#include <iostream>
#include <QDebug>
#include "source/util/util.h"
#include "source/ProcessManager/processmanagerfactory.h"
#include "source/data.h"
#include "mainwindow.h"
using namespace std;
/*
Nauto::Nauto(QString filename, int sheetIndex)
{
    m_sheetIndex = sheetIndex;
    m_filename = filename;
}

Nauto::Nauto(QString filename)
{
    m_filename = filename;
}
*/
Nauto::Nauto()
{

}

Nauto::Nauto(NutilTemplate *temp)
{
     m_data  = temp;
}
/*
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

   LSheet* sheet = m_book->GetSheet("Nutil_info");
   if (sheet==nullptr) {
       LMessage::lMessage.Error("Excel sheet does not contain a 'Nutil_info' sheet. Are you sure this is is a nutil template file?");
       delete m_book;
       m_book = nullptr;
       return;

   }
   if (sheet->readStr(14,4).toFloat()!=MainWindow::Version ) {
       LMessage::lMessage.Error("The excel template ("+QString::number(sheet->readStr(14,4).toFloat()) + ") version is not compatible with the current version of Nutil ("+QString::number(MainWindow::Version)+")");
       delete m_book;
       m_book = nullptr;
       return;

   }

}
*/
void Nauto::Execute()
{
    if (m_status!=Status::Idle) {
        LMessage::lMessage.Error("Cannot start new job before previous is finished");
        return;
    }


/*    if (!m_book) {
        LMessage::lMessage.Error("No excel document loaded.");
        return;
    }
    m_sheet = m_book->GetSheet(m_sheetIndex);
    */
/*    if(!m_sheet)
    {
        LMessage::lMessage.Error(m_book->errorMessage());
    }
*/
    ReadHeader();
    LMessage::lMessage.Log("Type of operation: " + m_type );
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
    m_pm->m_excelInputFilename = m_filename;
    m_pm->m_numProcessors = m_numThreads;

    m_pm->ReadHeader(m_data);

    if (Data::data.abort) {
        m_status = Status::Idle;
        return;
    }

    if (m_pm->Build(m_data)) {

        // Verify memory limits
        float memRequired = m_pm->CalculateRamNeededInGB();
        float totalMemory = Util::getAmountOfInstalledMemory();
        float freeMemory = Util::getFreeRam();
        float total = memRequired/freeMemory;
        LMessage::lMessage.Message("Required memory: " + QString::number(memRequired)+" GB. Free memory : "+QString::number(freeMemory)+ " GB from a total of "+QString::number(totalMemory) +" GB installed ("+(QString::number((int)(total*100))) +" %) usage");
        if (total>0.9 && total<=1.0)
            LMessage::lMessage.Message("Warning! You are close to exceeding maximum memory usage. Consider lowering the number of threads.");
        if (total>1) {
            LMessage::lMessage.Error("You are exceeding the memory limitations of this system. Please lower the number of threads, or reduce size of input files.");
        } else {
            LMessage::lMessage.Log("Executing...");
            m_pm->Execute();
        }
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
 //   xlnt::column_t t;
    if (m_data==nullptr)
        return;
    m_type = m_data->Get("type");
    m_batchName = m_data->Get("name");

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

    if (Data::data.m_globalMessage=="")
        t+="<br>";
    else
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
/*    if (m_book)
        delete m_book;

    m_book = nullptr;*/
}
/*
QStringList Nauto::getSheetList()
{
    return m_book->sheet_titles();
}
*/
Nauto::~Nauto()
{
    Release();
}
