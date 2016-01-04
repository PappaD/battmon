/*

*/
#ifndef battery_h
#define battery_h

#include "Arduino.h"

class battery
{
  public:
    battery();
    void setup();
    void setCurrentAndVoltage(double current, double voltage);
    double getCurrent();
    double getVoltage();
    double getmWhConsumed();
    
  private:
    double _current;
    double _voltage;
    double _mWhConsumed;
    long _lastUpdated;
};

#endif
