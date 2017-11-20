#pragma once

#include <string>
#include <iostream>

using namespace std;

class Counter {

  int ticks;
  int Max;
  int current, currentTick;
  int percent;
  bool outputClams;
 public:
  Counter(int m, string s, bool output) {
    outputClams = output;
    if (outputClams) 
      cout << s << endl;
    Init(m);
  }

  Counter(int m, string s) {
    outputClams = true;
    cout << s << endl;
    Init(m);
  }


  void Init(int m) {
    ticks = 2;
    Max = m;
    current = 0;
    currentTick = -1;
    if (outputClams) 
      cout << "[";
    
  }

  void Tick() {
    percent = (current*100)/Max;
    //cout << percent << endl;
    if (percent % ticks==0 && percent!=currentTick) {
      currentTick = percent;
      cout << ".";
      cout.flush();
      if (percent==100-ticks)
	if (outputClams)
	  cout << "]" << endl;;
    }
    current++;
  }

};
