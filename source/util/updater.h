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
#ifndef UPDATER_H
#define UPDATER_H

#include "source/util/downloadmanager.h"

class Updater
{

public:

#ifdef IS_BETA
    QString m_versionURL = "https://www.irio.co.uk/med/nutil/version_beta.txt";
    QString m_appURL = "https://www.irio.co.uk/med/nutil/nutil_win_beta.zip";
    QString m_appFile = "nutil_win_beta.zip";
    QString m_versionFile = "version_beta.txt";
#else
    QString m_versionURL = "https://www.irio.co.uk/med/nutil/version.txt";
    QString m_appURL = "https://www.irio.co.uk/med/nutil/nutil_win.zip";
    QString m_appFile = "nutil_win.zip";
    QString m_versionFile = "version.txt";
#endif
    float m_newVersion;
    Updater();
    void Initialize();
    void FetchNewVersion();
    bool CheckVersionOK(float currentVersion);

private slots:
 void loadVersion();


};

#endif // UPDATER_H
