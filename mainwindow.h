#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "source/nauto.h"
#include "source/util/lmessage.h"
#include <QThread>

namespace Ui {
    class MainWindow;
}


class UpdateThread : public QThread
{
public:
    Nauto* m_nauto;
    float m_version = 0.06;

    bool quit = false;
    void Init(Nauto* n) {
        m_nauto = n;
    }

    Q_OBJECT
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
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private slots:
    void on_btnLoad_clicked();

    void on_btnStart_clicked();


    void on_btnStop_clicked();

private:
    Nauto m_nauto;
    UpdateThread* m_updateThread;
    WorkerThread* m_workerThread = nullptr;

    void AppQuit();
    void Abort();
    void FillSheetCombo();
    void closeEvent(QCloseEvent * event) override;

public slots:
    void OnInfoTextChanged(QString);
    void OnMessageTextChanged(QString);
};




#endif // MAINWINDOW_H
