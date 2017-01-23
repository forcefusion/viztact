/*
  touch.h - Header file for ForceFusion VizTact touch functions.

  Copyright (c) 2017 Quark Li

  This software is developped for a commersial product. Modification, further
  development and/or redistribution without prior agreement from the author 
  is prohibited.

  To whom is interested in using this software, please contact quarkli@gmail.com
*/
#ifndef __VT_TOUCH__
#define __VT_TOUCH__

#include "Arduino.h"
#include "hardware.h"

enum VT_CONSOLE_OUTPUT {
  VT_OUTPUT_OFF,          // Turn off touch scan result console output
  VT_OUTPUT_RAW,          // Output touch scan result as full forceMap raw data to console
  VT_OUTPUT_TOUCH,        // Output touch scan result as each touch data (x/y/force) to console
  VT_OUTPUT_EVENT         // Output touch scan result as touch events
};

class VT_TOUCH_CFG {
  public:
    bool hInvert = false;
    bool vInvert = false;
    VT_CONSOLE_OUTPUT output = VT_OUTPUT_OFF;
};

void scanTouch();

extern VT_TOUCH_CFG VT_TOUCH;
extern int forceMap[COLS][ROWS];

#endif
