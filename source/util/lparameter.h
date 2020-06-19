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
