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
#include <Mouse.h>

#define ENABLE_MEASUREMENT  0
#define ENABLE_EVENT_DEBUG 0

static short count = 0;                // Scan rate counter
static unsigned long t0 = millis();   // Time in (ms)

void setup() {
  vt_init();

  Touch_Config.hInvert = false;
  Touch_Config.vInvert = true;
  Touch_Config.output = VT_OUTPUT_OFF;
}

byte clr = 0;
float px, py;
unsigned long last = 0;
void loop() {
  bool hasEvent = false;
  scanTouch();
  while (VT_TOUCH_EVENT* e = nextEvent()) {
    hasEvent = true;
    if (clr > 0) {
      float distx = e->pos.x - px;
      float disty = e->pos.y - py;
      float sp = sqrt(pow(distx, 2) + pow(disty, 2)) / (e->ts - last) * 100;
      Mouse.move(distx * 10 * sp, disty * 10 * sp, 0);
    }
    px = e->pos.x;
    py = e->pos.y;
    last = e->ts;
    if (clr < 2) clr++;
    
#if ENABLE_EVENT_DEBUG
      Serial.print("Seq No. / Timestamp: ");
      Serial.print(e->seq);
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
      Serial.print("Force: ");
      Serial.print(e->centerForce);
      Serial.print(" / ");
      Serial.println(e->totalForce);
      Serial.println();
#endif   
  }

  if (!hasEvent && clr > 0) clr--;

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


