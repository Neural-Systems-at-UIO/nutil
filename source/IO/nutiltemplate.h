#ifndef NUTILTEMPLATE_H
#define NUTILTEMPLATE_H

#include <QString>
#include <QStringList>
#include <QFile>
#include <QMap>
#include <QVariant>
#include <QGridLayout>

class NutilTemplateItem : public QObject {
    Q_OBJECT
public:

    enum Type{ STRING, LIST, DIRECTORY, FILE, TEXTFIELD, NUMBER, NONE };
    Q_ENUM(Type)

    QString m_name;
    QString m_text;
    QStringList m_items;
    QString m_value;
    Type m_type;
    QWidget* m_widget;

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
        if (t=="none") return NONE;
        return NONE;
    }

};


class NutilTemplate
{
public:
    NutilTemplate();
    QMap<QString,NutilTemplateItem*> m_items;

    QVector<QString> m_sortList;

    void LoadTemplate(QString file);

    void Populate(QGridLayout* grid);
    void clearGrid(QGridLayout* grid);
    void FillFromGUI();
    void Save();
};

#endif // NUTILTEMPLATE_H
