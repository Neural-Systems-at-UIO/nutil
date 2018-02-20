#include "source/updatethread.h"

void ImageUpdateThread::UpdateDrawing()
{
    if (m_isPanning)
        return;

}

void ImageUpdateThread::UpdateMousePosition()
{
    QPointF pos = QCursor::pos() - ui->lblImage->mapToGlobal(ui->lblImage->rect().topLeft());
    pos.setX(pos.x()/(float)ui->lblImage->width()*m_tif->m_tif.m_width);
    pos.setY(pos.y()/(float)ui->lblImage->height()*m_tif->m_tif.m_height);
    m_prevPos = m_currentPos;
    m_currentPos = QPoint(pos.x(), pos.y());
    //    qDebug() << QApplication()::mouseButtons();
}

void ImageUpdateThread::UpdatePanning()
{

    m_isPanning = false;
    if (m_currentButton == 2 && (QApplication::keyboardModifiers() & Qt::ShiftModifier)) {
        QPoint delta = (m_prevPos - m_currentPos);
        m_zoomCenter+=(QPoint)delta*0.5;
//        qDebug() << delta;
        m_isPanning = true;
        Data::data.redrawOutput = true;
    }


}




void ImageUpdateThread::UpdateImage()
{

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

