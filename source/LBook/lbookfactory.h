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
