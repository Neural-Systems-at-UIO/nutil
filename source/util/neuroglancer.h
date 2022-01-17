#ifndef NEUROGLANCER_H
#define NEUROGLANCER_H

#include <QJsonDocument>
#include <QImage>


class NeuroGlancer
{
public:
    NeuroGlancer(QString dir) {
        Open (dir);
    }
    NeuroGlancer() {}
    QImage m_img;
    QPoint m_chunkSize;
    QPoint m_size;
    QString m_chunkDir;
    void Open(QString directory);
    void LoadAllChunks();

};

#endif // NEUROGLANCER_H
