#ifndef LPARAMETER_H
#define LPARAMETER_H

#include <QString>
#include <QMap>


class LParameter
{
public:
    LParameter();
    QMap<QString, float> m_parameters;

    float getFloat(QString p) {
        if (m_parameters.contains(p))
            return m_parameters[p];
        return -1;
    }

    void Add(QString p, float f) {
        m_parameters[p]=f;
    }


};

#endif // LPARAMETER_H
