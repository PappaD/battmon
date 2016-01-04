#include <Arduino.h>
#include <EEPROM.h>
#include "sensor.h"
#include "settings.h"

#define ZEROVOLTAGEPOSITION 0
#define VOLTAGESCALERPOSITION 4
#define ZEROCURRENTPOSITION 8
#define CURRENTSCALERPOSITION 12

void sensor::EEPROM_writeDouble(int ee, double value)
{
   byte* p = (byte*)(void*)&value;
   for (int i = 0; i < sizeof(value); i++)
       EEPROM.write(ee++, *p++);
}

double sensor::EEPROM_readDouble(int ee)
{
   double value = 0.0;
   byte* p = (byte*)(void*)&value;
   for (int i = 0; i < sizeof(value); i++)
       *p++ = EEPROM.read(ee++);
   return value;
}


sensor::sensor()
{
  _zeroVoltage = EEPROM_readDouble(ZEROVOLTAGEPOSITION);
  _voltageScaler = EEPROM_readDouble(VOLTAGESCALERPOSITION);

  _zeroCurrent = EEPROM_readDouble(ZEROCURRENTPOSITION);
  _currentScaler = EEPROM_readDouble(CURRENTSCALERPOSITION);

  if(_voltageScaler == 0) _voltageScaler = 15;
  if(_currentScaler == 0) _currentScaler = 30;
}

void sensor::setup()
{
  pinMode(ENABLEMETERPIN, OUTPUT);
}


void sensor::initialize()
{
  _voltageScaler = 15;
  _currentScaler = 30;
  EEPROM_writeDouble(CURRENTSCALERPOSITION, _currentScaler);
  EEPROM_writeDouble(VOLTAGESCALERPOSITION, _voltageScaler);
}

void sensor::sense()
{
  double voltageValue=0;
  double currentValue=0;
  
  digitalWrite(ENABLEMETERPIN,1);
  analogRead(VOLTAGEPIN);
  for(int n=0;n<OVERSAMPLING;n++)
  {
    voltageValue += analogRead(VOLTAGEPIN)-_zeroVoltage;
  }
  
  analogRead(CURRENTPIN);
  for(int n=0;n<OVERSAMPLING;n++)
  {
    currentValue += analogRead(CURRENTPIN)-_zeroCurrent;
  }

  digitalWrite(ENABLEMETERPIN,0);
  
  _voltage = _voltageScaler*voltageValue/(1024.0*OVERSAMPLING);
  _current = _currentScaler*currentValue/(512.0*OVERSAMPLING);  

}


double sensor::getCurrent()
{
  return _current;
}

double sensor::getVoltage()
{
  return _voltage;
}


void sensor::setCurrent(double current)
{
  _currentScaler = _currentScaler*current/_current;
  EEPROM_writeDouble(CURRENTSCALERPOSITION, _currentScaler);
}


void sensor::setVoltage(double voltage)
{
  _voltageScaler = _voltageScaler*voltage/_voltage;
  EEPROM_writeDouble(VOLTAGESCALERPOSITION, _voltageScaler);
}


void sensor::setZeroCurrent()
{
  double currentValue=0;
  digitalWrite(ENABLEMETERPIN,1);

  analogRead(CURRENTPIN);
  for(int n=0;n<OVERSAMPLING_SETTINGS;n++)
  {
    currentValue += analogRead(CURRENTPIN);
  }
  digitalWrite(ENABLEMETERPIN,0);

  _zeroCurrent = currentValue/OVERSAMPLING_SETTINGS;
  EEPROM_writeDouble(ZEROCURRENTPOSITION, _zeroCurrent);
}



void sensor::setZeroVoltage()
{
  double voltageValue=0;
  digitalWrite(ENABLEMETERPIN,1);

  analogRead(VOLTAGEPIN);
  for(int n=0;n<OVERSAMPLING_SETTINGS;n++)
  {
    voltageValue += analogRead(VOLTAGEPIN);
  }
  digitalWrite(ENABLEMETERPIN,0);

  _zeroVoltage = voltageValue/OVERSAMPLING_SETTINGS;
  EEPROM_writeDouble(ZEROVOLTAGEPOSITION, _zeroVoltage);
}


