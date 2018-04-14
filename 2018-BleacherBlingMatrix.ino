#include <Adafruit_NeoMatrix.h>
#include <gamma.h>

// Example for NeoPixel Shield.  In this application we'd like to use it
// as a 5x8 tall matrix, with the USB port positioned at the top of the
// Arduino.  When held that way, the first pixel is at the top right, and
// lines are arranged in columns, progressive order.  The shield uses
// 800 KHz (v2) pixels that expect GRB color data.
Adafruit_NeoMatrix matrix = Adafruit_NeoMatrix(12, 12, 6,
                            NEO_MATRIX_BOTTOM  + NEO_MATRIX_RIGHT +
                            NEO_MATRIX_COLUMNS + NEO_MATRIX_ZIGZAG,
                            NEO_GRB            + NEO_KHZ800);

#define ourAlliance matrix.Color(255, 255, 255)

void setup() {
  // put your setup code here, to run once:
  matrix.begin();
  matrix.setBrightness(255);
  matrix.setTextWrap(false);
}

byte pos = 0;

void loop() {
  // put your main code here, to run repeatedly:
  gears();
  gap();
  alliance();
  gap();
  bar();
  gap();
}

void gap () {
  matrix.clear();
  updateScreen();
  delay(500);
}

uint32_t Wheel (byte WheelPos) {
  WheelPos = 255 - WheelPos;
  if (WheelPos < 85) {
    return matrix.Color(255 - WheelPos * 3, 0, WheelPos * 3);
  }
  if (WheelPos < 170) {
    WheelPos -= 85;
    return matrix.Color(0, WheelPos * 3, 255 - WheelPos * 3);
  }
  WheelPos -= 170;
  return matrix.Color(WheelPos * 3, 255 - WheelPos * 3, 0);
}

void updateScreen () {
  pos += 5;
  matrix.show();
}

void bar () {
  for (int i = 0; i < 7; i++) {
    for (int y = 0; y < matrix.height(); y++) {
      matrix.drawLine(0, y, matrix.width(), y, Wheel(pos));
      updateScreen();
      //      matrix.clear();
      delay(40);
    }
    for (int y = matrix.height() - 1; y >= 0; y--) {
      for (int x = 0; x < matrix.width(); x++) {
        matrix.drawPixel(x, y, Wheel(pos));
      }
      updateScreen();
      //      matrix.clear();
      delay(40);
    }
  }
}

void gears () {
  String p = "PHYXTGEARS";
  for (int i = 12; i > -70; i--) { // -32 * p.length()
    unsigned int t = millis();
    matrix.setCursor(i, 2);
    matrix.setTextColor(matrix.Color(0, 255, 0));
    matrix.print(p);
    updateScreen();
    matrix.clear();
    delay(70);
    Serial.println(String(i) + ": " + String(millis() - t));
  }
}

void alliance () {
  String p = "1720 1741 5188";
  for (int i = 12; i > -90; i--) { // -32 * p.length()
    unsigned int t = millis();
    matrix.setCursor(i, 2);
    matrix.setTextColor(ourAlliance);
    matrix.print(p);
    updateScreen();
    matrix.clear();
    delay(70);
    Serial.println(String(i) + ": " + String(millis() - t));
  }
}

