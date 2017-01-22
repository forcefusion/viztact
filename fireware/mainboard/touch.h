#ifndef __VT_TOUCH__
#define __VT_TOUCH__

#include "Arduino.h"
#include "hardware.h"

class TouchEvent {
  public:
    unsigned int id;
    unsigned int seq;
    unsigned int ts;
    unsigned int gridX;
    unsigned int gridY;
    float posX;
    float posY;
    unsigned int centerForce;
    unsigned int totalForce;
    unsigned char forceLevel;

  private:
    unsigned char levelUp;
    unsigned char levelDown;
};

class VT_TOUCH_CFG {
  public:
    bool hInvert = false;
    bool vInvert = false;
};

bool scanTouch();
void processForceMap();

extern VT_TOUCH_CFG VT_TOUCH;
extern int forceMap[COLS][ROWS];

#endif
