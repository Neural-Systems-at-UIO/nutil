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
#pragma once

#include <string>
#include <iostream>
#include <QElapsedTimer>
#include "source/util/util.h"

//using namespace std;

class Counter {
public:
    int ticks;
    float Max;
    int current, currentTick;
    std::string str;
    bool outputClams;
    long prevTime;
    float m_progress = 0;

    long startTime;
    QElapsedTimer ttimer;
public:
    float percent;
    QString getPercent() {
        return QString::number((int)percent)+"%";
    }
    QString getPercentFormatted() {
        return "<font size=\"+1\">[<b>"+getPercent() +"</b>]</font>";
    }
    Counter() {}
    Counter(int m, std::string s, bool output) {
        outputClams = output;
        if (outputClams)
            std::cout << s << std::endl;
        Init(m);
    }

    Counter(int m, std::string s) {
        str = s;
        outputClams = true;
        std::cout << s << std::endl;
        Init(m);

    }


    void Init(int m) {
        ticks = 2;
        Max = m;
        current = 0;
        currentTick = -1;
        outputClams = false;
        if (outputClams)
            std::cout << "[";

        ttimer.start();
        prevTime = ttimer.elapsed();
        startTime = ttimer.elapsed();

    }




    void Tick() {

        int dt = ttimer.elapsed() - prevTime;
        prevTime = ttimer.elapsed();
        percent = (current*100.0)/(float)Max;

        int totalTime = (ttimer.elapsed() - startTime)/(percent/100.0);

        int timeLeft = (ttimer.elapsed());
        m_progress = percent;

        //cout << percent << endl;
        //if (percent % ticks==0 && percent!=currentTick)
        if (outputClams)
        {
            currentTick = percent;
            std::cout << "\r" <<str << " " << QString::number( percent,'f',1).toStdString() << "%" << "    " << Util:: MilisecondToString(timeLeft).toStdString() << " of total "  <<Util::MilisecondToString(totalTime).toStdString() << "                                                  ";
            std::cout.flush();
            if (percent==100-ticks)
                if (outputClams)
                    std::cout << "]" << std::endl;;
        }
        current++;
    }

};
