#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QFileDialog>
#include <QDebug>
#include "source/dialogtiff.h"

float MainWindow::Version = 0.12;

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

    ui->lblMain->setText("NeSys Utilities " + QString::number(Version));
    ui->lblNewt->setPixmap(QPixmap ("://images/Resources/newt.png"));
 //   QPixmap pixmap = QPixmap ("://my_image.png");

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
    if (!m_nauto.m_book) {
        LMessage::lMessage.Error("No file loaded!");
        return;
    }

    m_nauto.m_sheetIndex = ui->cmbSheets->currentIndex();;
    //m_nauto.Execute(); // Non-threaded
    m_workerThread = new WorkerThread();
    m_workerThread->Init(&m_nauto);
    m_workerThread->start();
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
    ui->cmbSheets->clear();
    ui->cmbSheets->addItems(m_nauto.getSheetList());
}

void MainWindow::closeEvent(QCloseEvent * event)
{
    AppQuit();
}
void MainWindow::OnInfoTextChanged(QString info)
{
    ui->txtInfo->setText(info);
}

void MainWindow::OnMessageTextChanged(QString msg)
{
    ui->txtError->setText(msg);
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
