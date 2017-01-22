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

#define ENABLE_MEASUREMENT 0

static int count = 0;                // Scan rate counter
static int t0 = millis();            // Time in (ms)

void setup() {
  vt_init();
  VT_TOUCH.hInvert = true;
  VT_TOUCH.vInvert = true;
}

void loop() {
  if (scanTouch()) {
    processForceMap();
    Serial.println();
  }
  
#if ENABLE_MEASUREMENT     // calculate scan rate (Hz) in 10 seconds period
  int t1 = millis();

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


