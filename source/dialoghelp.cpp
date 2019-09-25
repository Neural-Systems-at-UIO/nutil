#include "dialoghelp.h"
#include "ui_dialoghelp.h"

DialogHelp::DialogHelp(QString text, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::DialogHelp)
{
    ui->setupUi(this);
    ui->txtText->setText(text);
}

DialogHelp::~DialogHelp()
{
    delete ui;
}

void DialogHelp::on_pushButton_clicked()
{
    close();
}
