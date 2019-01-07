#include "unittest.h"
#include "source/ltiff/ltiff.h"
#include <QDebug>

UnitTest::UnitTest()
{

}

/*
tab1 : incbin("tab1.dat","$2000");
p1 : pointer;
y,x,k : byte;
..

begin

    p1:=tab1; // la p1 peke til tabellen
    moveto(0,0,$04); // Flytt screenmemroy til $0400
    for y:=0 to 24 do begin // alle y-linjer
        for x:=0 to 40 do begin
            screenmemory[i]:=p1[x]/16 + 64; // anta at data er mellom [0-16] + 64 (ha noen tøffe chars her!)
        end;
        inczp(p1,40); //flytt p1 1 row ned
        inczp(screenmemory, 40); //flytt screenmemory 1 row ned

    end;

*/

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
