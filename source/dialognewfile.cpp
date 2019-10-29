#include "dialognewfile.h"
#include "ui_dialognewfile.h"

DialogNewFile::DialogNewFile(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::DialogNewFile)
{
    ui->setupUi(this);
}

DialogNewFile::~DialogNewFile()
{
    delete ui;
}

void DialogNewFile::on_btnClose_clicked()
{
    close();
}

void DialogNewFile::on_btnOK_clicked()
{
    m_isOK = true;
    m_type = ui->cmbNew->currentText();
    close();
}
