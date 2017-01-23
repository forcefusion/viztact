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

#include "Arduino.h"

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

class EventList {
  public:
    unsigned int size = 0;
    TouchEvent list[10];
    void updateList(TouchEvent* e);
};

#endif