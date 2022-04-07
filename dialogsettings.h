#ifndef DIALOGSETTINGS_H
#define DIALOGSETTINGS_H

#include <QDialog>
#include "source/util/cinifile.h"

namespace Ui {
class DialogSettings;
}

class DialogSettings : public QDialog
{
    Q_OBJECT
    CIniFile* m_settings = nullptr;

public:
    explicit DialogSettings(QWidget *parent, CIniFile* ini);
    ~DialogSettings();

    void ToIni();
    void FromIni();


private slots:
    void on_pushButton_clicked();


    void on_btnPython_clicked();

private:
    Ui::DialogSettings *ui;
};

#endif // DIALOGSETTINGS_H
