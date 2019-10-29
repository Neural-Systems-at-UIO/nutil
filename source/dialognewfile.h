#ifndef DIALOGNEWFILE_H
#define DIALOGNEWFILE_H

#include <QDialog>

namespace Ui {
class DialogNewFile;
}

class DialogNewFile : public QDialog
{
    Q_OBJECT



public:
    bool m_isOK = false;
    QString m_type;

    explicit DialogNewFile(QWidget *parent = nullptr);
    ~DialogNewFile();

private slots:
    void on_btnClose_clicked();

    void on_btnOK_clicked();

private:
    Ui::DialogNewFile *ui;
};

#endif // DIALOGNEWFILE_H
