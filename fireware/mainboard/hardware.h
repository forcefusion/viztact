/*
  hardware.h - Header file for ForceFusion VizTact VT3224 touch sensor hardware.

  Copyright (c) 2017 Quark Li

  This software is developped for a commersial product. Modification, further
  development and/or redistribution without prior agreement from the author 
  is prohibited.

  To whom is interested in using this software, please contact quarkli@gmail.com
*/
#ifndef __VT_HARDWARE__
#define __VT_HARDWARE__

#include "Arduino.h"

#define SEL_PINS    {4, 5, 6, 7}    // 4067 1:16 MUX, Analog Line Selection PINS D4, D5, D6, D7
#define DOUT_STCP   8               // 595 Shift Register, Storage Register Clock = D8
#define DOUT_SHCP   9               // 595 Shift Register, Shift Register Clock = D9
#define DOUT_DS     10              // 595 Shift Register, Serial Data Input = D10
#define ROWS        16              // Number of Rows (Y-coordinator)
#define COLS        24              // Nomber of Columns (X-coordinator)
#define DOUT_LINES  COLS            // Digital oupput lines on columns/rows
#define AIN_LINES   ROWS            // Analog input lines on columns/rows
#define LINES_SPLIT COLS            // Lines are splitted in two sides (half of them will be in reverse order)
#define PIN0_AT_MID true            // The first pin (PIN 0) of split lines is at the middle

void vt_init();
void vt_pullup(byte line);
byte vt_read(byte line);

#endif
