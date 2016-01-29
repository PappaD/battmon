#include <Arduino.h>
#include "sensor.h"
#include "settings.h"



sensor::sensor()
{
}

void sensor::setup()
{
  pinMode(ENABLEMETERPIN, OUTPUT);
  digitalWrite(ENABLEMETERPIN, 1);
  _ina219.begin();
  digitalWrite(ENABLEMETERPIN, 0);

  _current = 0;
  _voltage = 0;
  _shuntvoltage = 0;
}


void sensor::initialize()
{

}

void sensor::sense()
{  
  pinMode(ENABLEMETERPIN, OUTPUT);
  digitalWrite(ENABLEMETERPIN, 1);
  _ina219.begin();
  
  if(_shuntvoltage < 0.03) {
    _ina219.setCalibration_16V_400mA();
  } else {
    _ina219.setCalibration_16V_GAIN2();
  }

  _shuntvoltage = _ina219.getShuntVoltage_mV()/1000;
  _voltage = _ina219.getBusVoltage_V();
  _current = _shuntvoltage/SHUNTRESISTANCE;
  digitalWrite(ENABLEMETERPIN, 0);
  pinMode(ENABLEMETERPIN, INPUT);

  pinMode(A4, INPUT);
  pinMode(A5, INPUT);
  digitalWrite(A4, 0);
  digitalWrite(A5, 0);
  
}


double sensor::getCurrent()
{
  return _current;
}

double sensor::getVoltage()
{
  return _voltage;
}




