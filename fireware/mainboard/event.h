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

#define VT_EVENT_MAX 1

class VT_TOUCH_EVENT {
  public:
    unsigned short seq = 0;
    unsigned long ts = 0;
    VT_POINT grid;
    VT_POINT pos;
    unsigned short centerForce = 0;
    unsigned short totalForce = 0;
};

void updateTouchEvent(VT_TOUCH_EVENT ein[VT_EVENT_MAX], byte sz);
VT_TOUCH_EVENT* nextEvent();

#endif
