#include "processmanagerneuroglancer.h"
#include "source/util/neuroglancer.h"

ProcessManagerNeuroglancer::ProcessManagerNeuroglancer()
{

}

void ProcessManagerNeuroglancer::Execute()
{
    if (!QDir(m_outputDir).exists())
        QDir().mkdir(m_outputDir);

    m_processFinished = false;
    ClearProcesses();
    for (int i=0;i<m_processItems.length();i++) {
        m_processes.append(QSharedPointer<NutilProcess>(QSharedPointer<NutilProcess>(new NutilProcess())));
    }
    SetParameters();

    if (m_processes.length()==0)
        return;

    Util::globalTimer.restart();

    m_mainCounter = Counter(m_processes.length(),"",false);

    for (int i=0;i<m_processes.length();i++) {
        QSharedPointer<ProcessItem> pi = m_processItems[i];
        NeuroGlancer ng(pi->m_inFile);
        ng.LoadAllChunks();
        qDebug() << pi->m_outFile;
        ng.m_img.save(pi->m_outFile);


    }



    #pragma omp parallel for

    for (int i=0;i<m_processes.length();i++) {

    }
    m_processFinished = true;

}


void ProcessManagerNeuroglancer::ReadHeader(NutilTemplate* data)
{
    ProcessManager::ReadHeader(data);
//    m_compression = data->Get("resize_output_compression");
    m_inputDir = data->Get("resize_input_dir")+"/";
    m_outputDir = data->Get("resize_output_dir")+"/";
    m_tileSize = data->Get("resize_size").toFloat();
    m_isPercent = data->Get("resize_type").toLower().trimmed()=="percent";

}

bool ProcessManagerNeuroglancer::Build(NutilTemplate *data)
{

    m_processItems.clear();
    QDir directory(m_inputDir);
    QStringList images = directory.entryList(QDir::Dirs | QDir::NoDotAndDotDot);
    for (QString filename: images) {
        QStringList inFileSplit = filename.split("/");
        QString inFile = (inFileSplit[inFileSplit.count()-1]);
        QString outFile = inFile.split(".").first()+".png";
        inFile+="/";

        m_processItems.append(QSharedPointer<ProcessItem>(new ProcessItem(m_inputDir+  inFile, m_outputDir+ outFile, 0, QPointF(1,1), outFile, m_outputDir)));
        //        return true;
    }

    if (images.count()==0) {
        LMessage::lMessage.Error("Could not find any directories files in the specified directory. Please check your input parameters.");
        //m_status = Status::Idle;
        return false;

    }

    if (!Verify()) {
        m_processItems.clear();
        return false;
    }


    return true;

}
