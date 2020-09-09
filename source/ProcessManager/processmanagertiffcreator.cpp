#include "processmanagertiffcreator.h"

ProcessManagerTiffCreator::ProcessManagerTiffCreator()
{


}

bool ProcessManagerTiffCreator::Build(NutilTemplate* data)
{

    m_processItems.clear();
    QDir directory(m_inputDir);
    QStringList images = directory.entryList(QStringList() << "*.jpg" << "*.png" <<"*.tiff" <<"*.tif",QDir::Files);
    for (QString filename: images) {
        QStringList inFileSplit = filename.split("/");
        QString inFile = (inFileSplit[inFileSplit.count()-1]);
        QFile test(m_inputDir+inFile);
        if(!test.exists()) {
            LMessage::lMessage.Error("Could not find file '" + inFile + "' for processing. Please fix input data and try again.");
            //m_status = Status::Idle;
            return false;
        }
        QString outFile = inFile.split(".").first()+".tif";

        m_processItems.append(QSharedPointer<ProcessItem>(new ProcessItem(m_inputDir+  inFile, m_outputDir+ outFile, 0, QPointF(1,1), outFile, m_outputDir)));
//        return true;
    }
    if (!Verify()) {
        m_processItems.clear();
        return false;
    }


    return true;

}

void ProcessManagerTiffCreator::Execute()
{
    m_processFinished = false;
    ClearProcesses();
    for (int i=0;i<m_processItems.length();i++) {
        m_processes.append(QSharedPointer<NutilProcess>(new NutilProcess()));
    }
    SetParameters();

    if (m_processes.length()==0)
        return;

    Util::globalTimer.restart();
    m_mainCounter = Counter(m_processes.length(),"",false);
#pragma omp parallel for

    for (int i=0;i<m_processes.length();i++) {
        QImage img;
        auto pi = m_processItems[i];
        img.load(pi->m_inFile);


        LTiff t;
        t.FromQIMage(pi->m_outFile,img,m_compression,m_tileSize, m_processes[i]->m_counter);
        //m_processes[i]->AutoContrast(pi->m_inFile, pi->m_outFile, m_compression, m_background, m_outputDir);
        LMessage::lMessage.Message("New tiled TIFF file: <font color=\"yellow\">"+pi->m_outFile+"</font>");

        m_mainCounter.Tick();
    }
    m_processFinished = true;

}

void ProcessManagerTiffCreator::ReadHeader(NutilTemplate* data)
{
    ProcessManager::ReadHeader(data);
    m_compression = data->Get("output_compression");
    m_inputDir = data->Get("tiffcreator_input_dir")+"/";
    m_outputDir = data->Get("tiffcreator_output_dir")+"/";
    m_tileSize = data->Get("tiffcreator_size").toFloat();

/*    m_compression = m_sheet->readStr(2,1);
    m_inputDir = m_sheet->readStr(3,1);
    m_outputDir = m_sheet->readStr(4,1);
    m_tileSize = m_sheet->readNum(5,1);
*/


}
