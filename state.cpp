#include <Arduino.h>
#include "state.h"
#include "settings.h"
#include <LowPower.h>


state::state()
{
}

void state::setup()
{
  _state = NORMAL;
  _lastCurrentConsumtion = myMillis();
  _millisOffset = 0;
}

long state::myMillis()
{
  return _millisOffset+millis();
}


void state::updateState(sensor *sen)
{
  if (abs(sen->getCurrent()) > CURRENTTHRESHOLD)
  {
    _lastCurrentConsumtion = myMillis();
    _state = NORMAL;
  } else {
    if (myMillis() - _lastCurrentConsumtion > TIMETOSLEEP)
    {
      _state = SLEEP;
    }
  }
}

void state::wait()
{
  if(_state == NORMAL)
  {
    wait(WAIT_120MS);
  }
  else
  {
    wait(WAIT_1S);
  }
}


void state::wait(waitEnum w)
{
  
  switch (_state)
  {
    case SLEEP:
      switch (w)
      {
        case WAIT_15MS:
          LowPower.powerDown(SLEEP_15MS, ADC_OFF, BOD_OFF);
          _millisOffset += 15;
          break;
        case WAIT_30MS:
          LowPower.powerDown(SLEEP_30MS, ADC_OFF, BOD_OFF);
          _millisOffset += 30;
          break;
        case WAIT_60MS:
          LowPower.powerDown(SLEEP_60MS, ADC_OFF, BOD_OFF);
          _millisOffset += 60;
          break;
        case WAIT_120MS:
          LowPower.powerDown(SLEEP_120MS, ADC_OFF, BOD_OFF);
          _millisOffset += 120;
          break;
        case WAIT_250MS:
          LowPower.powerDown(SLEEP_250MS, ADC_OFF, BOD_OFF);
          _millisOffset += 250;
          break;
        case WAIT_500MS:
          LowPower.powerDown(SLEEP_500MS, ADC_OFF, BOD_OFF);
          _millisOffset += 500;
          break;
        case WAIT_1S:
          LowPower.powerDown(SLEEP_1S, ADC_OFF, BOD_OFF);
          _millisOffset += 1000;
          break;
        case WAIT_2S:
          LowPower.powerDown(SLEEP_2S, ADC_OFF, BOD_OFF);
          _millisOffset += 2000;
          break;
        case WAIT_4S:
          LowPower.powerDown(SLEEP_4S, ADC_OFF, BOD_OFF);
          _millisOffset += 4000;
          break;
        case WAIT_8S:
          LowPower.powerDown(SLEEP_8S, ADC_OFF, BOD_OFF);
          _millisOffset += 8000;
          break;
      }
      break;
    case NORMAL:
      switch (w)
      {
        case WAIT_15MS:
          delay(15);
          break;
        case WAIT_30MS:
          delay(30);
          break;
        case WAIT_60MS:
          delay(60);
          break;
        case WAIT_120MS:
          delay(120);
          break;
        case WAIT_250MS:
          delay(250);
          break;
        case WAIT_500MS:
          delay(500);
          break;
        case WAIT_1S:
          delay(1000);
          break;
        case WAIT_2S:
          delay(2000);
          break;
        case WAIT_4S:
          delay(4000);
          break;
        case WAIT_8S:
          delay(8000);
          break;
      }
      break;
  }
}


state::stateEnum state::getState()
{
  return _state;
}

