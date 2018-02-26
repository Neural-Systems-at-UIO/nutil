#ifndef ImageUpdateThread_H
#define ImageUpdateThread_H

#include "ui_dialogtiff.h"
#include <QThread>
#include <QString>
#include <QObject>
#include "source/limage/limagetiff.h"
#include <QPixmap>

class ImageUpdateThread : public QThread {
    Q_OBJECT

public:

    bool m_quit = false;
    Ui::DialogTiff* ui;
    LImageTiff* m_tif;
    ImageUpdateThread(Ui::DialogTiff* _ui, LImageTiff* tif) {
            m_tif = tif;
            ui = _ui;
    }

    QPointF m_currentPos, m_prevPos;
    int m_currentButton = 0;
    float m_zoom = 1;
    bool m_isPanning = false;
    QPointF m_zoomCenter = QPoint(00,00);
    QPixmap m_pixMapImage;

    void run() override;
    bool isPreview;

    void UpdateDrawing();
    void UpdateMousePosition();
    void UpdatePanning();
    void UpdateImage();

signals:
    void updateImageSignal();



public slots:
    void OnQuit();
};



#endif // ImageUpdateThread_H
