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

#define ENABLE_TSQ_DEBUG  0           // Enable touch square data dump to console print

const byte CENTER = 1;

static unsigned short forceMap[COLS][ROWS] = {0};       // Full force map
static unsigned long timestamp = 0;
static byte sz = 0;

VT_TOUCH_CFG Touch_Config;
VT_TOUCH_EVENT ein[5];

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

      // force value below 4 is filtered out as noise
      if (val > 4) hasData = true;
      else val = 0;

      if (DOUT_LINES == COLS) forceMap[x][y] = val;
      else forceMap[y][x];
      
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
      short touchSquare[3][3] = {0};        // Temporary 3x3 force map for evaluation force center

      // looking for a force center where a force center must has its neighbor's force lower than (or equal to) its force value
      if (forceMap[x][y] == 0) continue;

      // top-left
      if (x > 0 && y > 0) {
        if (forceMap[x][y] <= forceMap[x-1][y-1]) continue;
        touchSquare[CENTER-1][CENTER-1] = forceMap[x-1][y-1];
      }
      // top
      if (y > 0) {
        if (forceMap[x][y] <= forceMap[x][y-1]) continue;
        touchSquare[CENTER][CENTER-1] = forceMap[x][y-1];
      }
      // top-right
      if (x < COLS-1 && y > 0) {
        if (forceMap[x][y] <= forceMap[x+1][y-1]) continue;
        touchSquare[CENTER+1][CENTER-1] = forceMap[x+1][y-1];
      }
      // left
      if (x > 0) {
        if (forceMap[x][y] <= forceMap[x-1][y]) continue;
        touchSquare[CENTER-1][CENTER] = forceMap[x-1][y];
      }

      // right
      if (x < COLS-1) {
        if (forceMap[x][y] < forceMap[x+1][y]) continue;
        touchSquare[CENTER+1][CENTER] = forceMap[x+1][y];
      }
      // bottom-left
      if (x > 0 && y < ROWS-1) {
        if (forceMap[x][y] < forceMap[x-1][y+1]) continue;
        touchSquare[CENTER-1][CENTER+1] = forceMap[x-1][y+1];
      }
      // bottom
      if (y < ROWS-1) {
        if (forceMap[x][y] < forceMap[x][y+1]) continue;
        touchSquare[CENTER][CENTER+1] = forceMap[x][y+1];
      }
      // bottom-right
      if (x < COLS-1 && y < ROWS-1) {
        if (forceMap[x][y] < forceMap[x+1][y+1]) continue;
        touchSquare[CENTER+1][CENTER+1] = forceMap[x+1][y+1];
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
      e.vector.radius = sqrt(pow(e.pos.x + 1,2) + pow(e.pos.y + 1,2));
      e.vector.sine = (e.pos.y + 1) / e.vector.radius;

      ein[sz++] = e;
     
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
