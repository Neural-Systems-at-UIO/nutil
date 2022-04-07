#include "dialogsettings.h"
#include "ui_dialogsettings.h"
#include <QFileDialog>

DialogSettings::DialogSettings(QWidget *parent, CIniFile* ini) :
    QDialog(parent),
    ui(new Ui::DialogSettings)
{
    ui->setupUi(this);
    m_settings = ini;
    FromIni();
}

DialogSettings::~DialogSettings()
{
    delete ui;
}

void DialogSettings::ToIni()
{
    m_settings->setString("fill_method", ui->cmbFillMethod->currentText());
    m_settings->setString("color_theme", ui->cmbThemes->currentText());
    m_settings->setFloat("csv_separator", (ui->chkUSSep->isChecked()==true)?1:0);
    m_settings->setString("python_path",ui->lePython->text());

}

void DialogSettings::FromIni()
{
    ui->cmbFillMethod->setCurrentText(m_settings->getString("fill_method"));
    ui->cmbThemes->setCurrentText(m_settings->getString("color_theme"));
    ui->chkUSSep->setChecked(m_settings->getdouble("csv_separator")==1.0);
    ui->lePython->setText(m_settings->getString("python_path"));
}

void DialogSettings::on_pushButton_clicked()
{
    ToIni();
    m_settings->Save();
    close();
}

void DialogSettings::on_btnPython_clicked()
{
    auto fileName = QFileDialog::getOpenFileName(this,
        tr("Python Executable"), "python3", tr("All files (*.*)"));
    ui->lePython->setText(fileName);
}

