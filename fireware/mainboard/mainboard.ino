const int AIN_SEL_PINS[] = {4, 5, 6, 7};    // 4067 1:16 MUX, Analog Line Selection PINS D4, D5, D6, D7
const int DOUT_LCLK = 8;                    // 595 Register-Shifter, Local Clock control D8
const int DOUT_CLK = 9;                     // 595 Register-Shifter, Data Clock control D9
const int DOUT_REG = 10;                    // 595 Register-Shifter, Register State control D10
const int ROWS = 16;                        // IN
const int COLS = 24;                        // OUT
const int DOUT_LINES = COLS;
const int AIN_LINES = ROWS;

static int c = 0;                   // Scan rate counter
static int t = millis();            // Time in (ms)
static int forceMap[24][16] = {0};  // Full force map
static int touchSquare[3][3] = {0}; // Temporary 3x3 force map for evaluation force center
static  bool hasData = false;

typedef struct touchEvent {
  unsigned int id;
  unsigned int seq;
  unsigned int ts;
  unsigned int gridX;
  unsigned int gridY;
  float posX;
  float posY;
  unsigned int centerForce;
  unsigned int totalForce;
  unsigned char forceLevel;
  unsigned char levelUp;
  unsigned char levelDown;
  unsigned char padding;
} touchEvent;

touchEvent te[10];
int validEvent = 0;

void vt_pullup(int line) {
  digitalWrite(DOUT_LCLK, LOW);
  // Count in decending order due to the hardware design is reversed from physical space
  for (int i = DOUT_LINES-1; i >= 0; i--) {
    digitalWrite(DOUT_CLK, LOW);
    digitalWrite(DOUT_REG, i == line);
    digitalWrite(DOUT_CLK, HIGH);
  }
  digitalWrite(DOUT_LCLK, HIGH);
}

int vt_read(int line) {
  digitalWrite(AIN_SEL_PINS[0], line & 1);
  digitalWrite(AIN_SEL_PINS[1], (line & 3) >> 1);
  digitalWrite(AIN_SEL_PINS[2], (line & 7) >> 2);
  digitalWrite(AIN_SEL_PINS[3], (line & 15) >> 3);

  int pipe = line < 16 ? A1 : A0;
  return analogRead(pipe);
}

void setup() {
  pinMode(DOUT_REG, OUTPUT);
  pinMode(DOUT_LCLK, OUTPUT);
  pinMode(DOUT_CLK, OUTPUT);

  digitalWrite(DOUT_LCLK, HIGH);
  digitalWrite(DOUT_CLK, HIGH);
  digitalWrite(DOUT_REG, LOW);

  // initialize analog read lines selection pins
  for (int i = 0; i < 4; i++) {
    pinMode(AIN_SEL_PINS[i], OUTPUT);
  }
}

void loop() {
  hasData = false;

  // force sensor scan: pull up digital output lines sequencially and read analog input lines sequencially
  for (int x = 0; x < 24; x++) {
    vt_pullup(x < 12 ? x : 35 - x);
    for (int y = 0; y < 16; y++) {
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
      forceMap[x][y] = val;
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

