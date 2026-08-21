#include <IRremote.hpp>
#include <LedControl.h>

// ---- Pin setup ----
const int RECV_PIN = 2;
LedControl lc = LedControl(11, 13, 10, 1); // DIN, CLK, CS, number of matrices

// ---- IR remote codes ----
#define CODE_7    0xFF007F80UL  // Smiley
#define CODE_8    0xF00F7F80UL  // Letter N
#define CODE_9    0xE6197F80UL  // Heart
#define CODE_MODE 0xE51A7F80UL  // All LEDs on
#define CODE_U    0xED127F80UL // Power toggle

bool powerOn = false; // tracks toggle state for U button

// ---- Patterns (8x8, each byte = one row) ----
byte smiley[8]  = {0x3C,0x42,0xA5,0x81,0xA5,0x99,0x42,0x3C};
byte heart[8]   = {0x66,0xFF,0xFF,0xFF,0x7E,0x3C,0x18,0x00};
byte letterN[8] = {0x81,0xC1,0xA1,0x91,0x89,0x85,0x83,0x81};
byte allOn[8]   = {0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF};
byte topRow[8]  = {0xFF,0x00,0x00,0x00,0x00,0x00,0x00,0x00};
byte blank[8]   = {0,0,0,0,0,0,0,0};

void showPattern(byte pattern[8]) {
  for (int row = 0; row < 8; row++) {
    lc.setRow(0, row, pattern[row]);
  }
}

void setup() {
  Serial.begin(9600);
  IrReceiver.begin(RECV_PIN, ENABLE_LED_FEEDBACK);

  lc.shutdown(0, false);     // wake up display
  lc.setIntensity(0, 8);     // brightness (0-15)
  lc.clearDisplay(0);
}

void loop() {
  if (IrReceiver.decode()) {

    // Ignore repeat frames (happens when button held or pressed too fast)
    if (IrReceiver.decodedIRData.flags & IRDATA_FLAGS_IS_REPEAT) {
      IrReceiver.resume();
      return;
    }

    unsigned long code = IrReceiver.decodedIRData.decodedRawData;
    Serial.println(code, HEX);

    switch (code) {
      case CODE_7:
        showPattern(smiley);
        break;

      case CODE_8:
        showPattern(letterN);
        break;

      case CODE_9:
        showPattern(heart);
        break;

      case CODE_MODE:
        showPattern(allOn);
        break;

      case CODE_U:
        powerOn = !powerOn;
        showPattern(powerOn ? topRow : blank);
        break;
    }

    IrReceiver.resume();
  }
}