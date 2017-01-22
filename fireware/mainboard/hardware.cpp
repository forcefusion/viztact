#include "hardware.h"

const char sel_pins[] = SEL_PINS;
const char num_of_pins = sizeof(sel_pins) / sizeof(char);

void vt_init() {
  pinMode(DOUT_REG, OUTPUT);
  pinMode(DOUT_LCLK, OUTPUT);
  pinMode(DOUT_CLK, OUTPUT);

  digitalWrite(DOUT_LCLK, HIGH);
  digitalWrite(DOUT_CLK, HIGH);
  digitalWrite(DOUT_REG, LOW);

  // initialize analog read lines selection pins
  for (int i = 0; i < num_of_pins; i++) {
    pinMode(sel_pins[i], OUTPUT);
  }
}

void vt_pullup(int line) {
  digitalWrite(DOUT_LCLK, LOW);

#if REV_ORDER
  // Count in decending order due to the hardware design is reversed from physical space
  for (int i = DOUT_LINES-1; i >= 0; i--) {
    digitalWrite(DOUT_CLK, LOW);
    digitalWrite(DOUT_REG, i == line);
    digitalWrite(DOUT_CLK, HIGH);
  }
#else
  // Count in decending order due to the hardware design is reversed from physical space
  for (int i = 0; i < DOUT_LINES; i++) {
    digitalWrite(DOUT_CLK, LOW);
    digitalWrite(DOUT_REG, i == line);
    digitalWrite(DOUT_CLK, HIGH);
  }
#endif

  digitalWrite(DOUT_LCLK, HIGH);
}

int vt_read(int line) {
  for (int i = 0; i < num_of_pins; i++) {
    digitalWrite(sel_pins[i], (line & (1 << (i + 1) - 1)) >> i);  
  }

  int pipe = line < 16 ? A1 : A0;      // lower 16 pins is read by A1, higher 16 pins is read by A0
  return analogRead(pipe);
}
