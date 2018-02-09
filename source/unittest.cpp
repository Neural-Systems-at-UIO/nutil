#include "unittest.h"
#include "source/ltiff.h"
#include <QDebug>

UnitTest::UnitTest()
{

}


void UnitTest::TestMemory()
{
    for (int i=0;i<1000; i++) {
        LTiff* t = new LTiff();
        if (t->Open("C:\\data\\input\\H108_6c.tif")) {
            qDebug() << "Setting up buffers..";
            t->SetupBuffers();
            qDebug() << "Reading..";
            for (int j=0;j<1000;j++) {
                int x = rand()%t->m_width;
                int y = rand()%t->m_height;
                t->GetTiledRGB(x,y,0);
                t->bufferStack.UpdateBuffer();

            }
        }

        delete t;
        qDebug() << "Memory test: " << i;

    }
}
