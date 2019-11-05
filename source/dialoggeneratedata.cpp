#include "dialoggeneratedata.h"
#include "ui_dialoggeneratedata.h"

DialogGenerateData::DialogGenerateData(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::DialogGenerateData)
{
    ui->setupUi(this);
}

DialogGenerateData::~DialogGenerateData()
{
    delete ui;
}

void DialogGenerateData::on_btnClose_clicked()
{
    close();
}
