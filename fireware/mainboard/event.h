/*
  event.h - Header file for ForceFusion VizTact touch event functions.

  Copyright (c) 2017 Quark Li

  This software is developped for a commersial product. Modification, further
  development and/or redistribution without prior agreement from the author 
  is prohibited.

  To whom is interested in using this software, please contact quarkli@gmail.com
*/
#ifndef __VT_EVENT__
#define __VT_EVENT__

#include "touch.h"
#include "Arduino.h"

#define DEBOUNCE 2

class VT_TOUCH_EVENT {
  public:
    unsigned short id = 0;
    unsigned short seq = 0;
    unsigned long ts = 0;
    VT_POINT grid;
    VT_POINT pos;
    VT_VECTOR vector;
    unsigned short centerForce = 0;
    unsigned short totalForce = 0;
    byte forceLevel = 0;
    byte levelUp = 0;
    byte levelDown = 0;
    short referBy = -1;
    short referTo = -1;
};

void updateTouchEvent(VT_TOUCH_EVENT ein[10], byte sz);
VT_TOUCH_EVENT* nextEvent();

#endif
