#include "dialogtiff.h"
#include <QMouseEvent>
#include <QMessageBox>

DialogTiff::DialogTiff(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::DialogTiff)
{
    ui->setupUi(this);
    Data::data.abort = false;
    m_updateThread = new ImageUpdateThread(ui, &m_tif);
    connect(m_updateThread, SIGNAL(updateImageSignal()), this, SLOT(UpdateImage()));

    m_updateThread->start();
    m_guiThread = new UpdateGUIThread();

    connect(m_guiThread, SIGNAL(updateProgressSignal()), this, SLOT(UpdateProgress()));

    m_guiThread->start();


}

void UpdateGUIThread::run()
{
    while (!m_quit) {
        emit updateProgressSignal();
        QThread::msleep(10);
    }

}


DialogTiff::~DialogTiff()
{
    delete ui;
}

void DialogTiff::UpdateImage()
{
//    LColorList lst;
//    m_tif.ToQImage(lst,m_tif.m_qImage,m_updateThread->m_zoom, m_updateThread->m_currentPos );
    m_tif.ApplyToLabel(ui->lblImage);
}

void DialogTiff::UpdateProgress()
{
   ui->prgProgress->setValue(Data::data.percent*100.0);
}

void DialogTiff::on_btnClose_clicked()
{
    Data::data.abort = true;
    m_updateThread->m_quit = true;
    m_updateThread->quit();
    m_guiThread->m_quit = true;
    m_guiThread->quit();
    close();
}

void DialogTiff::on_btnOpen_clicked()
{
    QString fileName = QFileDialog::getOpenFileName(this,
                                                    tr("Open Tiled Tiff"), "", tr("Tiff files (*.tif *.tiff)"));
    if (fileName=="")
        return;

//    m_tif.Initialize(1024,768);
    m_tif.Initialize(320,200);
//    m_tif.Initialize(64,40);
    if (!m_tif.LoadTiff(fileName)) {
        QMessageBox msgBox;
        msgBox.setText("TIFF file is corrputed!");
        msgBox.exec();
        return;
    }
    qDebug() << "OK";
//    UpdateImage();
    m_updateThread->m_zoom = 0.1;
    m_updateThread->m_zoomCenter = QPointF(m_tif.m_tifs[0]->m_width/2, m_tif.m_tifs[0]->m_height/2);
    Data::data.Redraw();

}


void DialogTiff::mousePressEvent(QMouseEvent *e)
{
    if(e->buttons() == Qt::RightButton)
        m_updateThread->m_currentButton = 2;
    if(e->buttons() == Qt::LeftButton) {
        m_updateThread->m_currentButton = 1;

    }


}

void DialogTiff::mouseReleaseEvent(QMouseEvent *e)
{
    if (m_updateThread->m_currentButton==2)
        m_updateThread->m_currentButton = 0;
    else
    m_updateThread->m_currentButton = -1;

}

void DialogTiff::wheelEvent(QWheelEvent *event)
{
    float f = event->delta()/100.0f;

    //if (QApplication::keyboardModifiers() & Qt::ControlModifier)
    {
        m_updateThread->m_zoom *=1 - f*0.05;
        m_updateThread->m_zoom = min(m_updateThread->m_zoom, 1.0f);
        m_updateThread->m_zoom = max(m_updateThread->m_zoom, 0.001f);
        float t = 0.0f;
        m_updateThread->m_zoomCenter = (m_updateThread->m_zoomCenter*t + (1-t)*m_updateThread->m_currentPos);//*(2-2*m_zoom);
        Data::data.redrawOutput = true;


    }

}

void DialogTiff::keyPressEvent(QKeyEvent *e)
{

}

