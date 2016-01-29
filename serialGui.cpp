#include <Arduino.h>
#include <LiquidCrystal.h>
#include "serialGui.h"
#include "sensor.h"
#include "battery.h"
#include "settings.h"
#include "state.h"

LiquidCrystal lcd(RS, ENABLE, D4, D5, D6, D7);


serialGui::serialGui()
{
}

void serialGui::setup(void)
{
  
  
  pinMode(RS, INPUT);
  pinMode(RW, INPUT);
  pinMode(VDD, INPUT);
  pinMode(ENABLE, INPUT);
  pinMode(D4, INPUT);
  pinMode(D5, INPUT);
  pinMode(D6, INPUT);
  pinMode(D7, INPUT);
  pinMode(VDDCONTRAST, INPUT);
  pinMode(VCCCONTRAST, INPUT);
  
  digitalWrite(RS, 0);
  digitalWrite(RW, 0);
  digitalWrite(VDD, 0);
  digitalWrite(ENABLE, 0);
  digitalWrite(D4, 0);
  digitalWrite(D5, 0);
  digitalWrite(D6, 0);
  digitalWrite(D7, 0);
  digitalWrite(VDDCONTRAST, 0);
  digitalWrite(VCCCONTRAST, 0);

  _lcdInit = false;
}

void serialGui::updateGui(battery *bat, sensor *sen, state *sta)
{
  
  if(sta->getState() == state::NORMAL && _lcdInit == false) {
    pinMode(RW, OUTPUT);
    pinMode(VDD, OUTPUT);
    pinMode(VDDCONTRAST, OUTPUT);
    pinMode(VCCCONTRAST, OUTPUT);
    
    digitalWrite(RW, 0);
    digitalWrite(VDD, 1);
    digitalWrite(VDDCONTRAST, 1);
    digitalWrite(VCCCONTRAST, 0);  

    Serial.begin(9600);
    lcd.begin(16, 2);
    _lcdInit = true;
  }

  if(sta->getState() == state::SLEEP && _lcdInit == true) {
    pinMode(RS, INPUT);
    pinMode(RW, INPUT);
    pinMode(VDD, INPUT);
    pinMode(ENABLE, INPUT);
    pinMode(D4, INPUT);
    pinMode(D5, INPUT);
    pinMode(D6, INPUT);
    pinMode(D7, INPUT);
    pinMode(VDDCONTRAST, INPUT);
    pinMode(VCCCONTRAST, INPUT);

    digitalWrite(RS, 0);
    digitalWrite(RW, 0);
    digitalWrite(VDD, 0);
    digitalWrite(ENABLE, 0);
    digitalWrite(D4, 0);
    digitalWrite(D5, 0);
    digitalWrite(D6, 0);
    digitalWrite(D7, 0);
    digitalWrite(VDDCONTRAST, 0);
    digitalWrite(VCCCONTRAST, 0);

    pinMode(0, INPUT);
    pinMode(1, INPUT);
    digitalWrite(0, 0);
    digitalWrite(1, 0);
    
    _lcdInit = false;       
  }

  if(_lcdInit)
  {
  
    Serial.print(bat->getVoltage(),4);
    Serial.print(" V, ");
    Serial.print(bat->getCurrent(),4);  
    Serial.print(" A, ");
    Serial.print(bat->getmWhConsumed(), 4);
    Serial.print(" mWh, state ");
  
    if(sta->getState() == state::NORMAL) {
      Serial.println("NORMAL");
    }
  
    if(sta->getState() == state::SLEEP) {
      Serial.println("WAIT");    
    }
  
    Serial.flush();
  
  
    String volt = String(bat->getVoltage(),2) + " V";
    String amp = String(bat->getCurrent(), 2) + " A";
    String space = "               ";
  
    String row1 = volt + space.substring(0, 16-volt.length()-amp.length()) + amp;
    
  
  
  
    String ah;
    
    if(bat->getAhConsumed() < 1) {
      ah = String(1000.0*bat->getAhConsumed(), 2) + " mAh";
    } else {
      ah = String(bat->getAhConsumed(), 2) + " Ah";
    } 
  
    if(bat->getAhConsumed() == 0) {
      ah = "Full";
    }
  
    String row2 = ah + space.substring(0, 16-ah.length());


    lcd.setCursor(0, 0);
    lcd.print(row1);
    
    lcd.setCursor(0, 1);
    lcd.print(row2);
  }

 
}

