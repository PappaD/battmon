
#ifndef sensor_h
#define sensor_h

#include <Wire.h>
#include "Adafruit_INA219.h"



class sensor
{
  public:
    sensor();
    void sense();

    void setup();
    
    double getCurrent();
    double getVoltage();

    void initialize();
    
  private:
    double _current;
    double _voltage;
    double _shuntvoltage;
    
    Adafruit_INA219 _ina219;
};



#endif
