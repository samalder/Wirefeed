/*
Wirefeed.cpp - Library for operating a wire feed module, part of the Mini-Bender
 Created by Sam D. Alder, 01/09/2014.
*/

#include "Arduino.h"
#include "Wirefeed.h"

Wirefeed::Wirefeed(int feedStepPin, int feedDirPin)
{
  	//Save Pin Map
  	_feedStepPin = feedStepPin;
  	_feedDirPin = feedDirPin;
  
	//Initialize Output Pins
  	pinMode(feedStepPin, OUTPUT);
  	pinMode(feedDirPin, OUTPUT);

	//Initialize Public Variables
	//---State Machine
	timeStep = 20;
	stepCountForward = 0;
	feedLength = 0;
	
	//Initialize Private Variables
	//---State Machine  
  	_feeding = false;
  	_feedDirection = 1;
  	
  	//---Carry over
  	_lastTime = 0;
  	_feedStepPinState = 0;
  	_stepCount = 0;
  	_stepCountTotal = 0;

}

void Wirefeed::on()
{
 	_feeding = true;
}

void Wirefeed::off()
{
//Update the odometer and clear the step counter
 _stepCountTotal += _stepCount;									//Track motor usage
 if (_feedDirection > 0) {stepCountForward += _stepCount;}		//Count how much wire we use
 else if (_feedDirection < 1) {stepCountForward -= _stepCount;}
 _stepCount = 0;												//Reset for next time
 _feeding = false;
}

void Wirefeed::update()
{
  if (_feeding) {
  	int thisTime = millis();
  	int elapsedTime = thisTime - _lastTime;
  	
  	if (elapsedTime > timeStep) {
	    	if (_feedStepPinState > 0) {
    		  digitalWrite(_feedStepPin, LOW);
    		  _feedStepPinState = 0;
    		  _stepCount++;
    		  
    		  _lastTime = thisTime;				//start a new time step
    		}
    		if (_feedStepPinState < 1) {
    		  digitalWrite(_feedStepPin, HIGH);
    		  _feedStepPinState = 1;
    		  _stepCount++;
    		  
    		  _lastTime = thisTime;				//start a new time step
    		}
    	}
  }
}

void Wirefeed::setTimeStep(int timeStepIn) {
	timeStep = timeStepIn;
}

void Wirefeed::setDirection(int feedDirection) {
	_feedDirection = feedDirection;
	digitalWrite(_feedDirPin, _feedDirection);
	
}