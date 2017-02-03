/*
  touch.cpp - ForceFusion VizTact touch functions.

  Copyright (c) 2017 Quark Li

  This software is developped for a commersial product. Modification, further
  development and/or redistribution without prior agreement from the author 
  is prohibited.

  To whom is interested in using this software, please contact quarkli@gmail.com
*/

#include "touch.h"
#include "event.h"

#define TSQ_SIZE 3
#define CENTER 1
#define LEFT(x) x - 1
#define RIGHT(x) x + 1
#define UP(x) LEFT(x)
#define DOWN(x) RIGHT(x)

#define ENABLE_TSQ_DEBUG  0           // Enable touch square data dump to console print

static short forceMap[COLS][ROWS] = {0};       // Full force map
static unsigned long timestamp = 0;
static byte sz = 0;

VT_TOUCH_CFG Touch_Config;
VT_TOUCH_EVENT ein[VT_EVENT_MAX];

void processForceMap();

void scanTouch() {
  bool hasData = false;
  timestamp = millis();
  sz = 0;

  // force sensor scan: pull up digital output lines sequencially and read analog input lines sequencially
  for (byte x = 0; x < DOUT_LINES; x++) {
    vt_pullup(Touch_Config.hInvert ? DOUT_LINES - x - 1 : x);
    for (byte y = 0; y < AIN_LINES; y++) {
      short val = vt_read(Touch_Config.vInvert ? AIN_LINES - y - 1: y);
      val = val < 4 ? 0 : val; 

      if (DOUT_LINES == COLS) forceMap[x][y] = val;
      else forceMap[y][x] = val;

      if (val > 0) hasData = true;

      if (Touch_Config.output == VT_OUTPUT_RAW) {
        Serial.print(val);
        Serial.print(",");
      }
      else if (Touch_Config.output == VT_OUTPUT_FORCE && val > 0) {
        Serial.print(x);
        Serial.print(",");
        Serial.print(y);
        Serial.print(",");
        Serial.print(val);
        Serial.print("/");
      }
    }
  }

  if (hasData) processForceMap();
  updateTouchEvent(ein, sz);

  if (Touch_Config.output != VT_OUTPUT_OFF) {
    if (hasData || Touch_Config.output == VT_OUTPUT_RAW) Serial.println();
  }
}

void processForceMap() {
  for (byte x = 0; x < COLS; x++) {
    for (byte y = 0; y < ROWS; y++) {
      short touchSquare[TSQ_SIZE][TSQ_SIZE] = {0};        // Temporary 3x3 force map for evaluation force center

      // looking for a force center where a force center must has its neighbor's force lower than (or equal to) its force value
      if (forceMap[x][y] == 0) continue;

      // top-left
      if (x > 0 && y > 0) {
        if (forceMap[x][y] <= forceMap[LEFT(x)][UP(y)]) continue;
        touchSquare[LEFT(CENTER)][UP(CENTER)] = forceMap[LEFT(x)][UP(y)];
      }
      // top
      if (y > 0) {
        if (forceMap[x][y] <= forceMap[x][UP(y)]) continue;
        touchSquare[CENTER][UP(CENTER)] = forceMap[x][UP(y)];
      }
      // top-right
      if (x < COLS-1 && y > 0) {
        if (forceMap[x][y] <= forceMap[RIGHT(x)][UP(y)]) continue;
        touchSquare[RIGHT(CENTER)][UP(CENTER)] = forceMap[RIGHT(x)][UP(y)];
      }
      // left
      if (x > 0) {
        if (forceMap[x][y] <= forceMap[LEFT(x)][y]) continue;
        touchSquare[LEFT(CENTER)][CENTER] = forceMap[LEFT(x)][y];
      }

      // right
      if (x < COLS-1) {
        if (forceMap[x][y] < forceMap[RIGHT(x)][y]) continue;
        touchSquare[RIGHT(CENTER)][CENTER] = forceMap[RIGHT(x)][y];
      }
      // bottom-left
      if (x > 0 && y < ROWS-1) {
        if (forceMap[x][y] < forceMap[LEFT(x)][DOWN(y)]) continue;
        touchSquare[LEFT(CENTER)][DOWN(CENTER)] = forceMap[LEFT(x)][DOWN(y)];
      }
      // bottom
      if (y < ROWS-1) {
        if (forceMap[x][y] < forceMap[x][DOWN(y)]) continue;
        touchSquare[CENTER][DOWN(CENTER)] = forceMap[x][DOWN(y)];
      }
      // bottom-right
      if (x < COLS-1 && y < ROWS-1) {
        if (forceMap[x][y] < forceMap[RIGHT(x)][DOWN(y)]) continue;
        touchSquare[RIGHT(CENTER)][DOWN(CENTER)] = forceMap[RIGHT(x)][DOWN(y)];
      }

      touchSquare[CENTER][CENTER] = forceMap[x][y];

      short totalForce = 0;
      float hForce = 0, vForce = 0;
#if ENABLE_TSQ_DEBUG
      Serial.print(x);
      Serial.print(",");
      Serial.print(y);
      Serial.println("=");
#endif
      for (byte i = 0; i < 3; i++) {
        short vSum = 0, hSum = 0;
        for (byte j = 0; j < 3; j++) {
          totalForce += touchSquare[i][j];
          hSum += touchSquare[i][j];
          vSum += touchSquare[j][i];
#if ENABLE_TSQ_DEBUG
          Serial.print(touchSquare[i][j]);
          Serial.print("(");
          Serial.print(forceMap[x+i-1][y+j-1]);
          Serial.print(")");
          Serial.print(",");
#endif
        }

        hForce += hSum * i / 2.0;
        vForce += vSum * i / 2.0;
#if ENABLE_TSQ_DEBUG
        Serial.println();
#endif
      }

      VT_TOUCH_EVENT e;
      e.ts = timestamp;
      e.grid.x = x;
      e.grid.y = y;
      e.pos.x = x + hForce / totalForce * 2 - 1;
      e.pos.y = y + vForce / totalForce * 2 - 1;
      e.centerForce = touchSquare[1][1];
      e.totalForce = totalForce;

      if (sz < VT_EVENT_MAX) ein[sz++] = e;
     
      if (Touch_Config.output == VT_OUTPUT_TOUCH) {
        Serial.print(e.pos.x);
        Serial.print(",");
        Serial.print(e.pos.y);
        Serial.print(",");
        Serial.print(totalForce);
        Serial.print("/");       
      }
    }
  }
}
