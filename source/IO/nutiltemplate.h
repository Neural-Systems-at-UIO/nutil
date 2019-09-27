#ifndef NUTILTEMPLATE_H
#define NUTILTEMPLATE_H

#include <QString>
#include <QStringList>
#include <QFile>
#include <QMap>
#include <QVariant>
#include <QGridLayout>
#include "source/dialoghelp.h"

class NutilTemplateItem : public QObject {
    Q_OBJECT
public:

    enum Type{ STRING, LIST, DIRECTORY, FILE, TEXTFIELD, NUMBER, NONE, COLOR };
    Q_ENUM(Type)

    QString m_name;
    QString m_text;
    QStringList m_items;
    QString m_value;
    QColor m_color;
    Type m_type;
    QWidget* m_widget;

    static QString colorToString(QColor col) {
        return QString::number(col.red())+","+QString::number(col.green())+","+ QString::number(col.blue()) +"," + QString::number(col.alpha());
    }
    static QColor StringToColor(QString col) {
        QStringList l = col.trimmed().simplified().split(",");
        return QColor(l[0].toFloat(),l[1].toFloat(),l[2].toFloat(),l[3].toFloat());
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
        return NONE;
    }

};


class NutilTemplate
{
    QGridLayout* m_grid = nullptr;

public:
    NutilTemplate();
    QMap<QString,NutilTemplateItem*> m_items;

    QVector<QString> m_sortList;
    void LoadTemplate(QString file);

    void Populate(QGridLayout* grid);
    void clearGrid(QGridLayout* grid);
    void FillFromGUI();
    void Save(QString fname);
    void Load(QString fname);
};

#endif // NUTILTEMPLATE_H
