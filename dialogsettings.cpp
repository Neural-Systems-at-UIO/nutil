#include "dialogsettings.h"
#include "ui_dialogsettings.h"

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

}

void DialogSettings::FromIni()
{
    ui->cmbFillMethod->setCurrentText(m_settings->getString("fill_method"));
    ui->cmbThemes->setCurrentText(m_settings->getString("color_theme"));
    ui->chkUSSep->setChecked(m_settings->getdouble("csv_separator")==1.0);
}

void DialogSettings::on_pushButton_clicked()
{
    ToIni();
    m_settings->Save();
    close();
}
