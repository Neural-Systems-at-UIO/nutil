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
#ifndef LBOOKFACTORY_H
#define LBOOKFACTORY_H

#include "lbookcsv.h"
#include "lbookhtml.h"
#include "lbookxlnt.h"

class LBookFactory
{
public:
    LBookFactory();

    static LBook* Create(QString type) {
        if (type=="xlsx")
            return new LBookXlnt();
        if (type=="csv")
            return new LBookCSV();
        if (type=="html")
            return new LBookHTML();

        qDebug() << "Error : could not create book type " << type;
        return nullptr;
    }
};

#endif // LBOOKFACTORY_H
