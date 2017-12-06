#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QFileDialog>
#include <QDebug>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    m_updateThread = new UpdateThread();
    connect(m_updateThread, SIGNAL(TextChanged(QString)), this, SLOT(OnInfoTextChanged(QString)));
    m_updateThread->Init(&m_nauto);
    m_updateThread->start();

}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_btnLoad_clicked()
{

    QString fileName = QFileDialog::getOpenFileName(this,
                                                    tr("Open Excel document"), "..\\TestData\\", tr("Excel Files (*.xls)"));

    m_nauto.Load(fileName);
    UpdateError();

}

void MainWindow::on_btnStart_clicked()
{
    if (!m_nauto.m_book) {
        Error("No file loaded!");
        return;
    }

    int sheetNo = ui->lneSheet->text().toInt();
    m_nauto.m_sheetIndex = sheetNo;
    //m_nauto.Execute();
    m_workerThread = new WorkerThread();
    m_workerThread->Init(&m_nauto);
    m_workerThread->start();
    UpdateError();


}

void MainWindow::Error(QString q)
{
    m_nauto.m_error = q;
    UpdateError();

}



void MainWindow::UpdateError()
{
    if (m_nauto.m_error!="")
        ui->txtError->setText(m_nauto.m_error);
    m_nauto.m_error = "";
}

void MainWindow::Update()
{
    //m_nauto.BuildInfo();
    //ui->txtInfo->setText(m_nauto.m_mainInfo);
}

void MainWindow::AppQuit()
{
    close();
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
    QApplication::quit();
}

void MainWindow::closeEvent(QCloseEvent * event)
{
    AppQuit();
}
void MainWindow::OnInfoTextChanged(QString info)
{
    ui->txtInfo->setText(info);
}
