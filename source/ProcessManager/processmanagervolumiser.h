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
#ifndef PROCESSMANAGERVOLUMISER_H
#define PROCESSMANAGERVOLUMISER_H

#include "source/ProcessManager/processmanager.h"
#include "source/IO/xmlanchor.h"
#include <QRegularExpression>
#include "source/IO/nifti.h"
#include "source/ProcessManager/processmanagerpcounter.h"


class ProcessManagerVolumiser : public ProcessManagerPCounter {

public:
    ~ProcessManagerVolumiser() {

    }

    void Volumise(QString filename, QSharedPointer<ProcessItem> item, QString flatFile);
    Nifti nifti;
    QString m_palette;
    int m_sections;
    int m_niftiScale = 1;
    bool Build(NutilTemplate* data) override;
    void Execute() override; //(QString compression, QColor background, bool autoClip, int thumbnailSize, QString thumbType);
    void ReadHeader(NutilTemplate* data) override;
    QVector3D InvProject(QPointF p, Area* a, double rndSpread, QVector3D invCenter, QVector3D* altPoint, CoordinateTransform* transform);
    void CreateNifti(QString filename, QVector<QSharedPointer<NutilProcess>> processes, QVector<QSharedPointer<ProcessItem>> items, int size);
    QVector<QColor> getPalette(QString pal);
};


#endif // PROCESSMANAGERVOLUMISER_H
