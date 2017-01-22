#include "touch.h"

#define ENABLE_TSQ_DEBUG  1           // Enable touch square data dump to console print
#define ENABLE_EVT_DEBUG  1           // Enable touch event output to console

int forceMap[COLS][ROWS] = {0};       // Full force map
static unsigned int seq = 0;

VT_TOUCH_CFG VT_TOUCH;

bool scanTouch() {
  int hasData = false;
  
  // force sensor scan: pull up digital output lines sequencially and read analog input lines sequencially
  for (int x = 0; x < DOUT_LINES; x++) {
    vt_pullup(VT_TOUCH.hInvert ? DOUT_LINES - x - 1 : x);
    for (int y = 0; y < AIN_LINES; y++) {
      int val = vt_read(VT_TOUCH.vInvert ? AIN_LINES - y - 1: y);

      // force value below 4 is filtered out as noise
      if (val > 4) hasData = true;
      else val = 0;

      if (DOUT_LINES == COLS) forceMap[x][y] = val;
      else forceMap[y][x];
    }
  }
  return hasData;
}

void processForceMap() {
  for (int x = 0; x < COLS; x++) {
    for (int y = 0; y < ROWS; y++) {
      int touchSquare[3][3] = {0};        // Temporary 3x3 force map for evaluation force center

      // looking for a force center where a force center must has its neighbor's force lower than (or equal to) its force value
      if (forceMap[x][y] == 0) continue;

      // top-left
      if (x > 0 && y > 0) {
        if (forceMap[x][y] <= forceMap[x-1][y-1]) continue;
        touchSquare[0][0] = forceMap[x-1][y-1];
      }
      // top
      if (y > 0) {
        if (forceMap[x][y] <= forceMap[x][y-1]) continue;
        touchSquare[1][0] = forceMap[x][y-1];
      }
      // top-right
      if (x < DOUT_LINES-1 && y > 0) {
        if (forceMap[x][y] <= forceMap[x+1][y-1]) continue;
        touchSquare[2][0] = forceMap[x+1][y-1];
      }
      // left
      if (x > 0) {
        if (forceMap[x][y] <= forceMap[x-1][y]) continue;
        touchSquare[0][1] = forceMap[x-1][y];
      }

      // right
      if (x < DOUT_LINES-1) {
        if (forceMap[x][y] < forceMap[x+1][y]) continue;
        touchSquare[2][1] = forceMap[x+1][y];
      }
      // bottom-left
      if (x > 0 && y > y < AIN_LINES-1) {
        if (forceMap[x][y] < forceMap[x-1][y+1]) continue;
        touchSquare[0][2] = forceMap[x-1][y+1];
      }
      // bottom
      if (y < AIN_LINES-1) {
        if (forceMap[x][y] < forceMap[x][y+1]) continue;
        touchSquare[1][2] = forceMap[x][y+1];
      }
      // bottom-right
      if (x < DOUT_LINES-1 && y < AIN_LINES-1) {
        if (forceMap[x][y] < forceMap[x+1][y+1]) continue;
        touchSquare[2][2] = forceMap[x+1][y+1];
      }

      touchSquare[1][1] = forceMap[x][y];
      
      int totalForce = 0;
      float hForce = 0, vForce = 0;
      TouchEvent e;

#if ENABLE_TSQ_DEBUG
      Serial.print(x);
      Serial.print(",");
      Serial.print(y);
      Serial.println(",");
#endif
      for (int i = 0; i < 3; i++) {
        int vSum = 0, hSum = 0;
        for (int j = 0; j < 3; j++) {
          totalForce += touchSquare[i][j];
          hSum += touchSquare[i][j];
          vSum += touchSquare[j][i];

#if ENABLE_TSQ_DEBUG
          Serial.print(touchSquare[i][j]);
          Serial.print(",");    
#endif
        }

        hForce += hSum * i / 2.0;
        vForce += vSum * i / 2.0;
        
#if ENABLE_TSQ_DEBUG
        Serial.println();
#endif
      }
      
      e.id = -1;
      e.seq = seq;
      e.ts = millis();
      e.gridX = x;
      e.gridY = y;
      e.posX = vForce / totalForce * 2 - 1;
      e.posY = hForce / totalForce * 2 - 1;
      e.centerForce = touchSquare[1][1];
      e.totalForce = totalForce;
      e.forceLevel = 0;

#if ENABLE_EVT_DEBUG
//      Serial.print("Event ID: ");
//      Serial.println(e.id);
//      Serial.print("Seq No.: ");
//      Serial.println(e.seq);
//      Serial.print("Timestamp.: ");
//      Serial.println(e.ts);
//      Serial.print("GRID X: ");
//      Serial.println(e.gridX);
//      Serial.print("GRID Y: ");
//      Serial.println(e.gridY);
      Serial.print("POS X: ");
      Serial.println(e.posX);
      Serial.print("POS Y: ");
      Serial.println(e.posY);
      Serial.print("Center-F: ");
      Serial.println(e.centerForce);
      Serial.print("Total-F: ");
      Serial.println(e.totalForce);
//      Serial.print("F-Level: ");
//      Serial.println(e.forceLevel);
//      Serial.println();
#endif

      seq++;      
    }
  }
}
