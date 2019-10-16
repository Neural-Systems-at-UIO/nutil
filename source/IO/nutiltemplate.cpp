#include "nutiltemplate.h"
#include <QTextStream>
#include <QDebug>
#include <QLabel>
#include <QLineEdit>
#include <QPushButton>
#include <QComboBox>
#include <QTextEdit>
#include <QFileDialog>
#include <QColorDialog>

NutilTemplate::NutilTemplate()
{

}

void NutilTemplate::LoadTemplate(QString fileName)
{
    QFile file(fileName);
    if (!QFile::exists(fileName)) {
        qDebug() << "Could not load template: "<<fileName;
        return;
    }
    file.open(QFile::ReadOnly);
    QTextStream in(&file);
    m_items.clear();
    m_sortList.clear();
    while(!in.atEnd()) {
        QString line = in.readLine();
//        qDebug() << line;
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
        if (nti->m_type==NutilTemplateItem::TEXTFIELD) {
            nti->m_value = fields[3];
        }
        if (nti->m_type==NutilTemplateItem::COLOR) {
            nti->m_items = fields[3].trimmed().simplified().split(",");
            for (QString& s : nti->m_items)
                s = s.trimmed();
            float a = 255;
            if (nti->m_items.size()==4)
                a=nti->m_items[3].toFloat();

             nti->m_color = QColor(nti->m_items[0].toFloat(),nti->m_items[1].toFloat(),nti->m_items[2].toFloat(),a);
             nti->m_value = NutilTemplateItem::colorToString(nti->m_color);
//             nti->m_value = nti->m_items[0].trimmed()+
        }

        m_items[nti->m_name] = nti;
        m_sortList.append(nti->m_name);
    }
}

QString NutilTemplate::Get(QString val)
{
    if (m_items.contains(val)) {
        QString v = m_items[val]->m_value;
        v = v.replace("#NNN","\n");
        return v;
    }
    qDebug() << "NutilTemplate::Get error : could not find item for value '"<<val<<"'";
    return "";
}

void NutilTemplate::Populate(QGridLayout *grid)
{
    int row = 0;
    clearGrid(grid);
    m_grid = grid;
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

                le->setEnabled(false);
                QPushButton* btn = new QPushButton("...");
                grid->addWidget(btn,row,2);


                QObject::connect(btn, &QPushButton::clicked, [=]() {
                    QString dir = QFileDialog::getExistingDirectory(nullptr, "Open Directory",
                                                            nti->m_value,
                                                            QFileDialog::ShowDirsOnly
                                                            | QFileDialog::DontResolveSymlinks);

                    if (!(dir=="")) {
                        nti->m_value = dir;
                        le->setText(dir);
                    }
                });

            }

            if (nti->m_type==NutilTemplateItem::FILE) {

                le->setEnabled(false);
                QPushButton* btn = new QPushButton("...");
                grid->addWidget(btn,row,2);


                QObject::connect(btn, &QPushButton::clicked, [=]() {
                    QString f = QFileDialog::getOpenFileName(nullptr, "Open Directory",
                                                            nti->m_value);
                    if (!(f=="")) {
                        nti->m_value = f;
                        le->setText(f);
                    }
                });

            }


        }

        if (nti->m_type==NutilTemplateItem::COLOR) {
            QPushButton* btn = new QPushButton("");
            btn->setStyleSheet("background-color: #"+QString::number(NutilTemplateItem::StringToColor(nti->m_value).rgb(),16));

            grid->addWidget(btn,row,1);

            QObject::connect(btn, &QPushButton::clicked, [=]() {
                nti->m_color = QColorDialog::getColor(nti->m_color, nullptr );
                btn->setStyleSheet("background-color: #"+QString::number(nti->m_color.rgb(),16));
                nti->m_value = NutilTemplateItem::colorToString(nti->m_color);


            });

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
            te->setText(nti->m_value);
            QObject::connect(te, &QTextEdit::textChanged, [=]() {
                nti->m_value = te->toPlainText();
                nti->m_value.replace("\n", "#NNN");
//                qDebug() << nti->m_value;
            });
        }

        QString helpfn = ":Resources/text/help/"+nti->m_name.toLower()+".rtf";
        if (QFile::exists(helpfn)) {

            QPushButton* help = new QPushButton("Help");
            grid->addWidget(help,row,3);


            QObject::connect(help, &QPushButton::clicked, [=]() {
                QFile f(helpfn);
                f.open(QFile::ReadOnly);
                QString txt = f.readAll();
                f.close();
                DialogHelp* dh = new DialogHelp(txt);
                dh->exec();
                delete dh;

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
        grid->itemAt(i)->widget()->disconnect();
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

void NutilTemplate::Save(QString fname)
{
    if (QFile::exists(fname))
        QFile::remove(fname);

    m_openFile = fname;

    QFile f(fname);
    f.open(QFile::WriteOnly | QFile::Text);
    QTextStream str(&f);
    for (QString k: m_sortList) {
        NutilTemplateItem* nti = m_items[k];
        QString s = nti->m_name + " = " + nti->m_value;;
        str<< s << endl;
    }

    f.close();
}

void NutilTemplate::Load(QString fname)
{
    if (!QFile::exists(fname))
        return;


    m_openFile = fname;
    QFile f(fname);
    f.open(QFile::ReadOnly);
    QString dataStr = f.readAll();
    QStringList data = dataStr.split('\n');
    QString type =  data[0].trimmed().simplified().split("=")[1].toLower().trimmed();
    LoadTemplate(":/Resources/text/"+ type+ ".txt");

    for (QString k: data) {
        if (k.trimmed()=="")
            continue;
        QStringList d =  k.trimmed().simplified().split("=");
        if (d.count()!=2)
            continue;
//        qDebug() << d;
        NutilTemplateItem* nti = m_items[d[0].trimmed()];
        if (nti==nullptr) {
            qDebug() << "Warning: could not find parameter " <<d[0].trimmed();
        }
        else {
            nti->m_value = d[1].trimmed();
            nti->m_value = nti->m_value.replace("#NNN","\n");
        }

    }
    f.close();

}
