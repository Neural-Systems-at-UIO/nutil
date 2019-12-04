#ifndef LBOOKHTML_H
#define LBOOKHTML_H

#include "source/LBook/lbookcsv.h"

class LBookHTML : public LBookCSV
{
public:
    LBookHTML();
    void Save(QString filename) override;

};

#endif // LBOOKHTML_H
