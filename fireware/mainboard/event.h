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

class VT_TOUCH_EVENT {
  public:
    unsigned int id = 0;
    unsigned int seq = 0;
    unsigned int ts = 0;
    VT_POINT grid;
    VT_POINT pos;
    VT_VECTOR vector;
    unsigned int centerForce = 0;
    unsigned int totalForce = 0;
    char forceLevel = -1;
    unsigned char levelUp = 0;
    unsigned char levelDown = 0;
    char referBy = -1;
    char referTo = -1;
};

void updateTouchEvent(VT_TOUCH_EVENT ein[10], int sz);
VT_TOUCH_EVENT* nextEvent();

#endif
