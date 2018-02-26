#include "source/updatethread.h"

void ImageUpdateThread::UpdateDrawing()
{
    if (m_isPanning)
        return;

}

void ImageUpdateThread::UpdateMousePosition()
{
    if (m_tif->m_tifs.count()==0)
        return;

    QPointF pos = QCursor::pos() - ui->lblImage->mapToGlobal(ui->lblImage->rect().topLeft());
    QPointF center = QPointF(m_tif->m_tifs[0]->m_width/2, m_tif->m_tifs[0]->m_height/2);
    pos.setX(pos.x()/(float)ui->lblImage->width()*m_tif->m_tifs[0]->m_width);
    pos.setY(pos.y()/(float)ui->lblImage->height()*m_tif->m_tifs[0]->m_height);
    m_prevPos = m_currentPos;
    m_currentPos = QPoint(pos.x(), pos.y());
    m_currentPos = (m_currentPos-center)*m_zoom + center;
}

void ImageUpdateThread::UpdatePanning()
{

    m_isPanning = false;
    if (m_currentButton == 1/* && (QApplication::keyboardModifiers() & Qt::ShiftModifier)*/) {
        QPointF delta = (m_prevPos - m_currentPos);
        m_zoomCenter+=(QPointF)delta*0.5;
//        qDebug() << delta;
        m_isPanning = true;
        Data::data.redrawOutput = true;
    }


}




void ImageUpdateThread::UpdateImage()
{
    if (m_tif->m_tifs.count()==0)
        return;

    m_tif->ToQImage(m_tif->m_colorList, m_tif->m_qImage, m_zoom, m_zoomCenter);
    m_pixMapImage.convertFromImage(*m_tif->m_qImage);

    emit updateImageSignal();
}

void ImageUpdateThread::OnQuit()
{
    m_quit = true;
}

void ImageUpdateThread::run()
{
    while (!m_quit) {

        UpdateMousePosition();
        UpdatePanning();
        UpdateDrawing();

        if (Data::data.redrawOutput) {
            UpdateImage();
            Data::data.redrawOutput = false;

        }
        int newShift = 0;
        if (QApplication::keyboardModifiers() & Qt::ShiftModifier)
            newShift = 1;


        QThread::msleep(2);
    }

}

