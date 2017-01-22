#include "hardware.h"
#include "touch.h"

static int c = 0;                   // Scan rate counter
static int t = millis();            // Time in (ms)
int forceMap[24][16] = {0};  // Full force map
static  bool hasData = false;

touchEvent te[10];
int validEvent = 0;

void setup() {
  vt_init();
}

void loop() {
  hasData = false;

  // force sensor scan: pull up digital output lines sequencially and read analog input lines sequencially
  for (int x = 0; x < 24; x++) {
    int yy = 0;
    vt_pullup(x < 12 ? x : 35 - x);
    for (int y = 15; y >= 0; y--) {
      int val = vt_read(y);

      // force value below 4 is filtered out as noise
      if (val > 4) {
        hasData = true;
#if 0   // console prints for debuging 
        Serial.print(x);
        Serial.print(",");
        Serial.print(y);
        Serial.print(",");
        Serial.print(val);
        Serial.print("/");
#endif
      }
      else {
        val = 0;
      }
      forceMap[x][yy++] = val;
    }
  }

  if (hasData) {
    processForceMap();
    Serial.println();
  }
  
#if 0     // calculate scan rate (Hz) in 10 seconds period
  int t1 = millis();

  if (t1 - t >= 10000) {
    Serial.println(c);
    t = t1;
    c = 0;
  }
  else {
    c++;
  }
#endif
}


