#ifndef __VT_TOUCH__
#define __VT_TOUCH__

#include "Arduino.h"
#include "hardware.h"

class touchEvent {
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
  unsigned char levelUp;
  unsigned char levelDown;
  unsigned char padding;
};

class VT_TOUCH_CFG {
  public:
    bool hInvert = false;
    bool vInvert = false;
};

void processForceMap();

extern int forceMap[COLS][ROWS];
extern VT_TOUCH_CFG VT_TOUCH;

#endif
