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

#define ourAlliance matrix.Color(0, 255, 0)

void setup() {
  // put your setup code here, to run once:
  matrix.begin();
  matrix.setBrightness(255);
  matrix.setTextWrap(false);
}

byte pos = 0;
int c = 7;

void loop() {
  // put your main code here, to run repeatedly:
  if (Serial.available() > 0) {
    String p = "";
    while (Serial.available() > 0) {
      p += String((char)Serial.read());
    }
    Serial.println("How many times to print: " + p);
    while (Serial.available() <= 0) {}
    int times = Serial.parseInt();
    Serial.println(times);
    for (int tm = 0; tm < times; tm++) {
      Serial.println("Printing: " + p + ". Time number " + String(tm + 1) + ".");
      int len = p.length() * 6;
      Serial.println(-20 - len);
      for (int i = 12; i > -20 - len; i--) { // -32 * p.length()
        unsigned int t = millis();
        matrix.setCursor(i, 2);
        matrix.setTextColor(Wheel(pos));
        matrix.print(p);
        updateScreen();
        matrix.clear();
        delay(70);
        //      Serial.println(String(i) + ": " + String(millis() - t));
      }
    }
    Serial.println("done");
    gap();
    return;
  }
  int numberSeq = 8;
  Serial.println("c: " + String(c % numberSeq));
  switch (c % numberSeq) {
    case 0:
      scrolltext("PHYXTGEARS", matrix.Color(0, 255, 0));
      break;
    case 1:
      bar(false);
      break;
    case 2:
      flash(true);
      break;
    case 3:
      scrolltext("GOOD JOB!", matrix.Color(255, 255, 255));
      break;
    case 4:
      randomText();
      break;
    case 5:
      bar(true);
      break;
    case 6:
      flash(false);
      break;
    case 7:
      for (int i = 0; i < 10; i++) {
        rectangleZoom(50, false);
      }
      break;
  }
  gap();
  c++;
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

void bar (bool d) {
  for (int i = 0; i < 7; i++) {
    for (int j = 0; j < (d ? matrix.height() : matrix.width()); j++) {
      matrix.drawLine((d ? 0 : j), (d ? j : 0), (d ? matrix.width() : j), (d ? j : matrix.height()), Wheel(pos));
      updateScreen();
      delay(40);
    }
    for (int j = (d ? matrix.height() : matrix.width()) - 1; j >= 0; j--) {
      matrix.drawLine((d ? 0 : j), (d ? j : 0), (d ? matrix.width() : j), (d ? j : matrix.height()), Wheel(pos));
      updateScreen();
      delay(40);
    }
  }
}

void scrolltext (String p, uint16_t color) {
  for (int i = 12; i > -20 - p.length() * 6; i--) { // -32 * p.length()
    unsigned int t = millis();
    matrix.setCursor(i, 2);
    matrix.setTextColor(matrix.Color(0, 255, 0));
    matrix.print(p);
    updateScreen();
    matrix.clear();
    delay(50);
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
    //    Serial.println(String(i) + ": " + String(millis() - t));
  }
}

void alliance () {
  String p = "GRACIOUS PROFESSIONALISM";
  for (int i = 12; i > -90; i--) { // -32 * p.length()
    unsigned int t = millis();
    matrix.setCursor(i, 2);
    matrix.setTextColor(ourAlliance);
    matrix.print(p);
    updateScreen();
    matrix.clear();
    delay(70);
    //    Serial.println(String(i) + ": " + String(millis() - t));
  }
}

void randomText () {
  //  String p = "SHOUT OUT TO 447 ROBOT BLING";
  //  for (int i = 12; i > -150; i--) { // -32 * p.length()
  //    unsigned int t = millis();
  //    matrix.setCursor(i, 2);
  //    matrix.setTextColor(ourAlliance);
  //    matrix.print(p);
  //    updateScreen();
  //    matrix.clear();
  //    delay(70);
  //    //    Serial.println(String(i) + ": " + String(millis() - t));
  //  }
}

void flash (bool w) {
  for (int i = 0; i < 1500; i++) {
    uint16_t color = matrix.Color(random(256), random(256), random(256));
    if (w) {
      color = matrix.Color(255, 255, 255);
    }
    int x = random(matrix.width());
    int y = random(matrix.width());
    matrix.drawPixel(x, y, color);
    updateScreen();
    if (w) {
      matrix.drawPixel(x, y, matrix.Color(0, 0, 0));
    }
  }
}

void rectangleZoom(int Delay, bool noFill) {
  int x = 0;
  int y = 0;
  int width = matrix.width();
  int height = matrix.height();
  int iterations = min(width / 2, height / 2);
  for (int i = 0; i < iterations; i++) {
    matrix.drawRect(x, y, width, height, Wheel(pos));
    delay(Delay);
    updateScreen();
    pos += 10;
    if (noFill) {
      matrix.clear();
    }
    x += 1;
    y += 1;
    width -= 2;
    height -= 2;
    //    if (Length < c) {
    //      c += 1;
    //    }
  }
}

void rectFromCenter (int centerX, int centerY, int radius, uint16_t color) {
  int a = radius * 2;
  a++;
  matrix.drawRect((centerX - radius), (centerY - radius), a, a, color);
  Serial.println("X: " + String(centerX) + " Y: " + String(centerY) + " R: " + String(radius));
}
