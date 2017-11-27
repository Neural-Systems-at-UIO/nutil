#include "node.h"
#include <QGridLayout>


Node::Node(QWidget *parent) : QWidget(parent)
{
    QGridLayout *grid = new QGridLayout;
    grid->addWidget(createGroup(), 0, 0);
    setLayout(grid);

    setWindowTitle(tr("Whooo!"));
    resize(480, 320);
}

QGroupBox *Node::createGroup()
{
    QGroupBox *groupBox = new QGroupBox(tr("Parameters"));
    return groupBox;
}
