/*
Nutil - Neuroimaging utilities - aims to both simplify and streamline the mechanism of
pre-and-post processing 2D brain image data. Nutil is developed as a stand-alone application
that runs on all operating systems with a minimalistic user interface requiring little-to-no
experience to execute.

Copyright (C) 2020 nicolaas.groeneboom@gmail.com

This program is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 3 of the License, or
(at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/

#ifndef NUTILTEMPLATE_H
#define NUTILTEMPLATE_H

#include <QString>
#include <QStringList>
#include <QFile>
#include <QMap>
#include <QVariant>
#include <QGridLayout>
#include "source/dialoghelp.h"
#include <QSpacerItem>
#include <QTableWidget>
#include <QLayout>
#include <QComboBox>
#include <QEvent>
#include <QDebug>
#include <QMessageBox>
#include <QPixmap>
#include <QDirIterator>
#include "source/util/util.h"
#include "ui_mainwindow.h"
#include "source/LBook/lbookxlnt.h"
#include <QSharedPointer>



class NutilTemplateItem : public QObject {
    Q_OBJECT
public:

    enum Type{ STRING, LIST, DIRECTORY, FILE, TEXTFIELD, NUMBER, NONE, COLOR, MATRIXFIELD };
    Q_ENUM(Type)

    int m_matrixFieldWidth =1;
    QStringList m_matrixField;
    QStringList m_depID, m_depVal;
    QString m_name;
    QString m_text;
    QStringList m_items;
    QString m_value;
    QColor m_color;
    int m_level = 0;
    Type m_type;
    QWidget* m_widget;
    bool m_isHidden = false;

    static QString colorToString(QColor col) {
        return QString::number(col.red())+","+QString::number(col.green())+","+ QString::number(col.blue()) +"," + QString::number(col.alpha());
    }
    static QColor StringToColor(QString col) {
        QStringList l = col.trimmed().simplified().split(",");
        if (l.count()==3) l<<"255";
        if (l.count()<3) {
            qDebug() << "Error reading color: " << col;
            return Qt::black;
        }
        return QColor(l[0].toFloat(),l[1].toFloat(),l[2].toFloat(),l[3].toFloat());
    }


    NutilTemplateItem(NutilTemplateItem* nti) {
        m_matrixFieldWidth = nti->m_matrixFieldWidth;
        m_matrixField = nti->m_matrixField;
        m_depID = nti->m_depID;
        m_depVal = nti->m_depVal;
        m_name = nti->m_name;
        m_text = nti->m_text;
        m_items = nti->m_items;
        m_value = nti->m_value;
        m_color = nti->m_color;
        m_level =nti->m_level;
        m_type = nti->m_type;


    }

    NutilTemplateItem() {

    }



    static QString TypeToString(Type t) {
        return QVariant::fromValue(t).toString().toLower();
    }
    static Type StringToType(QString t) {
        t = t.toLower().trimmed().simplified();
        if (t=="string") return STRING;
        if (t=="list") return LIST;
        if (t=="directory") return DIRECTORY;
        if (t=="file") return FILE;
        if (t=="textfield") return TEXTFIELD;
        if (t=="number") return NUMBER;
        if (t=="color") return COLOR;
        if (t=="none") return NONE;
        if (t=="matrixfield") return MATRIXFIELD;
        return NONE;
    }

};


class NutilTemplate : public QObject
{
    Q_OBJECT


    QGridLayout* m_grid = nullptr;
    Ui::MainWindow *m_ui;

public:
    QObject* m_eventFilter = nullptr;
    NutilTemplate();
    int m_currentLevel = 0;
    QMap<QString,NutilTemplateItem*> m_items;
    QString m_openFile = "";
    QVector<QString> m_sortList;
    void LoadTemplate(QString file);
    QVector<QComboBox*> m_cmbBoxes;

    QString Get(QString val);
    int GetInt(QString val);

//    void Populate(QGridLayout* grid);
    void Populate(Ui::MainWindow* ui, bool sendSignal = true);
    void clearGrid(QLayout* grid);
    void clearLayout2(QLayout *layout);

    void FillFromGUI();
    void Save(QString fname);
    void Load(QString fname);
    void FillFromExcel(QTableWidget* tw);

    void Duplicator(QString directory);


signals:
    void emitUpdate();
    void emitRePopulate();

private:
    void CreateBasicAdvancedOption(QGridLayout* grid, int& row);

};

#endif // NUTILTEMPLATE_H
