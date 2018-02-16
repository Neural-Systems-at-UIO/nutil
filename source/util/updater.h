#ifndef UPDATER_H
#define UPDATER_H

#include "source/util/downloadmanager.h".h"

class Updater
{

public:

    Updater();
    void Initialize();

private slots:
 void loadVersion();


};

#endif // UPDATER_H
