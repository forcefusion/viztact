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
  VT_OUTPUT_RAW,          // Output full touch scan result of force raw data to console
  VT_OUTPUT_FORCE,        // Output only valid force data (x/y/force) to console
  VT_OUTPUT_TOUCH         // Output touch data (pos-x/pos-y/total-force) to console
};

class VT_TOUCH_CFG {
  public:
    bool hInvert = false;
    bool vInvert = false;
    VT_CONSOLE_OUTPUT output = VT_OUTPUT_OFF;
};

class VT_POINT {
  public:
    float x;
    float y;
};

class VT_VECTOR {
  public:
    float radius;
    float sine;
};

void scanTouch();

extern VT_TOUCH_CFG Touch_Config;

#endif
