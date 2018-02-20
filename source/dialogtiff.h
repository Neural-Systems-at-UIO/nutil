#ifndef DIALOGTIFF_H
#define DIALOGTIFF_H
#include "ui_dialogtiff.h"
#include "source/limage/limagetiff.h"

#include <QDialog>
#include <QString>
#include <QFileDialog>
#include "source/updatethread.h"

namespace Ui {
class DialogTiff;
}





class DialogTiff : public QDialog
{
    Q_OBJECT

public:
    explicit DialogTiff(QWidget *parent = 0);
    ~DialogTiff();
    LImageTiff m_tif;

    ImageUpdateThread* m_updateThread;
    void mousePressEvent(QMouseEvent *e) override;
    void mouseReleaseEvent(QMouseEvent *e) override;
    void wheelEvent(QWheelEvent *event) override;
    void keyPressEvent(QKeyEvent* e) override;

private slots:
    void on_btnClose_clicked();
    void UpdateImage();

    void on_btnOpen_clicked();

private:
    Ui::DialogTiff *ui;
};

#endif // DIALOGTIFF_H
