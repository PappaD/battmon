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
    void readCommand(battery *bat, sensor *sen);
    
  private:
    void printFloat(float value, int places);
    void parseCommand(String command);
    String _command;
};




#endif
