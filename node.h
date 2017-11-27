#ifndef NODE_H
#define NODE_H

#include <QString>
#include <QVector3D>
#include <QVector>

#include <QWidget>
#include <QGroupBox>

class Parameter {
public:
    QString name;
    QVector3D value = QVector3D(0,0,1);
    Parameter(QString n, QVector3D v) {
        name = n;
        value = v;
    }
};


class Node : public QWidget
{
    Q_OBJECT
public:
    explicit Node(QWidget *parent = nullptr);
    QVector<Parameter> parameters;

private:
    QGroupBox *createGroup();

signals:

public slots:
};

#endif // NODE_H
