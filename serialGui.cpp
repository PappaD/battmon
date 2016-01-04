#include <Arduino.h>
#include "serialGui.h"
#include "sensor.h"
#include "battery.h"
#include "settings.h"
#include "state.h"

serialGui::serialGui()
{
  _command = "";
}

void serialGui::setup(void)
{
  Serial.begin(115200);
}

void serialGui::updateGui(battery *bat, sensor *sen, state *sta)
{
  
  printFloat(bat->getVoltage(),4);
  Serial.print(" V, ");
  printFloat(bat->getCurrent(),4);  
  Serial.print(" A, ");
  printFloat(bat->getmWhConsumed(), 4);
  Serial.print(" mWh, state ");

  if(sta->getState() == state::NORMAL) {
    Serial.println("NORMAL");
  }

  if(sta->getState() == state::SLEEP) {
    Serial.println("WAIT");    
  }

  Serial.flush();
}

void serialGui::readCommand(battery *bat, sensor *sen)
{

    while (Serial.available() > 0) {
            // read the incoming byte:
            char incoming = Serial.read();
            if(incoming == '\n') {
              Serial.println("Executing command: " + _command);
              if(_command == "setZeroCurrent")
              {
                sen->setZeroCurrent();
                Serial.println("Current set to zero");
              } else if(_command == "setZeroVoltage")
              {
                sen->setZeroVoltage();
                Serial.println("Voltage set to zero");
              } else if(_command.substring(0,5) == "volt=")
              {
                double val = atof(_command.substring(5).c_str()) ;
                sen->setVoltage(val);
                Serial.print("Voltage set to ");
                printFloat(val,4);
                Serial.println();
              } else if(_command.substring(0,8) == "current=")
              {
                double val = atof(_command.substring(8).c_str()) ;
                sen->setCurrent(val);
                Serial.print("Current set to ");
                printFloat(val,4);
                Serial.println();         
              } else if(_command == "initialize")
              {
                sen->initialize();
                Serial.println("Scalers reset");
              } else
              {
                Serial.println("Unknown command");
              }
              _command = "";
            } else {
              _command += incoming;
            }
    }
}



void serialGui::printFloat(float value, int places) {
  // this is used to cast digits 
  int digit;
  float tens = 0.1;
  int tenscount = 0;
  int i;
  float tempfloat = value;

    // make sure we round properly. this could use pow from <math.h>, but doesn't seem worth the import
  // if this rounding step isn't here, the value  54.321 prints as 54.3209

  // calculate rounding term d:   0.5/pow(10,places)  
  float d = 0.5;
  if (value < 0)
    d *= -1.0;
  // divide by ten for each decimal place
  for (i = 0; i < places; i++)
    d/= 10.0;    
  // this small addition, combined with truncation will round our values properly 
  tempfloat +=  d;

  // first get value tens to be the large power of ten less than value
  // tenscount isn't necessary but it would be useful if you wanted to know after this how many chars the number will take

  if (value < 0)
    tempfloat *= -1.0;
  while ((tens * 10.0) <= tempfloat) {
    tens *= 10.0;
    tenscount += 1;
  }


  // write out the negative if needed
  if (value < 0)
    Serial.print('-');

  if (tenscount == 0)
    Serial.print(0, DEC);

  for (i=0; i< tenscount; i++) {
    digit = (int) (tempfloat/tens);
    Serial.print(digit, DEC);
    tempfloat = tempfloat - ((float)digit * tens);
    tens /= 10.0;
  }

  // if no places after decimal, stop now and return
  if (places <= 0)
    return;

  // otherwise, write the point and continue on
  Serial.print('.');  

  // now write out each decimal place by shifting digits one by one into the ones place and writing the truncated value
  for (i = 0; i < places; i++) {
    tempfloat *= 10.0; 
    digit = (int) tempfloat;
    Serial.print(digit,DEC);  
    // once written, subtract off that digit
    tempfloat = tempfloat - (float) digit; 
  }
}

