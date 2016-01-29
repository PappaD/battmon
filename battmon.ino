#include <Wire.h>
#include <LowPower.h>
#include <LiquidCrystal.h>
#include "sensor.h"
#include "battery.h"
#include "settings.h"
#include "serialGui.h"
#include "state.h"

battery bat;
sensor sen;
serialGui gui;
state sta;


void setup() {
  bat.setup();
  gui.setup(); 
  sen.setup();
  sta.setup();
}

long act, pasv;


void loop()
{
  act = millis();
  sen.sense();
  bat.setCurrentAndVoltage(sen.getCurrent(), sen.getVoltage());

  gui.updateGui(&bat, &sen, &sta);
  
  sta.updateState(&sen);
  pasv = millis();
  sta.wait();
  
  if(false) {
    Serial.print("Total loop time: "); Serial.print(millis()-act);
    Serial.print("  Active time: "); Serial.print(pasv-act);
    Serial.print("  Percent active: "); Serial.println(100.0*((float)pasv-act)/(millis()-act));    
  }
}


