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
#include <iostream>
#include "source/data.h"

NutilTemplate::NutilTemplate()
{

}

void NutilTemplate::LoadTemplate(QString fileName)
{
    QFile file(fileName);
    qDebug() << "Loading "<<fileName;
    if (!QFile::exists(fileName)) {
        qDebug() << "Could not load template: "<<fileName;
        return;
    }
    file.open(QFile::ReadOnly);
    QTextStream in(&file);
    m_items.clear();
    m_sortList.clear();

    int fldID = 0;
    int fldLevel = 1;
    int fldDep = 2;
    int fldText = 3;
    int fldType = 4;
    int fldDefault = 5;



    while(!in.atEnd()) {
        QString line = in.readLine();
        //        qDebug() << line;
        if (line.trimmed()=="")
            continue;
        if (line.trimmed().startsWith("#"))
            continue;

        QStringList fields = line.split(";");
        NutilTemplateItem* nti = new NutilTemplateItem();
        //        qDebug() << fields;
        nti->m_name = fields[fldID].toLower().trimmed();
        QStringList depList = fields[fldDep].split(",");

        for (QString s : depList) {

            QStringList ls = s.split("=");
            if (ls.count()==2) {
                nti->m_depID.append(ls[0].trimmed());
                nti->m_depVal.append(ls[1].trimmed());

            }

        }
        nti->m_level = fields[fldLevel].toInt();
        nti->m_text = fields[fldText].trimmed();
        QStringList typeData = fields[fldType].trimmed().split(",");
        QString t = typeData[0];
        if (typeData.count()>1)
            nti->m_matrixFieldWidth = typeData[1].toInt();

        if (t.contains(",")) {
            nti->m_isHidden = t.split(",")[1].trimmed().toLower() == "hidden"?true:false;
            t = t.split(",")[0].trimmed();
        }
        nti->m_type = NutilTemplateItem::StringToType(t);

        if (nti->m_type==NutilTemplateItem::STRING || nti->m_type == NutilTemplateItem::NUMBER) {
            if (fields.size()>=fldDefault+1)
                nti->m_value = fields[fldDefault].trimmed();
        }
        if (nti->m_type==NutilTemplateItem::LIST) {
            nti->m_items = fields[fldDefault].trimmed().simplified().split(",");
            for (QString& s : nti->m_items)
                s = s.trimmed();

            if (fields.size()>=fldDefault+2)
                nti->m_value = fields[fldDefault+1].trimmed();

            //     qDebug() << nti->m_value;
        }
        if (nti->m_type==NutilTemplateItem::TEXTFIELD) {
            nti->m_value = fields[fldDefault];
        }
        if (nti->m_type==NutilTemplateItem::COLOR) {
            nti->m_items = fields[fldDefault].trimmed().simplified().split(",");
            for (QString& s : nti->m_items)
                s = s.trimmed();
            float a = 255;
            if (nti->m_items.size()==fldDefault+2)
                a=nti->m_items[fldDefault+1].toFloat();

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
        if (m_items[val]==nullptr)
            return "";
        QString v = m_items[val]->m_value;
        v = v.replace("#NNN","\n");
        return v;
    }
    qDebug() << "NutilTemplate::Get error : could not find item for value '"<<val<<"'";
    return "";
}

int NutilTemplate::GetInt(QString val)
{
    if (m_items.contains(val)) {
        if (m_items[val]==nullptr)
            return 0;
        QString v = m_items[val]->m_value;
        v = v.replace("#NNN","\n");
        return v.toInt();
    }
    qDebug() << "NutilTemplate::GetInt error : could not find item for value '"<<val<<"'";
    return 0;
}


void NutilTemplate::CreateBasicAdvancedOption(QGridLayout* grid, int& row)
{
    //    grid->addWidget(new QLabel("View type:"),0,0);

    /*    QComboBox* cmb = new QComboBox();
    cmb->addItem("Basic");
    cmb->addItem("Advanced");
    grid->addWidget(cmb, row,0);
    cmb->setCurrentIndex(m_currentLevel);

    QObject::connect(cmb, &QComboBox::currentTextChanged, [=]() {
        m_currentLevel = cmb->currentIndex();
        Populate(grid);
    });
*/
    QString text ="Show advanced settings >>";
    if (m_currentLevel==1)
        text = "Hide advanced settings <<";
    QPushButton* cmb = new QPushButton(text);


    for (int j=0;j<2;j++)
        for (int i=0;i<4;i++) {
            QWidget *horizontalLineWidget = new QWidget;
            horizontalLineWidget->setFixedHeight(5);
            //        horizontalLineWidget->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Fixed);
            //      horizontalLineWidget->setStyleSheet(QString("background-color: #101010;"));

            grid->addWidget(horizontalLineWidget, row+j*2,i);
        }

    grid->addWidget(cmb, row+1,2);
    //    grid->addWidget(horizontalLineWidget, row+2,2);

    QObject::connect(cmb, &QPushButton::clicked, [=]() {
        m_currentLevel = (m_currentLevel+1)&1;
        Populate(m_ui);
    });
    row+=3;

}



void NutilTemplate::Populate(Ui::MainWindow* ui, bool sendSignal)
{
    int row = 1;

  //  m_grid = grid;
    m_ui = ui;
//    clearGrid(m_grid);
    clearGrid(ui->gridTemplate);
//    clearLayout2(ui->gridTemplate);
//    clearGrid(ui->gridTemplate);
//    m_ui->gridTemplate->deleteLater();
//    delete m_ui->gridTemplate;
  //  m_ui->gridTemplate = new QGridLayout(uia);
    m_grid = m_ui->gridTemplate;

    int textColumn = 0;
    int helpColumn = 1;
    int valueColumn = 2;
    int buttonColumn = 3;


    bool hasAdvancedSettings = false;
    bool isDrawn = false;
    m_cmbBoxes.clear();




    for (QString name : m_sortList) {

        NutilTemplateItem* nti = m_items[name];


        if (nti->m_level==1)
            hasAdvancedSettings = true;

        if (nti->m_level > m_currentLevel)
            continue;

        if (nti->m_isHidden)
            continue;

        if (nti->m_name=="nutil_version")
            continue;

        bool breakHere = false;



        for (int i=0;i<nti->m_depID.count();i++) {
            if (!m_items.contains(nti->m_depID[i])) {
                qDebug() << "LEUAT ERROR: missing dependency in template file for value " + nti->m_depID[i];
                exit(1);
            }
            if (m_items[nti->m_depID[i]]->m_value != nti->m_depVal[i])
                breakHere = true;
        }
        if (breakHere)
            continue;


        if (nti->m_level==1 && !isDrawn) {
            isDrawn=true;
            CreateBasicAdvancedOption(m_grid,row);
        }



        int fontSize = -1;
        QString n = nti->m_text;
        QStringList lstName = n.split(",");

        if (lstName.count()!=1) {
            n = lstName[0];
            fontSize = lstName[1].toInt();
        }

        QLabel * lbl = new QLabel(n);
//        QLabel * lbl = new QLabel(n + ""+QString::number(rand()%100));

        if (fontSize!=-1) {
            QFont f;
            //        f.setFamily("Courier new");
            f.setPixelSize(fontSize);
            lbl->setFont(f);
        }
        m_grid->addWidget(lbl,row,textColumn);
        //        lbl->setMinimumSize(QSize(0,500));


        if (nti->m_type==NutilTemplateItem::STRING || nti->m_type==NutilTemplateItem::FILE || nti->m_type==NutilTemplateItem::DIRECTORY || nti->m_type==NutilTemplateItem::NUMBER) {
            QLineEdit* le = new QLineEdit();
            m_grid->addWidget(le,row,valueColumn);
            nti->m_widget = le;
            le->setText(nti->m_value);
            if (nti->m_name=="type")
                le->setEnabled(false);

            QObject::connect(le, &QLineEdit::textChanged, [=]() {
                nti->m_value = le->text();

            });


            if (nti->m_type==NutilTemplateItem::DIRECTORY) {

                le->setEnabled(false);
                QPixmap m = QPixmap::fromImage(QImage(":Resources/images/disk"));

//                QPushButton* btn = new QPushButton(m,"");
                QPushButton* btn = new QPushButton("Browse...");
                btn->setIconSize(QSize(24,24));
                QFont font = btn->font();
                //             font.setPointSize(16);
                btn->setFont(font);
                m_grid->addWidget(btn,row,buttonColumn);


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

                QPixmap m = QPixmap::fromImage(QImage(":Resources/images/disk"));

//                QPushButton* btn = new QPushButton(m,"");
                QPushButton* btn = new QPushButton("Browse...");
                btn->setIconSize(QSize(24,24));

                le->setEnabled(false);
                m_grid->addWidget(btn,row,buttonColumn);


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

            #ifndef __APPLE__

            QPushButton* btn = new QPushButton("");
            btn->setStyleSheet("background-color: #"+QString::number(NutilTemplateItem::StringToColor(nti->m_value).rgb(),16));

            m_grid->addWidget(btn,row,valueColumn);


            QObject::connect(btn, &QPushButton::clicked, [=]() {
                //nti->m_color = QColorDialog::getColor(nti->m_color, nullptr );

                QColor c = QColorDialog::getColor(nti->m_color, nullptr );
                if (c.isValid())
                {
                    nti->m_color = c;
                    btn->setStyleSheet("background-color: #"+QString::number(nti->m_color.rgb(),16));
                    nti->m_value = NutilTemplateItem::colorToString(nti->m_color);
                }

            });


#else

            QLineEdit* le = new QLineEdit(nti->m_value);
            le->setStyleSheet("background-color: #"+QString::number(NutilTemplateItem::StringToColor(nti->m_value).rgb(),16));

            m_grid->addWidget(le,row,valueColumn);


            QObject::connect(le, &QLineEdit::editingFinished, [=]() {
                nti->m_value = le->text();
                nti->m_color = NutilTemplateItem::StringToColor(nti->m_value);
                le->setStyleSheet("background-color: #"+QString::number(nti->m_color.rgb(),16));
            });




#endif

        }


        if (nti->m_type==NutilTemplateItem::LIST) {
            QComboBox* cmb = new QComboBox();
            m_cmbBoxes.append(cmb);
            cmb->setFocusPolicy( Qt::StrongFocus );
            cmb->installEventFilter(m_eventFilter);

            cmb->addItems(nti->m_items);
            m_grid->addWidget(cmb,row,valueColumn);
            nti->m_widget = cmb;
            QString val = nti->m_value;
            QObject::connect(cmb, &QComboBox::currentTextChanged, [=]() {
                if (nti->m_value!=cmb->currentText()) {
                    nti->m_value = cmb->currentText();
                    //Populate(m_ui,true);
                    QObject::disconnect(cmb);
                    //cmb->disconnect();
                    emit emitRePopulate();
                }

            });
            cmb->setCurrentText(nti->m_value);

        }
        if (nti->m_type==NutilTemplateItem::TEXTFIELD) {
            QTextEdit* te = new QTextEdit();
            m_grid->addWidget(te,row,valueColumn);
            nti->m_widget = te;
            te->setText(nti->m_value);
            QObject::connect(te, &QTextEdit::textChanged, [=]() {
                nti->m_value = te->toPlainText();
                nti->m_value.replace("\n", "#NNN");
                //                qDebug() << nti->m_value;
            });
        }


        if (nti->m_type==NutilTemplateItem::MATRIXFIELD) {
            QVBoxLayout* vl = new QVBoxLayout();
            QHBoxLayout* hl = new QHBoxLayout();
            QTableWidget* tw = new QTableWidget();

            tw->setMinimumHeight(200);
            vl->addWidget(tw);
            vl->addItem(hl);
//            vl->addWidget(new QPushButton("TEST"));
            /*              vl->addWidget(new QPushButton("WTF"));
                grid->update();*/
            //                grid->addWidget(vl,row,valueColumn);
            //grid->addWidget(new QPushButton("WTF"),row,valueColumn);
            nti->m_widget = tw;
            tw->setColumnCount(nti->m_matrixFieldWidth);
//            qDebug() << row << valueColumn;
            m_grid->addItem(vl,row,valueColumn);
//            qDebug() << m_grid->itemAt(row,valueColumn);

            QPushButton* plus = new QPushButton("+");
            QPushButton* minus = new QPushButton("-");
            QPushButton* fill = new QPushButton("Fill files");
            QPushButton* fillFromExcel = new QPushButton("From Excel");
            QPushButton* duplicate = new QPushButton("Duplicate");
            QPushButton* clear = new QPushButton("Clear");

            QObject::connect(plus, &QPushButton::pressed, [=]() {
                int y = tw->rowCount();
                tw->insertRow(y);
                tw->setItem(y, 0, new QTableWidgetItem("in_file.tif"));
                tw->setItem(y, 1, new QTableWidgetItem("out_file"));
                tw->setItem(y, 2, new QTableWidgetItem("0"));
                tw->setItem(y, 3, new QTableWidgetItem("1"));
                tw->setItem(y, 4, new QTableWidgetItem("1"));
            }
            );


            QObject::connect(duplicate, &QPushButton::pressed, [=]() {
                QMessageBox msgBox;
                msgBox.setText("Are you sure you want to duplicate the data in this cell to all other cells in the same column?");
                msgBox.setInformativeText("Duplicate columns?");
                msgBox.setStandardButtons(QMessageBox::Ok | QMessageBox::Cancel);
                msgBox.setDefaultButton(QMessageBox::Cancel);
                int ret = msgBox.exec();
                int currentCol = tw->currentColumn();
                QString currentVal = tw->currentItem()->text();
                if (ret==QMessageBox::Ok) {
                    for (int i=0;i<tw->rowCount();i++) {
                        tw->item(i,currentCol)->setText(currentVal);
                    }
                }

            }
            );



            QObject::connect(minus, &QPushButton::pressed, [=]() {
                tw->removeRow(tw->currentRow());
            }
            );




            tw->setHorizontalHeaderLabels(QStringList() << "Input file" << "Output file" << "Rotation" << "X scale" << "Y scale");
            QPixmap pmA(":Resources/images/btn-b-mirror-vert.png");
            QPixmap pmB(":Resources/images/btn-a-mirror-horiz.png");
            QTableWidgetItem* itmA = new QTableWidgetItem();
            itmA->setIcon(pmA);
            itmA->setText("Y scale");


            QTableWidgetItem* itmB = new QTableWidgetItem();
            itmB->setIcon(pmB);
            itmB->setText("X scale");
            tw->setHorizontalHeaderItem(4, itmA);
            tw->setHorizontalHeaderItem(3, itmB);
            int l0 = 200;
            int l1 = 120;
            tw->setColumnWidth(0,l0);
            tw->setColumnWidth(1,l0*0.8);
            tw->setColumnWidth(2,l1);
            tw->setColumnWidth(3,l1);
            tw->setColumnWidth(4,l1);
            QObject::connect(fill, &QPushButton::pressed, [=]() {
                tw->setRowCount(0);
                int y = 0;
                QDir directory(Get("transform_input_dir"));
                QStringList images = directory.entryList(QStringList() << "*.tif" << "*.tiff" << "*.TIF" << "*.TIFF",QDir::Files);
                for (QString fn :  images) {
                    tw->insertRow(y);
                    tw->setItem(y, 0, new QTableWidgetItem(fn));
                    tw->setItem(y, 1, new QTableWidgetItem(fn.split(".").first()));
                    tw->setItem(y, 2, new QTableWidgetItem("0"));
                    tw->setItem(y, 3, new QTableWidgetItem("1"));
                    tw->setItem(y, 4, new QTableWidgetItem("1"));


                    y++;
                }
            });

            QObject::connect(clear, &QPushButton::pressed, [=]() {
                QMessageBox msgBox;
                msgBox.setText("Are you sure you want to delete all data from the file list?");
                msgBox.setInformativeText("Clear list?");
                msgBox.setStandardButtons(QMessageBox::Ok | QMessageBox::Cancel);
                msgBox.setDefaultButton(QMessageBox::Cancel);
                int ret = msgBox.exec();
                if (ret==QMessageBox::Ok) {
                    tw->setRowCount(0);
                }

            });

            QObject::connect(fillFromExcel, &QPushButton::pressed, [=]() {
                FillFromExcel(tw);
            });


            QObject::connect(tw, &QTableWidget::itemChanged, [=]() {
                QString data = "";
                for (int i=0;i<tw->rowCount();i++)
                    for (int j=0;j<tw->columnCount();j++) {
                        //                            qDebug() << tw->item(i,j)->text();
                        QString txt = "";
                        if (tw->item(i,j)!=nullptr)
                            txt = tw->item(i,j)->text();
                        data += txt + ",";
                    }

                data.remove(data.length()-1,1);
                //                    qDebug() << data;
                nti->m_value = data;
            });

            hl->addWidget(plus);
            hl->addWidget(minus);
            hl->addWidget(duplicate);
            hl->addWidget(fill);
            hl->addWidget(fillFromExcel);
            hl->addWidget(clear);

            QStringList data = nti->m_value.split(",");
            int dataWidth = nti->m_matrixFieldWidth;
            int cnt = data.count()/dataWidth;
            int y = 0;
            for (int i=0;i<cnt;i++) {
                tw->insertRow(y);
                int c = i*dataWidth;
                for (int j=0;j<dataWidth;j++)
                    tw->setItem(y, j, new QTableWidgetItem(data[c+j].trimmed()));
                y++;
            }





            /*            QTextEdit* te = new QTextEdit();
            grid->addWidget(te,row,valueColumn);
            nti->m_widget = te;
            te->setText(nti->m_value);
            QObject::connect(te, &QTextEdit::textChanged, [=]() {
                nti->m_value = te->toPlainText();
                nti->m_value.replace("\n", "#NNN");
//                qDebug() << nti->m_value;
            });*/
        }



        QString type = m_items["type"]->m_value.trimmed().toLower();
        QString helpfn = ":Resources/text/help/"+type + "/"+nti->m_name.toLower()+".rtf";
        if (QFile::exists(helpfn)) {

            QPushButton* help = new QPushButton("Help");
            m_grid->addWidget(help,row,helpColumn);


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

    m_grid->setColumnStretch(textColumn,10);
    m_grid->setColumnStretch(helpColumn,4);
    m_grid->setColumnStretch(valueColumn,30);
    m_grid->setColumnStretch(buttonColumn,2);


    if (!isDrawn && hasAdvancedSettings)
        CreateBasicAdvancedOption(m_grid,row);



    QSpacerItem* sp =new QSpacerItem(20, 400, QSizePolicy::Minimum, QSizePolicy::Expanding);
    m_grid->addItem(sp,row+1,0);

    if (sendSignal)
        emit emitUpdate();


}/*

void NutilTemplate::clearGrid(QGridLayout *grid)
{
    for (int i = 0; i < grid->count(); i++)
    {
        grid->itemAt(i)->widget()->disconnect();
        grid->itemAt(i)->widget()->deleteLater();

    }

}
*/

void NutilTemplate::clearGrid(QLayout* layout)
{
    while (QLayoutItem* item = layout->takeAt(0))
    {
        //        if (deleteWidgets)
        {
            if (QWidget* widget = item->widget()) {
                widget->disconnect();
                widget->deleteLater();
            }
        }
        if (QLayout* childLayout = item->layout())
            clearGrid(childLayout);
        delete item;
    }



}

void NutilTemplate::clearLayout2(QLayout *layout) {
    if (layout==nullptr)
        return;
    QLayoutItem *item = nullptr;
    while(layout->count() > 0){
        item = layout->takeAt(0);
        layout->removeItem(item);
        delete item;
        qDebug()<< layout->count();
/*        if (item->layout()) {
            clearLayout2(item->layout());
            delete item->layout();
        }
        else
        if (item->widget()) {
           delete item->widget();
        }
        else
        delete item;*/
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

    NutilTemplateItem* nti = new NutilTemplateItem();

    QString id = "nutil_version";

    nti->m_name = id;
    nti->m_value = Data::data.version;
    nti->m_type = NutilTemplateItem::STRING;
    m_items[id] = nti;
    m_sortList.append(id);
    QFile f(fname);
    f.open(QFile::WriteOnly | QFile::Text);
    QTextStream str(&f);
    for (QString k: m_sortList) {
        NutilTemplateItem* nti = m_items[k];
        QString s = nti->m_name + " = " + nti->m_value;
        str << s << "\n";
    }

    f.close();
}

void NutilTemplate::Load(QString fname)
{
    if (!QFile::exists(fname))
        return;

    m_currentLevel = 0;
    m_openFile = fname;
    QFile f(fname);
    f.open(QFile::ReadOnly);
    QString dataStr = f.readAll();
    QStringList data = dataStr.split('\n');
    QStringList d = data[0].trimmed().simplified().split("=");

    if (d.count()<=1)
        return;

    QString type =  d[1].toLower().trimmed();


    QString temp =  ":/Resources/text/"+ type+ ".txt";

    if (!QFile::exists(temp))
        return;

    LoadTemplate(temp);

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

void NutilTemplate::FillFromExcel(QTableWidget *tw)
{
    QString fileName = QFileDialog::getOpenFileName(nullptr,
        tr("XLSX File"), "", tr("Excel files (*.xlsx)"));
    if (fileName=="")
        return;
    if (!QFile::exists(fileName))
        return;

    QSharedPointer<LBook> book = QSharedPointer<LBookXlnt>(new LBookXlnt);
    book->Load(fileName);
    QSharedPointer<LSheet> l = book->GetSheet(0);
    int row = 1;
    int col = 0;

    if (l==nullptr) {
        qDebug() << "NutilTemplate::FillFromExcel book returned 0, should not happen "<<book->m_sheets.count();
        return;
    }
    int cnt = 0;
    while (l->readStr(row,col)!="") {
        int y = tw->rowCount();
        tw->insertRow(y);
        tw->setItem(y, 0, new QTableWidgetItem(l->readStr(row,col)));
        tw->setItem(y, 1, new QTableWidgetItem(l->readStr(row,col+1)));
        tw->setItem(y, 2, new QTableWidgetItem(QString::number(l->readNum(row,col+2))));
        tw->setItem(y, 3, new QTableWidgetItem(QString::number(l->readNum(row,col+3))));
        tw->setItem(y, 4, new QTableWidgetItem(QString::number(l->readNum(row,col+4))));
        row++;
        cnt++;
    }
    QMessageBox msgBox;
    msgBox.setText(QString::number(cnt)+" rows of data was added from '"+fileName+"'");
    msgBox.exec();


}

void NutilTemplate::Duplicator(QString directory) {
//    QDirIterator it(directory, QDirIterator::Subdirectories);
    QDirIterator it(directory, QDir::Dirs | QDir::NoDotAndDotDot);
    QString typ = m_items["type"]->m_value.toLower();
    QString base ="";
    QString end = "";
    if (typ=="quantifier") {
        base = m_items["quantifier_input_dir"]->m_value;
        base = base.replace("/",QDir::separator());
        base = base.replace("\\",QDir::separator());
        QStringList baseList = base.split(QDir::separator());
        base = "";
        for (int i=0;i<baseList.count()-1;i++)
            base = base + QDir::separator() + baseList[i];
//        end = QDir::separator() + baseList.last();

    }
    base = base.replace(QString(QDir::separator())+QString(QDir::separator()),QDir::separator());
  //  qDebug() << "Duplicator type : " << typ;
//    QString idir = m_items["inp"]
  //  qDebug() << "INPUT DIR" <<
//    qDebug() << "BASE " << base;
    while (it.hasNext()) {
        QString fn = it.next();
        QString ln = fn.split(QDir::separator()).last();
        if (QDir().exists(fn)) {
            NutilTemplate nt;
            for (QString& k : m_items.keys()) {
                nt.m_items[k] = new NutilTemplateItem(m_items[k]);
            }
//            nt.m_items = m_items;
            nt.m_sortList = m_sortList;
            nt.m_items["quantifier_input_dir"]->m_value = nt.m_items["quantifier_input_dir"]->m_value.replace(base,fn);
            nt.m_items["quantifier_output_dir"]->m_value = nt.m_items["quantifier_output_dir"]->m_value.replace(base,fn);
            nt.m_items["quantifier_atlas_dir"]->m_value = nt.m_items["quantifier_atlas_dir"]->m_value.replace(base,fn);
            nt.m_items["xml_anchor_file"]->m_value = nt.m_items["xml_anchor_file"]->m_value.replace(base,fn);
//            qDebug() << "BASE / fn "<<base<<fn;
  //          qDebug() << "NEW quantifier input dir : " << nt.m_items["quantifier_input_dir"]->m_value;
            nt.Save(directory+QDir::separator()+ln+".nut");
        }

    }
}
