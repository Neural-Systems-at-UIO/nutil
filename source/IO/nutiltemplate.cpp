#include "nutiltemplate.h"
#include <QTextStream>
#include <QDebug>
#include <QLabel>
#include <QLineEdit>
#include <QPushButton>
#include <QComboBox>
#include <QTextEdit>
#include <QFileDialog>


NutilTemplate::NutilTemplate()
{

}

void NutilTemplate::LoadTemplate(QString fileName)
{
    QFile file(fileName);
    file.open(QFile::ReadOnly);
    QTextStream in(&file);
    m_items.clear();
    m_sortList.clear();
    while(!in.atEnd()) {
        QString line = in.readLine();
        if (line.trimmed()=="")
            continue;
        if (line.trimmed().startsWith("#"))
            continue;

        QStringList fields = line.split(";");
        NutilTemplateItem* nti = new NutilTemplateItem();
        nti->m_name = fields[0].toLower().trimmed();
        nti->m_text = fields[1];
        nti->m_type = NutilTemplateItem::StringToType(fields[2].trimmed());
        if (nti->m_type==NutilTemplateItem::STRING || nti->m_type == NutilTemplateItem::NUMBER) {
            if (fields.size()>=4)
                nti->m_value = fields[3].trimmed();
        }
        if (nti->m_type==NutilTemplateItem::LIST) {
            nti->m_items = fields[3].trimmed().simplified().split(",");
            for (QString& s : nti->m_items)
                s = s.trimmed();
            if (fields.size()>=5)
                nti->m_value = fields[4].trimmed();
       //     qDebug() << nti->m_value;
        }

        m_items[nti->m_name] = nti;
        m_sortList.append(nti->m_name);
    }
}

void NutilTemplate::Populate(QGridLayout *grid)
{
    int row = 0;
    clearGrid(grid);

    for (QString name : m_sortList) {
        NutilTemplateItem* nti = m_items[name];

        grid->addWidget(new QLabel(nti->m_text),row,0);

        if (nti->m_type==NutilTemplateItem::STRING || nti->m_type==NutilTemplateItem::FILE || nti->m_type==NutilTemplateItem::DIRECTORY || nti->m_type==NutilTemplateItem::NUMBER) {
            QLineEdit* le = new QLineEdit();
            grid->addWidget(le,row,1);
            nti->m_widget = le;
            le->setText(nti->m_value);
            if (nti->m_name=="type")
                le->setEnabled(false);

            QObject::connect(le, &QLineEdit::textChanged, [=]() {
                nti->m_value = le->text();

            });


            if (nti->m_type==NutilTemplateItem::DIRECTORY) {


                QPushButton* btn = new QPushButton("...");
                grid->addWidget(btn,row,2);


                QObject::connect(btn, &QPushButton::clicked, [=]() {
                    QString dir = QFileDialog::getExistingDirectory(nullptr, "Open Directory",
                                                            "",
                                                            QFileDialog::ShowDirsOnly
                                                            | QFileDialog::DontResolveSymlinks);
                    nti->m_value = dir;
                    le->setText(dir);
                });

            }

        }

        if (nti->m_type==NutilTemplateItem::LIST) {
            QComboBox* cmb = new QComboBox();
            cmb->addItems(nti->m_items);
            grid->addWidget(cmb,row,1);
            nti->m_widget = cmb;
            QString val = nti->m_value;
            QObject::connect(cmb, &QComboBox::currentTextChanged, [=]() {
                nti->m_value = cmb->currentText();
            });
            cmb->setCurrentText(nti->m_value);

        }
        if (nti->m_type==NutilTemplateItem::TEXTFIELD) {
            QTextEdit* te = new QTextEdit();
            grid->addWidget(te,row,1);
            nti->m_widget = te;
            QObject::connect(te, &QTextEdit::textChanged, [=]() {
                nti->m_value = te->toPlainText();
            });
        }


        row++;
    }

    grid->setColumnStretch(0,2);
    grid->setColumnStretch(1,5);
    grid->setColumnStretch(2,1);
}
void NutilTemplate::clearGrid(QGridLayout *grid)
{
    for (int i = 0; i < grid->count(); i++)
    {
        grid->itemAt(i)->widget()->deleteLater();
    }
}

void NutilTemplate::FillFromGUI()
{
/*    for (QString k: m_sortList) {
        NutilTemplateItem* nti = m_items[k];
        if (nti->m_type==NutilTemplateItem::STRING || nti->m_type==NutilTemplateItem::FILE || nti->m_type==NutilTemplateItem::DIRECTORY) {

    }*/
}

void NutilTemplate::Save()
{
    for (QString k: m_sortList) {
        NutilTemplateItem* nti = m_items[k];
       qDebug() << nti->m_name << nti->m_value;
    }
}
