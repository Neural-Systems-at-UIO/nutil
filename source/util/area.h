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
#ifndef AREA_H
#define AREA_H

#include <QVector>
#include <QVector2D>
#include <QVector3D>
#include <QMatrix4x4>
#include <QPoint>
#include "source/util/atlaslabel.h"
#include <QColor>

class XMLData;

class Area
{
public:
    Area();
    QVector<QPointF> m_points;
    QPointF m_center;
    double m_pixelArea=0;
    QMatrix4x4 m_mat;
    QVector3D m_planeNormal;
    QVector<QVector3D>* deformationPoints = nullptr;
    bool m_matrixInitialized = false;
    double m_area=0;
    long id = 0;
    static int s_area_id_counter;
    double m_areaScale = 0;
    double m_width,m_height;
    QColor color;
    AtlasLabel* atlasLabel = nullptr;
    XMLData *m_xmlData = nullptr;
    bool m_areaHasReachedCutoff = false;

    void CalculateStatistics();

    bool operator<(const Area& rhs) const {
        return rhs.m_pixelArea<m_pixelArea;


    }
};

#endif // AREA_H
