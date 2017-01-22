#include "hardware.h"
#include "touch.h"

#define ENABLE_MEASUREMENT 0

static int count = 0;                // Scan rate counter
static int t0 = millis();            // Time in (ms)

void setup() {
  vt_init();
  VT_TOUCH.hInvert = false;
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


