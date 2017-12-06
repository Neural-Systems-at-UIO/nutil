#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "source/nauto.h"
#include <QThread>





namespace Ui {
    class MainWindow;
}


class UpdateThread : public QThread
{
public:
    Nauto* m_nauto;
    bool quit = false;
    void Init(Nauto* n) {
        m_nauto = n;

    }

    Q_OBJECT
    void run() override {

        while (!quit) {
            msleep(100);

            m_nauto->BuildInfo();
            emit TextChanged(m_nauto->m_mainInfo);
        }

    }
signals:
    void TextChanged(QString);

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


private:
    Nauto m_nauto;
    UpdateThread* m_updateThread;
    WorkerThread* m_workerThread = nullptr;

    void Error(QString q);
    void UpdateError();
    void Update();
    void AppQuit();
    void closeEvent(QCloseEvent * event) override;

public slots:
    void OnInfoTextChanged(QString);
};




#endif // MAINWINDOW_H
