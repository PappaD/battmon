#ifndef state_h
#define state_h

#include "sensor.h"

class state
{
  public:
    state();

    enum stateEnum {
      NORMAL,
      SLEEP
    };

    enum waitEnum {
      WAIT_15Ms,
      WAIT_30MS, 
      WAIT_60MS,
      WAIT_120MS,
      WAIT_250MS,
      WAIT_500MS,
      WAIT_1S,
      WAIT_2S,
      WAIT_4S,
      WAIT_8S
    };
    
    void setup(void);
    void updateState(sensor *sen);
    void wait(waitEnum w);
    void wait();
    
    stateEnum getState();
    
  private:
    stateEnum _state;
    long _lastCurrentConsumtion;
};
#endif
