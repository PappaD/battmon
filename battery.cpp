#include <Arduino.h>
#include "battery.h"
#include "settings.h"

battery::battery()
{

}

void battery::setup()
{
  _current = 0;
  _voltage = 0;
  _mWhConsumed = 0;
  _AhConsumed = 0;
  _lastUpdated = millis();
}


void battery::setCurrentAndVoltage(double current, double voltage)
{
  _current = current;
  _voltage = voltage;

  if(true || abs(_current) > CURRENTTHRESHOLD) {
    _mWhConsumed += _current*_voltage*(millis()-_lastUpdated)/(1000.0*3600.0);
    _AhConsumed += _current*(millis()-_lastUpdated)/(1000.0*3600.0);
  }
  if(_mWhConsumed > 0) {
    _mWhConsumed = 0;
    _AhConsumed = 0;
  }

  
  _lastUpdated = millis();
}


double battery::getVoltage()
{
  return _voltage;
}

double battery::getCurrent()
{
  return _current;
}

double battery::getmWhConsumed()
{
  return _mWhConsumed;
}

double battery::getAhConsumed()
{
  return _AhConsumed;
}


