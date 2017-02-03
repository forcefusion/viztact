/*
  event.cpp - ForceFusion VizTact touch event functions implementation.

  Copyright (c) 2017 Quark Li

  This software is developped for a commersial product. Modification, further
  development and/or redistribution without prior agreement from the author 
  is prohibited.

  To whom is interested in using this software, please contact quarkli@gmail.com
*/
#include "event.h"

static unsigned short seq = 0;
static byte size = 0;
static byte cursor = 0;

VT_TOUCH_EVENT eventList[VT_EVENT_MAX];

void updateTouchEvent(VT_TOUCH_EVENT ein[VT_EVENT_MAX], byte sz) {
  for (byte i = 0; i < sz; i++) {
    ein[i].seq = seq;
    eventList[i] = ein[i];
  }
  size = sz;
  seq++;
  cursor = 0;
}

VT_TOUCH_EVENT* nextEvent() {
  if (cursor >= size) {
    cursor = 0;
    return NULL;
  }

  return eventList + cursor++;
}
