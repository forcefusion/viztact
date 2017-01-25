/*
  mainboard.ino - ForceFusion VizTact firmware on ATMEGA32U4 (Arduino Leonardo).

  Copyright (c) 2017 Quark Li

  This software is developped for a commersial product. Modification, further
  development and/or redistribution without prior agreement from the author 
  is prohibited.

  To whom is interested in using this software, please contact quarkli@gmail.com
*/

#include "hardware.h"
#include "touch.h"
#include "event.h"

#define ENABLE_MEASUREMENT  0
#define ENABLE_EVENT_DEBUG 1

static byte count = 0;                // Scan rate counter
static unsigned long t0 = millis();   // Time in (ms)

void setup() {
  vt_init();

  Touch_Config.hInvert = false;
  Touch_Config.vInvert = true;
}

void loop() {
  scanTouch();
  while (VT_TOUCH_EVENT* e = nextEvent()) {
#if ENABLE_EVENT_DEBUG
      Serial.print("Seq No.: ");
      Serial.println(e->seq);
      Serial.print("Event ID / Timestamp: ");
      Serial.print(e->id);
      Serial.print(" / ");
      Serial.println(e->ts);
      Serial.print("GRID: (");
      Serial.print(e->grid.x);
      Serial.print(", ");
      Serial.print(e->grid.y);
      Serial.println(")");
      Serial.print("POS: (");
      Serial.print(e->pos.x, 3);
      Serial.print(", ");
      Serial.print(e->pos.y, 3);
      Serial.println(")");
      Serial.print("Vector: ");
      Serial.print(e->vector.radius, 3);
      Serial.print(" / ");
      Serial.println(e->vector.sine, 3);
      Serial.print("Force: ");
      Serial.print(e->centerForce);
      Serial.print(" / ");
      Serial.println(e->totalForce);
      Serial.print("Level Up/Down: ");
      Serial.print(e->levelUp);
      Serial.print(" / ");
      Serial.println(e->levelDown);
      Serial.print("F-Level: ");
      Serial.println(e->forceLevel);
      Serial.println();
#endif   
  }
  
#if ENABLE_MEASUREMENT     // calculate scan rate (Hz) in 10 seconds period
  unsigned long t1 = millis();

  if (t1 - t0 >= 10000) {
    Serial.print("Scan rate (Hz) = ");
    Serial.println(count / 10);
    t0 = t1;
    count = 0;
  }
  else {
    count++;
  }
#endif
}


