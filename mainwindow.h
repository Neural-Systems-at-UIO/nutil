#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "source/nauto.h"
#include "source/util/lmessage.h"
#include "ui_mainwindow.h"
#include "ui_dialogtiff.h"
#include "source/util/cinifile.h"
#include <QThread>
#include <QElapsedTimer>
#include "dialogsettings.h"

namespace Ui {
    class MainWindow;
}


class UpdateThread : public QThread
{
    Q_OBJECT
public:
    Nauto* m_nauto;

    bool quit = false;
    void Init(Nauto* n) {
        m_nauto = n;
    }





    void run() override {

        while (!quit) {
            msleep(25);

            m_nauto->BuildInfo();
            emit TextChanged(m_nauto->m_mainInfo);
            emit MessageChanged(LMessage::lMessage.Build());
        }

    }
signals:
    void TextChanged(QString);
    void MessageChanged(QString);

};


class WorkerThread : public QThread
{
public:
    Nauto* m_nauto;
    void Init(Nauto *n) {
        m_nauto = n;
    }

    Q_OBJECT
    void run()  {
        m_nauto->Execute();
    }

};


class MainWindow : public QMainWindow
{
    Q_OBJECT
public:
    Ui::MainWindow *ui;

    static float Version;
    long m_elapsedTimer = -1;
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
    CIniFile m_settings;




private slots:
    void on_btnLoad_clicked();

    void on_btnStart_clicked();


    void on_leProcessors_returnPressed();

    void on_btnStop_clicked();

    void on_btnTiffEdit_clicked();

    void on_leProcessors_editingFinished();

    void on_btnOpenFolder_clicked();

    void on_actionSettings_triggered();



private:
    Nauto m_nauto;
    UpdateThread* m_updateThread;
    WorkerThread* m_workerThread = nullptr;

    QElapsedTimer m_timer;

    void AppQuit();
    void Abort();
    void FillSheetCombo();
    void closeEvent(QCloseEvent * event) override;
    void UpdateInfoTimer();
    void DefaultSettings();


public slots:
    void OnInfoTextChanged(QString);
    void OnMessageTextChanged(QString);
};




#endif // MAINWINDOW_H
