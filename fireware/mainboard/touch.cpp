#include "touch.h"

static int touchSquare[3][3] = {0}; // Temporary 3x3 force map for evaluation force center

void processForceMap() {
  for (int x = 0; x < DOUT_LINES; x++) {
    for (int y = 0; y < AIN_LINES; y++) {
      bool center = true;
      center &= (forceMap[x][y] > 0);
      center &= (x > 0 && y > 0) ? (forceMap[x][y] >= forceMap[x-1][y-1]) : true;
      center &= (y > 0) ? (forceMap[x][y] >= forceMap[x][y-1]) : true;
      center &= (x < DOUT_LINES-1 && y > 0) ? (forceMap[x][y] >= forceMap[x+1][y-1]) : true;
      center &= (x > 0) ? (forceMap[x][y] >= forceMap[x-1][y]) : true;
      center &= (x < DOUT_LINES-1) ? (forceMap[x][y] >= forceMap[x+1][y]) : true;
      center &= (x > 0 && y > y < AIN_LINES-1) ? (forceMap[x][y] >= forceMap[x-1][y+1]) : true;
      center &= (y < AIN_LINES-1) ? (forceMap[x][y] >= forceMap[x][y+1]) : true;
      center &= (x < DOUT_LINES-1 && y < AIN_LINES-1) ? (forceMap[x][y] >= forceMap[x+1][y+1]) : true;

      if (center) {
        touchSquare[0][0] = (x > 0 && y > 0) ? forceMap[x-1][y-1] : 0;
        touchSquare[1][0] = (y > 0) ? forceMap[x][y-1] : 0;
        touchSquare[2][0] = (x < DOUT_LINES-1 && y > 0) ? forceMap[x+1][y-1] : 0;
        touchSquare[0][1] = (x > 0) ? forceMap[x-1][y] : 0;
        touchSquare[1][1] = forceMap[x][y];
        touchSquare[2][1] = (x < DOUT_LINES-1) ? forceMap[x+1][y] : 0;
        touchSquare[0][2] = (x > 0 && y > y < AIN_LINES-1) ? forceMap[x-1][y+1] : 0;
        touchSquare[1][2] = (y < AIN_LINES-1) ? forceMap[x][y+1] : 0;
        touchSquare[2][2] = (x < DOUT_LINES-1 && y < AIN_LINES-1) ? forceMap[x-1][y+1] : 0;
      
#if 1
        Serial.print(x);
        Serial.print(",");
        Serial.print(y);
        Serial.println(",");
        for (int i = 0; i < 3; i++) {
          for (int j = 0; j < 3; j++) {
            Serial.print(touchSquare[i][j]);
            Serial.print(",");    
            touchSquare[x][y] = 0;
          }
          Serial.println();
        }
        Serial.print("/");
#endif
      }
    }
  }
}
