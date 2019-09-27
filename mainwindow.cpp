#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QFileDialog>
#include <QDebug>
#include "source/dialogtiff.h"
#include <QDesktopServices>


float MainWindow::Version = 0.3301;

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    m_updateThread = new UpdateThread();
    connect(m_updateThread, SIGNAL(TextChanged(QString)), this, SLOT(OnInfoTextChanged(QString)));
    connect(m_updateThread, SIGNAL(MessageChanged(QString)), this, SLOT(OnMessageTextChanged(QString)));
    m_updateThread->Init(&m_nauto);
    m_updateThread->start();
    Data::data.m_settings = &m_settings;
#ifdef IS_BETA
    ui->lblMain->setText("NeSys Utilities BETA " + QString::number(Version) +"\nFor internal use only. \nUse template version "+ QString::number(Version));
#else
    ui->lblMain->setText("NeSys Utilities " + QString::number(Version));
#endif
    ui->lblNewt->setPixmap(QPixmap ("://images/Resources/newt.png"));
 //   QPixmap pixmap = QPixmap ("://my_image.png");


    m_settings.filename = "nutil.ini";
    if (QFile::exists(m_settings.filename))
        m_settings.Load(m_settings.filename);

    DefaultSettings();

    ui->leProcessors->setText(QString::number(omp_get_max_threads()));
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_btnLoad_clicked()
{

    QString fileName = QFileDialog::getOpenFileName(this,
                                                    tr("Open Excel document"), "..\\TestData\\", tr("Excel Files (*.xlsx)"));
    if (fileName=="")
        return;
    m_nauto.Load(fileName);
    FillSheetCombo();
}

void MainWindow::on_btnStart_clicked()
{
    LMessage::lMessage.Clear();
    if (!m_nauto.m_book) {
        LMessage::lMessage.Error("No file loaded!");
        return;
    }
    m_timer = QElapsedTimer();
     m_timer.start();

    m_nauto.m_numThreads = ui->leProcessors->text().toInt();
    //m_nauto.m_sheetIndex = ui->cmbSheets->currentText();

    //m_nauto.Execute(); // Non-threaded
    m_workerThread = new WorkerThread();
    m_workerThread->Init(&m_nauto);
    m_workerThread->start();


}

void MainWindow::on_leProcessors_returnPressed()
{
    bool ok=true;
    int i=ui->leProcessors->text().toInt(&ok,10);
    if (!ok || i<1 || i>omp_get_max_threads()) {
        ui->leProcessors->setText(QString::number(omp_get_max_threads()));
        m_nauto.m_numThreads=omp_get_max_threads();
    }
}


void MainWindow::AppQuit()
{
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
    m_nauto.Release();
    QApplication::quit();
}

void MainWindow::Abort()
{
    if (m_workerThread) {

        Util::CancelSignal = true;

        if (m_nauto.m_status != Nauto::Status::Idle) {

            while (!m_nauto.m_pm->m_processFinished) {
                m_workerThread->wait(200);
            }
            m_workerThread->terminate();
        }
        delete m_workerThread;
        m_workerThread = nullptr;
        m_nauto.m_status = Nauto::Status::Idle;
    }

}

void MainWindow::FillSheetCombo()
{
    if (m_nauto.m_book==nullptr)
        return;
    //ui->cmbSheets->clear();
    //ui->cmbSheets->addItems(m_nauto.getSheetList());
}

void MainWindow::closeEvent(QCloseEvent * event)
{
    AppQuit();
}

void MainWindow::UpdateInfoTimer()
{
    m_elapsedTimer=m_timer.elapsed();
    if (!m_nauto.m_status == Nauto::Idle)
        ui->lblElapsedTime->setText("Elapsed time: " + Util::MilisecondToString(m_elapsedTimer));
}

void MainWindow::DefaultSettings()
{
    if (!m_settings.contains("fill_method"))
        m_settings.setString("fill_method","bfs");
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
//    m_nt.LoadTemplate(":/text/Resources/text/"+ui->cmbNew->currentText().toLower()+".txt");

    m_nt.LoadTemplate(":/Resources/text/transform.txt");
    m_nt.Populate(ui->gridTemplate);
    m_settings.setString("current_file", m_newFileName);
}


void MainWindow::on_btnSave_clicked()
{
    QString fileName = m_settings.getString("current_file");
    if (fileName==m_newFileName) {
        fileName = QFileDialog::getSaveFileName(this, tr("Save File"),
                                   "",
                                   tr("Nutil (*.nut)"));
    }
    m_nt.Save(fileName);
}

void MainWindow::on_btnLoad_2_clicked()
{
   QString fileName = QFileDialog::getOpenFileName(this, tr("Open File"),
                                   "",
                                   tr("Nutil (*.nut)"));

    m_nt.Load(fileName);
    m_nt.Populate(ui->gridTemplate);

}
