#ifndef sensor_h
#define sensor_h


class sensor
{
  public:
    sensor();
    void sense();

    void setup();
    
    double getCurrent();
    double getVoltage();

    void setCurrent(double current);
    void setVoltage(double voltage);
    void setZeroCurrent();
    void setZeroVoltage();

    void initialize();
    
  private:
    double _zeroCurrent;
    double _zeroVoltage;
    double _voltageScaler;
    double _currentScaler;
    
    void EEPROM_writeDouble(int ee, double value);
    double EEPROM_readDouble(int ee);

    double _current;
    double _voltage;
};



#endif
