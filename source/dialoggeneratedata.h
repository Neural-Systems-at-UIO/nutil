#ifndef DIALOGGENERATEDATA_H
#define DIALOGGENERATEDATA_H

#include <QDialog>

namespace Ui {
class DialogGenerateData;
}

class DialogGenerateData : public QDialog
{
    Q_OBJECT

public:
    explicit DialogGenerateData(QWidget *parent = nullptr);
    ~DialogGenerateData();

private slots:
    void on_btnClose_clicked();

private:
    Ui::DialogGenerateData *ui;
};

#endif // DIALOGGENERATEDATA_H
