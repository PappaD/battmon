#ifndef serialGui_h
#define serialGui_h

#include "battery.h"
#include "sensor.h"
#include "state.h"

class serialGui
{
  public:
    serialGui();
    void setup(void);
    void updateGui(battery *bat, sensor *sen, state *sta);

  private:
    bool _lcdInit;
};




#endif
