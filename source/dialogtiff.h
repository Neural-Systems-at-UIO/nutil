/*
Nutil - Neuroimaging utilities - aims to both simplify and streamline the mechanism of
pre-and-post processing 2D brain image data. Nutil is developed as a stand-alone application
that runs on all operating systems with a minimalistic user interface requiring little-to-no
experience to execute.

Copyright (C) 2020 nicolaas.groeneboom@gmail.com

This program is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 3 of the License, or
(at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/
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


class UpdateGUIThread : public QThread {

    Q_OBJECT

public:

    UpdateGUIThread() {
    }

    bool m_quit = false;
    void run() override;

signals:
    void updateProgressSignal();


};



class DialogTiff : public QDialog
{
    Q_OBJECT

public:
    explicit DialogTiff(QWidget *parent = 0);
    ~DialogTiff();
    LImageTiff m_tif;

    ImageUpdateThread* m_updateThread;
    UpdateGUIThread* m_guiThread;
    void mousePressEvent(QMouseEvent *e) override;
    void mouseReleaseEvent(QMouseEvent *e) override;
    void wheelEvent(QWheelEvent *event) override;
    void keyPressEvent(QKeyEvent* e) override;

private slots:
    void on_btnClose_clicked();
    void UpdateImage();
    void UpdateProgress();
    void on_btnOpen_clicked();

private:
    Ui::DialogTiff *ui;
};

#endif // DIALOGTIFF_H
