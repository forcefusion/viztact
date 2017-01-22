#include "hardware.h"

static const char sel_pins[] = SEL_PINS;
static const char num_of_pins = sizeof(sel_pins) / sizeof(char);

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
  // ## Handling the pin order arrangement difference according to hardware layout
  // LINES_SPLIT means lines go into matrix from two sides, thus, these lines will not be sequential
  // but half of them will be in reversed order
  // ## PIN0_AT_MID means the first pin started in the middle of matrix, therefore, the first half
  // lines are in reversed order and the rest half lines are in normal order, and vice versa.
  if (LINES_SPLIT == DOUT_LINES)  {
    if (line < LINES_SPLIT / 2) {
      line = PIN0_AT_MID ? LINES_SPLIT / 2 - line - 1 : line;
    }
    else {
      line = PIN0_AT_MID ? line : LINES_SPLIT + line - 1 - LINES_SPLIT / 2;
    }
  }
  
  digitalWrite(DOUT_LCLK, LOW);

#if REV_ORDER
  // Count in decending order due to the hardware design is reversed from physical space
  for (int i = DOUT_LINES-1; i >= 0; i--) {
#else
  for (int i = 0; i < DOUT_LINES; i++) {
#endif
    digitalWrite(DOUT_CLK, LOW);
    digitalWrite(DOUT_REG, i == line);
    digitalWrite(DOUT_CLK, HIGH);
  }

  digitalWrite(DOUT_LCLK, HIGH);
}

int vt_read(int line) {
  // ## Handling the pin order arrangement difference according to hardware layout
  // LINES_SPLIT means lines go into matrix from two sides, thus, these lines will not be sequential
  // but half of them will be in reversed order
  // ## PIN0_AT_MID means the first pin started in the middle of matrix, therefore, the first half
  // lines are in reversed order and the rest half lines are in normal order, and vice versa.
  if (LINES_SPLIT == AIN_LINES)  {
    if (line < LINES_SPLIT / 2) {
      line = PIN0_AT_MID ? LINES_SPLIT / 2 - line - 1 : line;
    }
    else {
      line = PIN0_AT_MID ? line : LINES_SPLIT + line - 1 - LINES_SPLIT / 2;
    }
  }
  
  for (int i = 0; i < num_of_pins; i++) {
    digitalWrite(sel_pins[i], (line & (1 << (i + 1) - 1)) >> i);  
  }

  int pipe = line < 16 ? A1 : A0;      // lower 16 pins is read by A1, higher 16 pins is read by A0
  return analogRead(pipe);
}
