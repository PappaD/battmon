#include <EEPROM.h>
#include <LowPower.h>
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

void loop()
{
  sen.sense();
  bat.setCurrentAndVoltage(sen.getCurrent(), sen.getVoltage());

  gui.updateGui(&bat, &sen, &sta);
  gui.readCommand(&bat, &sen);
  
  sta.updateState(&sen);
  sta.wait();
}


