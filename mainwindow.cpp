#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QFileDialog>
#include <QDebug>
#include "source/dialogtiff.h"
#include <QDesktopServices>
#include <QTimer>






float MainWindow::Version = 0.403;

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    m_updateThread = new UpdateThread();
    connect(m_updateThread, SIGNAL(TextChanged(QString)), this, SLOT(OnInfoTextChanged(QString)));
    connect(m_updateThread, SIGNAL(MessageChanged(QString)), this, SLOT(OnMessageTextChanged(QString)));
    connect(&m_nt, SIGNAL(emitUpdate()), this, SLOT(on_EmitUpdate()));
    connect(&m_nt, SIGNAL(emitRePopulate()), this, SLOT(on_RePopulate()));
    m_nauto = QSharedPointer<Nauto>(new Nauto());
    m_updateThread->Init(m_nauto);
    m_updateThread->start();
    Data::data.m_settings = &m_settings;
#ifdef IS_BETA
    ui->lblMain->setText("NeSys Utilities BETA " + QString::number(Version) +"\nFor internal use only.");
#else
    ui->lblMain->setText("NeSys Utilities " + QString::number(Version));
#endif

//    ui->lblNewt->setPixmap(QPixmap ("://images/Resources/newt.png"));
 //   QPixmap pixmap = QPixmap ("://my_image.png");


    m_nt.m_eventFilter = this;
    m_settings.filename = "nutil.ini";
    if (QFile::exists(m_settings.filename))
        m_settings.Load(m_settings.filename);

    DefaultSettings();

    ui->leProcessors->setText(QString::number(omp_get_max_threads()));
    QStringList l = m_settings.getStringList("recent_files");
    if (l.count()!=0) {
        Load(l[0]);
    }
    UpdateRecentList();

}

MainWindow::~MainWindow()
{
    delete ui;
}


/*
 *
 *  MainWindow::UpdateRecentList
 *  Parameters: none
 *  This method will update the recent list of the main window
 *
 *
 * */

void MainWindow::UpdateRecentList()
{

    if (m_nt.m_openFile!="") {
        QStringList lst = m_settings.getStringList("recent_files");
        lst.removeAll(m_nt.m_openFile);
        lst.insert(0,m_nt.m_openFile);
        m_settings.setStringList("recent_files",lst);
    }


    QStringList lst = m_settings.getStringList("recent_files");

    ui->lstRecent->clear();
    for (QString s: lst) {
        QString small = s;
        small = small.replace("\\","/");
        small = small.split("/").last();
        QListWidgetItem* wi = new QListWidgetItem(small);
        wi->setData(Qt::UserRole,s);
        ui->lstRecent->addItem(wi);
    }

    m_settings.Save();
}

void MainWindow::Load(QString f)
{
    m_nt.Load(f);
    m_nt.Populate(ui);

    //    on_EmitUpdate();
}


/*void MainWindow::on_btnLoad_clicked()
{

    QString fileName = QFileDialog::getOpenFileName(this,
                                                    tr("Open Excel document"), "..\\TestData\\", tr("Excel Files (*.xlsx)"));
    if (fileName=="")
        return;
    m_nauto->Load(fileName);
    FillSheetCombo();
}
*/

void MainWindow::on_btnStart_clicked()
{
    LMessage::lMessage.Clear();


    if (m_nt.m_openFile=="")
        on_btnSave_clicked();

    if (m_nt.m_openFile == "")
        return;

    m_timer = QElapsedTimer();
     m_timer.start();

//    while(m_workerThread->isRunning())
  //      QThread::sleep(1000);


    m_nauto->m_numThreads = ui->leProcessors->text().toInt();
    m_nauto->m_data = &m_nt;
    if (m_workerThread==nullptr)
        m_workerThread = QSharedPointer<WorkerThread>(new WorkerThread());
    m_workerThread->Init(m_nauto);
    m_workerThread->start();

    ui->tabMain->setCurrentIndex(2);

}




void MainWindow::PrivateUpdate()
{
    QWidget* w = new QWidget(this);
    w->setLayout(ui->gridTemplate);
    ui->scrollArea->setWidget(w);

}

void MainWindow::on_EmitUpdate()
{
     QTimer::singleShot(25, [=]() {
            PrivateUpdate();
     } );
}

void MainWindow::on_RePopulate()
{
    m_nt.Populate(ui);

}

void MainWindow::on_leProcessors_returnPressed()
{
    bool ok=true;
    int i=ui->leProcessors->text().toInt(&ok,10);
    if (!ok || i<1 || i>omp_get_max_threads()) {
        ui->leProcessors->setText(QString::number(omp_get_max_threads()));
        m_nauto->m_numThreads=omp_get_max_threads();
    }
}


void MainWindow::AppQuit()
{
    m_settings.Save();
    if (m_nt.m_openFile!="")
        m_nt.Save(m_nt.m_openFile);
    close();
    Abort();
    //Wait maximum 1 second
    if (m_updateThread) {
        m_updateThread->quit = true;
        if(!m_updateThread->wait(100)) {
            m_updateThread->terminate();
            qDebug() << "Forcing close updatethread";
        }
    }
    if (m_workerThread) {
        if(!m_workerThread->wait(100)) {
            m_workerThread->terminate();
            qDebug() << "Forcing close workerthread";
        }

    }
    m_nauto->Release();
    QApplication::quit();
}

void MainWindow::Abort()
{
    if (m_workerThread) {
        Util::CancelSignal = true;

        if (m_nauto->m_status != Nauto::Status::Idle) {

            while (!m_nauto->m_pm->m_processFinished) {
                m_workerThread->wait(200);
            }
            m_workerThread->terminate();
        }
        m_nauto->m_status = Nauto::Status::Idle;
    }

}


void MainWindow::closeEvent(QCloseEvent * event)
{
    AppQuit();
}

void MainWindow::UpdateInfoTimer()
{
    m_elapsedTimer=m_timer.elapsed();
    if (!(m_nauto->m_status == Nauto::Idle))
        ui->lblElapsedTime->setText("Elapsed time: " + Util::MilisecondToString(m_elapsedTimer));
}

void MainWindow::DefaultSettings()
{
    if (!m_settings.contains("fill_method"))
        m_settings.setString("fill_method","bfs");
}

bool MainWindow::eventFilter(QObject *obj, QEvent *event)
{
    if (event->type() == QEvent::Wheel)
    {
        event->ignore();
        return true;

    }
    return false;
}

void MainWindow::OnInfoTextChanged(QString info)
{
    ui->txtInfo->setText(info);
    UpdateInfoTimer();
}

void MainWindow::OnMessageTextChanged(QString msg)
{
    ui->txtError->setText(msg);
    ui->txtError->verticalScrollBar()->setValue(ui->txtError->verticalScrollBar()->maximum());
    if (msg.toLower().contains("error")) {
        QMessageBox msgBox;
        msgBox.setText("NUtil encountered an error. Please read the error messages carefully!");
        msgBox.exec();
    }
}


void MainWindow::on_btnStop_clicked()
{
    Abort();
}

void MainWindow::on_btnTiffEdit_clicked()
{
    DialogTiff* dTiff = new DialogTiff(this);
    dTiff->exec();
    delete dTiff;
}

void MainWindow::on_leProcessors_editingFinished()
{
    on_leProcessors_returnPressed();
}

void MainWindow::on_btnOpenFolder_clicked()
{
    QString s = Data::data.m_currentPath;
    s=s.replace("/","\\");
    s=s.replace("\\\\","\\");
//    qDebug() <<s;
    if (s!="")
//        QProcess::startDetached("explorer " + Data::data.m_currentPath);
        QDesktopServices::openUrl( QUrl::fromLocalFile(s) );
}

void MainWindow::on_actionSettings_triggered()
{
    DialogSettings* ds = new DialogSettings(nullptr, &m_settings);
    ds->exec();
}


void MainWindow::on_btnNew_clicked()
{

    DialogNewFile* newFile = new DialogNewFile();

    newFile->exec();

    if (!newFile->m_isOK)
        return;

    m_nt.LoadTemplate(":/Resources/text/"+newFile->m_type.toLower()+".txt");



    m_nt.Populate(ui);

/*    QWidget* w = new QWidget(this);
    w->setLayout(ui->gridTemplate);
    ui->scrollArea->setWidget(w);
*/
    m_nt.m_openFile = "";
    UpdateRecentList();
    delete newFile;

}


void MainWindow::on_btnSave_clicked()
{
    QString fileName = m_nt.m_openFile;
    if (fileName=="") {
        fileName = QFileDialog::getSaveFileName(this, tr("Save File"),
                                   m_nt.Get("name"),
                                   tr("Nutil (*.nut)"));
    }
    if (fileName!="") {
        m_nt.Save(fileName);
        UpdateRecentList();
    }
}

void MainWindow::on_btnLoad_2_clicked()
{
   QString fileName = QFileDialog::getOpenFileName(this, tr("Open File"),
                                   "",
                                   tr("Nutil (*.nut)"));

    if (fileName!="") {
        Load(fileName);
        UpdateRecentList();
    }
}

void MainWindow::on_lstRecent_itemDoubleClicked(QListWidgetItem *item)
{
    //    QObject::connect(ui->lstRecent, &QListWidget::doubleClicked, [=]() {
    if (ui->lstRecent->currentRow()==-1)
        return;

    QStringList lst = m_settings.getStringList("recent_files");

    QString v = lst[ui->lstRecent->currentRow()];

    if (v!=m_nt.m_openFile) {
        Load(v);
        UpdateRecentList();
    }

    //  });

}

void MainWindow::on_btnSaveAs_clicked()
{
    QString fileName = QFileDialog::getSaveFileName(this, tr("Save File As"),
                                   m_nt.Get("name"),
                                   tr("Nutil (*.nut)"));
    if (fileName!="") {
        m_nt.Save(fileName);
        UpdateRecentList();

    }
}

void MainWindow::on_pushButton_clicked()
{
    qApp->quit();
}

void MainWindow::on_btnClearList_clicked()
{
    m_settings.setStringList("recent_files",QStringList());
    UpdateRecentList();
}

void MainWindow::on_actionGenerate_validation_data_triggered()
{
    DialogGenerateData* d = new DialogGenerateData();

    d->exec();

    delete d;
}

void MainWindow::on_btnClearData_clicked()
{

    QMessageBox msgBox;
    msgBox.setText("Are you sure that you want to clear all data?");
    msgBox.setInformativeText("This action cannot be undone.");
    msgBox.setStandardButtons(QMessageBox::Ok | QMessageBox::Cancel);
    msgBox.setDefaultButton(QMessageBox::Cancel);
    if (msgBox.exec()==QMessageBox::Cancel)
        return;


    QString fileName = ":/Resources/text/"+ m_nt.Get("type").toLower()  +".txt";
    if (!QFile::exists(fileName))
        return;

    m_nt.LoadTemplate(fileName);
    m_nt.Populate(ui);
    m_nt.m_openFile = "";
    UpdateRecentList();

}

void MainWindow::on_actionNutil_Duplicator_triggered()
{
    m_nt.Duplicator("/home/leuat/code/nutildata/input/duptest");
}
