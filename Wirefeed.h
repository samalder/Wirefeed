/*
Wirefeed.h - Library for operating a wire feed module, part of the Mini-Bender
Created by Sam D. Alder, 01/09/2014
*/
#ifndef Wirefeed_h
#define Wirefeed_h

#include "Arduino.h"

class Wirefeed
{
  public:
    Wirefeed(int, int);
    void on();
    void off();
    void setTimeStep(int);
    void setDirection(int);
    void update();
    
    //State Machine Variables
    int timeStep;
    double stepCountForward;
    float feedLength;
    
  private:
  	//Pin Map
    int _feedStepPin;
    int _feedDirPin;
    
    //State Machine Variables
    bool _feeding;
    int _feedDirection;
    
    //Operational Variables (Carry over)
    int _lastTime;
    int _feedStepPinState;
    	//Motion and wire tracking
    double _stepCount;
    double _stepCountTotal;
    
};

#endif
