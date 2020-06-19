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

#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QScrollBar>
#include "source/nauto.h"
#include "source/util/lmessage.h"
#include "ui_mainwindow.h"
#include "ui_dialogtiff.h"
#include "source/util/cinifile.h"
#include <QThread>
#include <QElapsedTimer>
#include "dialogsettings.h"
#include <QMessageBox>
#include "source/IO/nutiltemplate.h"
#include "source/dialognewfile.h"
#include "source/dialoggeneratedata.h"
#include <QSharedPointer>

namespace Ui {
    class MainWindow;
}


class UpdateThread : public QThread
{
    Q_OBJECT
public:

    QSharedPointer<Nauto> m_nauto;

    bool quit = false;
    void Init(QSharedPointer<Nauto> n) {
        m_nauto = n;
    }





    void run() override {

        while (!quit) {
            msleep(25);
            if (m_nauto!=nullptr) {
                m_nauto->BuildInfo();
                emit TextChanged(m_nauto->m_mainInfo);
                if (LMessage::lMessage.changed())
                    emit MessageChanged(LMessage::lMessage.Build());
            }
        }

    }
signals:
    void TextChanged(QString);
    void MessageChanged(QString);

};


class WorkerThread : public QThread
{
public:
    QSharedPointer<Nauto> m_nauto;
    void Init(QSharedPointer<Nauto> n) {
        m_nauto = n;
    }

    Q_OBJECT
    void run()  {
        if (m_nauto!=nullptr)
            m_nauto->Execute();
    }

};


class MainWindow : public QMainWindow
{
    Q_OBJECT
public:
    Ui::MainWindow *ui;
    static float Version;
    bool m_isInit = false;
    long m_elapsedTimer = -1;
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
    CIniFile m_settings;

    void UpdateRecentList();

    void Load(QString f);

    void setDarkPalette();


private:
    void PrivateUpdate();


private slots:
//    void on_btnLoad_clicked();

    void on_btnStart_clicked();

    void on_EmitUpdate();
    void on_RePopulate();

    void on_leProcessors_returnPressed();

    void on_btnStop_clicked();

    void on_btnTiffEdit_clicked();

    void on_leProcessors_editingFinished();

    void on_btnOpenFolder_clicked();

    void on_actionSettings_triggered();



    void on_btnNew_clicked();


    void on_btnSave_clicked();

    void on_btnLoad_2_clicked();

    void on_lstRecent_itemDoubleClicked(QListWidgetItem *item);

    void on_btnSaveAs_clicked();

    void on_pushButton_clicked();

    void on_btnClearList_clicked();

    void on_actionGenerate_validation_data_triggered();

    void on_btnClearData_clicked();

    void on_actionNutil_Duplicator_triggered();

private:
    QSharedPointer<Nauto> m_nauto;
    NutilTemplate m_nt;
    UpdateThread* m_updateThread;
    QSharedPointer<WorkerThread> m_workerThread = nullptr;

    QElapsedTimer m_timer;


    void AppQuit();
    void Abort();
//    void FillSheetCombo();
    void closeEvent(QCloseEvent * event) override;
    void UpdateInfoTimer();
    void DefaultSettings();

    bool eventFilter(QObject* obj, QEvent *event) override;


public slots:
    void OnInfoTextChanged(QString);
    void OnMessageTextChanged(QString);

};




#endif // MAINWINDOW_H
