/*
  event.cpp - ForceFusion VizTact touch event functions implementation.

  Copyright (c) 2017 Quark Li

  This software is developped for a commersial product. Modification, further
  development and/or redistribution without prior agreement from the author 
  is prohibited.

  To whom is interested in using this software, please contact quarkli@gmail.com
*/
#include "event.h"

static unsigned int eid = 0;
static unsigned int seq = 0;
static unsigned int size = 0;
static unsigned int cursor = 0;

VT_TOUCH_EVENT eventList[10];

void updateTouchEvent(VT_TOUCH_EVENT ein[10], int sz) {
  int m = sz > size ? size : sz;
  int n = m == sz ? size : sz;

  for (int i = 0; i < m; i++) {
    float delta = -1;
    int id = -1;
    for (int j = 0; j < n; j++) {
      int cur_delta = -1;
      if (sz > size) {
        if (abs(eventList[i].vector.radius - ein[j].vector.radius) < 3) {
          cur_delta = abs(eventList[i].vector.radius - ein[j].vector.radius) * abs(eventList[i].vector.sine - ein[j].vector.sine);
        }
      }
      else {
        if (abs(eventList[j].vector.radius - ein[i].vector.radius) < 3) {
          cur_delta = abs(eventList[j].vector.radius - ein[i].vector.radius) * abs(eventList[j].vector.sine - ein[i].vector.sine);
        }        
      }

      if (delta < 0 || (cur_delta >= 0 && cur_delta < delta)) {
        delta = cur_delta;
        id = j;
      }
    }

    if (id < 0) continue;
    
    if (sz > size) {
      eventList[i].referBy = id;
      if (ein[id].referTo < 0) {
        ein[id].referTo = i;
      }
      else {
        Serial.println("##### Touch Tracking Conflict!!! #####");
        Serial.println();
        size = 0;
        break;
      }
    }
    else {
      ein[i].referTo = id;
      if (eventList[id].referBy < 0) {
        eventList[id].referBy = i;
      }
      else {
        Serial.println("##### Touch Tracking Conflict!!! #####");
        Serial.println();
        size = 0;
        break;
      }
    }
  }

  // add the rest new event into array
  for (int i = 0; i < sz; i++) {
   if (ein[i].referTo >= 0) {
    ein[i].id = eventList[ein[i].referTo].id;
    // force level evaluation 
   }
   else {
    ein[i].id = eid++;
   }
   ein[i].seq = seq;
  }

  if (size > sz) {
    for (int i = 0; i < size; i++) {
      if (eventList[i].referBy < 0 && eventList[i].forceLevel > 0) {
        eventList[i].levelDown++;
        if (eventList[i].levelDown < 3) {
          ein[sz++] = eventList[i];
        }
      }
    }
  }

  for (int i = 0; i < sz; i++) {
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
