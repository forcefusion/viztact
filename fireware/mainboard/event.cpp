/*
  event.cpp - ForceFusion VizTact touch event functions implementation.

  Copyright (c) 2017 Quark Li

  This software is developped for a commersial product. Modification, further
  development and/or redistribution without prior agreement from the author 
  is prohibited.

  To whom is interested in using this software, please contact quarkli@gmail.com
*/
#include "event.h"

static unsigned short eid = 0;
static unsigned short seq = 0;
static byte size = 0;
static byte cursor = 0;

VT_TOUCH_EVENT eventList[5];

void updateTouchEvent(VT_TOUCH_EVENT ein[10], byte sz) {
  byte m = sz > size ? size : sz;
  byte n = m == sz ? size : sz;

  for (byte i = 0; i < m; i++) {
    float delta = -1;
    short id = -1;
    for (byte j = 0; j < n; j++) {
      float cur_delta = -1;
      if (sz > size) {
        cur_delta = abs(eventList[i].vector.radius - ein[j].vector.radius) * abs(eventList[i].vector.sine - ein[j].vector.sine) + abs(eventList[i].vector.radius - ein[j].vector.radius);
      }
      else {
        cur_delta = abs(eventList[j].vector.radius - ein[i].vector.radius) * abs(eventList[j].vector.sine - ein[i].vector.sine) + abs(eventList[j].vector.radius - ein[i].vector.radius);
      }

      if (cur_delta >= 0 && cur_delta < 5 && (cur_delta < delta || delta < 0)) {
        delta = cur_delta;
        id = j;
      }
    }

    if (id < 0) continue;
    
    if (sz > size) {
      if (ein[id].referTo < 0) {
        eventList[i].referBy = id;
        ein[id].referTo = i;
      }
      else {
        Serial.println("##### Touch Tracking Conflict!!! #####");
        Serial.println();
        size = 0;
        seq++;
        cursor = 0;
        return;
      }
    }
    else {
      if (eventList[id].referBy < 0) {
        ein[i].referTo = id;
        eventList[id].referBy = i;
      }
      else {
        Serial.println("##### Touch Tracking Conflict!!! #####");
        Serial.println();
        size = 0;
        seq++;
        cursor = 0;
        return;
      }
    }
  }

  // assign ID and sequence number to the new events
  for (byte i = 0; i < sz; i++) {
   if (ein[i].referTo >= 0) {
    ein[i].id = eventList[ein[i].referTo].id;
    ein[i].forceLevel = eventList[ein[i].referTo].forceLevel;
    ein[i].levelUp = eventList[ein[i].referTo].levelUp;
    ein[i].levelDown = eventList[ein[i].referTo].levelDown;

    // force level evaluation 
    short upgrade = 0, downgrade = 0;
    switch (ein[i].forceLevel) {
      case 1:
        upgrade = 63;
        downgrade = 4;
        break;
      case 2:
        upgrade = 159;
        downgrade = 63;
        break;
      case 3:
        upgrade = 1024;
        downgrade = 159;
        break;
      default:
        upgrade = 4;
    }

    if (ein[i].totalForce > upgrade) {
      ein[i].levelUp++;
      ein[i].levelDown = 0;
    }
    else if (ein[i].totalForce <= downgrade) {
      ein[i].levelUp = 0;
      ein[i].levelDown++;
    }
    else {
      ein[i].levelUp = 0;
      ein[i].levelDown = 0;
    }
    

    if (ein[i].levelUp >= DEBOUNCE) {
      if (ein[i].forceLevel < 3) ein[i].forceLevel++;
      ein[i].levelUp = 0;
      ein[i].levelDown = 0;
    }
    if (ein[i].levelDown >= DEBOUNCE) {
      if (ein[i].forceLevel > 0) ein[i].forceLevel--;
      ein[i].levelUp = 0;
      ein[i].levelDown = 0;
    }
   }
   else {
    ein[i].id = eid++;
   }
   ein[i].seq = seq;
  }

  // add the unmatcheed event into new events array, or remove them if exceeded debounce limit
  for (byte i = 0; i < size; i++) {
    if (eventList[i].referBy < 0 && eventList[i].forceLevel > 0) {
      eventList[i].levelUp = 0;
      eventList[i].levelDown++;
      if (eventList[i].levelDown <= DEBOUNCE) {
        ein[sz++] = eventList[i];
      }
    }
  }

  for (byte i = 0; i < sz; i++) {
    eventList[i] = ein[i];
  }
  size = sz;
  seq++;
  cursor = 0;
}

VT_TOUCH_EVENT* nextEvent() {
  while (cursor < size && eventList[cursor].forceLevel == 0) {
    cursor++;
  }
  
  if (cursor >= size) {
    cursor = 0;
    return NULL;
  }

  return eventList + cursor++;
}
