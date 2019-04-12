/*
 Original Code Developer:  Robby Sammelson
 Adapted by:  Rob Cartwright (for 36 tubes, and to speed up the scrolling text, etc.
 Date:  04-14-20148
 Name:  2018 BleacherBling - for USFIRST Indiana State Championship

 Matrix Size:  36 pixel tubes x 12 tubes
 
 */

// --- definitions -----------------------------------------------------

//#include <Adafruit_GFX.h>
//#include <Adafruit_NeoPixel.h>
#include <Adafruit_NeoMatrix.h>
#include <gamma.h>

// Example for NeoPixel Shield.  In this application we'd like to use it
// as a 5x8 tall matrix, with the USB port positioned at the top of the
// Arduino.  When held that way, the first pixel is at the top right, and
// lines are arranged in columns, progressive order.  The shield uses
// 800 KHz (v2) pixels that expect GRB color data.
Adafruit_NeoMatrix matrix = Adafruit_NeoMatrix(36, 12, 6,
                            NEO_MATRIX_BOTTOM  + NEO_MATRIX_RIGHT +
                            NEO_MATRIX_COLUMNS + NEO_MATRIX_ZIGZAG,
                            NEO_GRB            + NEO_KHZ800);

#define ourAlliance matrix.Color(0, 255, 0)

// --- variables ---------------------------------------------------------

byte pos = 0;
int counter = 12;  // case statement to start on.  

/* You can set this <counter> to something different, to jump right to a new <case> that you have created
 *  ...either for testing purposes, or to get it up in a hurry, when you make up a phrase to honor a team or such.
*/

// ---setup----------------------------------------------------------------------

void setup() {
  // put your setup code here, to run once:
  matrix.begin();
  matrix.setBrightness(255);
  matrix.setTextWrap(false);

//matrix.print(F("Howdy"));
//  delay(10000);


}


// === loop =====================================================================

void loop() {
  // put your main code here, to run repeatedly:
  
//  if (Serial.available() > 0) 
//  {   // the following code let's you use Serial Monitor to enter a CASE number to jump immediately to
//    
//    String p = "";
//    while (Serial.available() > 0) {
//      p += String((char)Serial.read());
//    }
//    Serial.println("How many times to print: " + p);
//    while (Serial.available() <= 0) {}
//    int times = Serial.parseInt();
//    Serial.println(times);
//    for (int tm = 0; tm < times; tm++) {
//      Serial.println("Printing: " + p + ". Time number " + String(tm + 1) + ".");
//      int len = p.length() * 6;
//      Serial.println(-20 - len);
//      for (int i = 12; i > -20 - len; i--) { // -32 * p.length()
//        unsigned int t = millis();
//        matrix.setCursor(i, 2);
//        matrix.setTextColor(Wheel(pos));
//        matrix.print(p);
//        updateScreen();
//        matrix.clear();
//        delay(70);
//        //      Serial.println(String(i) + ": " + String(millis() - t));
//      } // for
//    } // for
//    
//    Serial.println("done");
//    gap();
//    return;
//    
//  } // if serial
  
  int caseTotal = 13;  // one greater than the highest case x statement that follows
  
  //Serial.println("counter: " + String(counter % numberSeq));
  
  switch (counter % caseTotal) 
  {
    case 0:
      scrolltext("     PHYXTGEARS 1720 - BleacherBling!!!", matrix.Color(0, 255, 0));
      break;
      
    case 1:
      bar(false);   // random colored bars left and right
      break;
      
    case 2:
      scrolltext("     Cooperitition!!", matrix.Color(255, 255, 0));
      break;
      
    case 3:
      flash();   // white strobes
      break;
      
    case 4:
      wavedownPatriotic();
      // bar(true);    // random horz lines
      delay(2000);
      break;
      
    case 5:
      sparkle();   //sparkle - random colored dots
      //flash(false);  // was flash(false);
      //make it put dots up a little faster
      break;
      
    case 6:
      for (int i = 0; i < 3; i++)  // rectangles zooming in.
      {   
        rectangleZoom(50, true);
        rectZoom(50, true);
      }
delay(1000);
      for (int i = 0; i < 3; i++)  // rectangles zooming in.
      {   
        rectangleZoomPatriotic(50, false);
        rectZoom(50, false);
      }
      delay(1000);
      break;

    case 7:
      scrolltext("     Gracious Professionalism!!", matrix.Color(255, 0, 255));
      break;

    case 8:
      coloredDots ();   // red, white, and blue larger splotches dots
      delay(2000);
      break;

    case 9:
      waverightPatriotic();
      delay(2000);
      break;
      
    case 10:
      announcementText();  // insert text in function call below, for a one-off announcement
      break;    
      
    case 11:
      //scrolltext("     Shout out to young Damien, Team 340!!!", matrix.Color(0, 0, 255));
      spiral();
      spiral();
      spiral();
      spiral();
      break;

    case 12:
    sinewave();
    delay (300);
    break;
    
 //   case 12:
 //    heartBeat();
  //   delay(300);
//     matrix.clear();
//     heartBeat();
//     delay(300);
//     matrix.clear();
//     heartBeat();
//     delay(300);
//     matrix.clear();
     

  }  //switch
  
  gap();
  counter++;
  
}  // loop



// ==== function calls =================================================
// in alphabetical order

// ----------------------------------------------------------------------

void announcementText () {
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

// ----------------------------------------------------------------------

void bar (bool d) {
  for (int i = 0; i < 2; i++) {
    for (int j = 0; j < (d ? matrix.height() : matrix.width()); j++) {
      matrix.drawLine((d ? 0 : j), (d ? j : 0), (d ? matrix.width() : j), (d ? j : matrix.height()), Wheel(pos));
      updateScreen();
      delay(30);
    }
    for (int j = (d ? matrix.height() : matrix.width()) - 1; j >= 0; j--) {
      matrix.drawLine((d ? 0 : j), (d ? j : 0), (d ? matrix.width() : j), (d ? j : matrix.height()), Wheel(pos));
      updateScreen();
      delay(30);
    }
  }
}

// --------------still under development----------------------------------------

void bumpLine()
{}

//-------------------------------------------------------

void coloredDots () 
{
  for (int i = 0; i < 250; i++) 
  {
    uint16_t color = matrix.Color(random(127)+126, random(127)+126, random(127)+126);
    int x = random(matrix.width());
    int y = random(matrix.width());
    matrix.drawPixel(x, y, color);
    updateScreen();
  }
}

// ----------------------------------------------------------------------

void flash () {

  uint16_t color = matrix.Color(255, 255, 255);
  int x = 0;
  int y = 0;
  
  for (int i = 1; i <= 300; i++) {
    
    x = random(matrix.width());
    y = random(matrix.width());
    //color = matrix.Color(255, 255, 255);
    matrix.drawPixel(x, y, matrix.Color(255, 255, 255));
    //matrix.drawPixel(x, y, color);
    updateScreen();
    delay(10);
    matrix.drawPixel(x, y, matrix.Color(0, 0, 0));
    
  } // for
} // flash()

// ----------------------------------------------------------------------

void gap () {
  matrix.clear();
  updateScreen();
 
  delay(300);
}


// --still under development---------------------------------------------------------------------

void heartBeat()
{
  int heartbeatDelay = 30; // between each pixel
  
  float yHeart = 5;
  int count = 0; 
  int beatOne = 8;
  int beatTwo = 18;
  int beatThree = 28;
  
  for(count=0; count < 105; count++)
  {

    if ((count > beatOne) and (count < beatOne+3))  // heartbeat going up
    {
    matrix.drawPixel(count,5,matrix.Color(255,255,255));
    matrix.show();
    delay(heartbeatDelay);
    }

    if ((count > beatOne + 4) and (count < beatOne + 12))  // heartbeat going down

   {
    matrix.drawPixel(count,count-13,matrix.Color(255,255,255));
    matrix.show();
    delay(heartbeatDelay);
   }

    if ((count > beatOne + 12) and (count < beatTwo + 16))  // heartbeat going up again
    {
    matrix.drawPixel(count+23,10-count,matrix.Color(255,255,255));
    matrix.show();
    delay(heartbeatDelay);
    } 
    

    matrix.drawPixel(count,5,matrix.Color(255,255,255));
    matrix.show();
    delay(heartbeatDelay);
    
  }  // for
    
}  // heartbeat
  

// ----------------------------------------------------------------------

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
//------------------------------------------------------------
void rectZoom(int Delay, bool noFill) {
  int x = 0;
  int y = 0;
  int width = matrix.width();
  int height = matrix.height();
  int iterations = min(width / 2, height / 2);
  for (int i = 0; i < iterations; i++) {
    matrix.drawRect(x, y, width, height, Wheel(pos));
    delay(Delay);
    updateScreen();
    pos += 5
    ;
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
//-------------------------------------------------------

void rectangleZoomPatriotic(int Delay, bool noFill) 
{
  int x = 0;
  int y = 0;
  int width = matrix.width();
  int height = matrix.height();
  int iterations = min(width / 2, height / 2);
  Serial.println(iterations);
  for (int i = 0; i < 2; i++) {
    matrix.drawRect(x, y, width, height, matrix.Color(200,0,0));  // red left part
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

  }

  for (int i = 2; i < 4; i++) {
    matrix.drawRect(x, y, width, height, matrix.Color(200,200,200));  // white middle part 
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

  }

    for (int i = 4; i < 6; i++) {
    matrix.drawRect(x, y, width, height, matrix.Color(0,0,200));  // blue right portion
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

  }

}
// ----------------------------------------------------------------------

void rectFromCenter (int centerX, int centerY, int radius, uint16_t color) {
  int a = radius * 2;
  a++;
  matrix.drawRect((centerX - radius), (centerY - radius), a, a, color);
  //Serial.println("X: " + String(centerX) + " Y: " + String(centerY) + " R: " + String(radius));
}

// ---------------------------------------------------------------------------------------

void scrolltext (String p, uint16_t color) {
  int a = p.length() * 6;
  int b = -20 - a;
  //Serial.println(String(a) + " " + String(b));
  for (int i = 12; i > b; i--) { // -32 * p.length()
   // Serial.print(String(i) + " ");
    unsigned int t = millis();
    matrix.setCursor(i, 2);
    matrix.setTextColor(color);
    //matrix.setTextColor(matrix.Color(0, 255, 0));
    matrix.print(p);
    updateScreen();
    matrix.clear();
    delay(25);   // this was 30, and we set it to 25 @ 07-13-2018 @ 2:51pm
  }
  //Serial.println();
}

// -------------------------------------------------------

void sinewave()
{
  int pixelsPerRow = 3;
  
  for (int x = 0; x < 36 * pixelsPerRow; x++)
  {
    float calcX = x / ((float)pixelsPerRow) / 1.8;
    matrix.drawPixel(x / pixelsPerRow, 5 * sin(calcX) + 6, Wheel(255));
    updateScreen();
    //delay (1);
  }

  delay(1000);

  
  for (int x = 0; x < 36 * pixelsPerRow; x++)
  {
    float calcX = x / ((float)pixelsPerRow) / 1.8;
    matrix.drawPixel(x / pixelsPerRow, 5 * sin(calcX) + 6, Wheel(180));
    updateScreen();
    //delay (1);
  }

  delay(1000);

  float colorPerX = 5 * 255 / (36 * pixelsPerRow);
  for (int x = 0; x < 36 * pixelsPerRow; x++)
  {
    float calcX = x / ((float)pixelsPerRow) / 1.8;
    matrix.drawPixel(x / pixelsPerRow, 5 * sin(calcX) + 6, Wheel(x * colorPerX));
    updateScreen();
    //delay (1);
  }

  delay(1000);
}



//-------------------------------------------------------

void sparkle ()    //void flash (bool w) 
{
  int colorChoice = 0;
  for (int i = 0; i < 150; i++) 
  {
    uint16_t color = matrix.Color(0,0,0);   // set the default color to black, while inititalizing the variable "color"
    // uint16_t color = matrix.Color(random(127)+126, random(127)+126, random(127)+126);

    colorChoice = random(1,4);
    Serial.println(colorChoice);
    
    //  color = matrix.Color(255, 255, 255);
    if (colorChoice == 1)
    {
      color = matrix.Color(30,50,240);  //blue
    }
    if (colorChoice == 2)
    {
      color = matrix.Color(250,175,30);  //gold
    }
    if (colorChoice == 3)
    {
      color = matrix.Color(25,255,40);   //green
    }
    
    int x = random(matrix.width());
    int y = random(matrix.width());
    matrix.drawCircle(x, y, 2, color);
    matrix.drawCircle(x-1, y, 2, color);
    matrix.drawCircle(x+1, y, 2, color);
    matrix.drawCircle(x, y-1, 2, color);
    matrix.drawCircle(x, y+1, 2, color);
    
    updateScreen();
      matrix.drawPixel(x, y, matrix.Color(0, 0, 0));

  }
}

// ----------------------------------------------------------------------

void spiral () 
{
  int x=0; 
  int y=0;
  for (int pixelPosition = 0; pixelPosition < 36; pixelPosition++) 
  {
    //pixelPosition = pixelPosition + 1;
    matrix.drawLine(pixelPosition, 0, 35-pixelPosition, 11, Wheel(pos*2));
    updateScreen();
  }  
  for (int pixelPosition = 0; pixelPosition < 12; pixelPosition++)
  {
    matrix.drawLine(0, 11-pixelPosition, 35, pixelPosition, Wheel(pos*2));
    updateScreen();
  }
  
}       
//-----------------------------------------------------------------------


     



// ----------------------------------------------------------------------
void updateScreen () {
  pos += 5;
  matrix.show();
}

//-------------------------------------------------------

void waveDown () 
{
  for (int i = 0; i < 3; i++) 
  {
    for (int j = 0; j < (true ? matrix.height() : matrix.width()); j++) 
    {
      matrix.drawLine((true ? 0 : j), (true ? j : 0), (true ? matrix.width() : j), (true ? j : matrix.height()), Wheel(pos));
      updateScreen();
      delay(20);
    }
//    for (int j = (true ? matrix.height() : matrix.width()) - 1; j >= 0; j--) 
//    {
//      matrix.drawLine((true ? 0 : j), (true ? j : 0), (true ? matrix.width() : j), (true ? j : matrix.height()), Wheel(pos));
//      updateScreen();
//      delay(20);
//    }
  }
}

//-------------------------------------------------------

void wavedownPatriotic () 
{
  for (int i = 0; i < 3; i++) 
  {
    for (int j = 0; j < 4; j++) 
    {
      matrix.drawLine((true ? 0 : j), (true ? j : 0), (true ? matrix.width() : j), (true ? j : matrix.height()), matrix.Color(200,0,0));
      updateScreen();
      delay(10);
    }

    for (int j = 4; j < 8; j++) 
    {
      matrix.drawLine((true ? 0 : j), (true ? j : 0), (true ? matrix.width() : j), (true ? j : matrix.height()), matrix.Color(200,200,200));
      updateScreen();
      delay(10);
    }
    
    for (int j = 8; j < 12; j++) 
    {
      matrix.drawLine((true ? 0 : j), (true ? j : 0), (true ? matrix.width() : j), (true ? j : matrix.height()), matrix.Color(0,0,200));
      updateScreen();
      delay(10);
    }

  }
}

//-------------------------------------------------------

void waveRight () 
{
  for (int i = 0; i < 3; i++) 
  {
    for (int j = 0; j < (false ? matrix.height() : matrix.width()); j++) 
    {
      matrix.drawLine((false ? 0 : j), (false ? j : 0), (false ? matrix.width() : j), (false ? j : matrix.height()), Wheel(pos));
      updateScreen();
      delay(20);
    }
//    for (int j = (fasle ? matrix.height() : matrix.width()) - 1; j >= 0; j--) 
//    {
//      matrix.drawLine((false ? 0 : j), (false ? j : 0), (false ? matrix.width() : j), (false ? j : matrix.height()), Wheel(pos));
//      updateScreen();
//      delay(20);
//    }
  }
}

// ----------------------------------------------------------------------

void waverightPatriotic ()

{
  for (int i = 0; i < 3; i++) 
  {
//    for (int j = 0; j < (false ? matrix.height() : matrix.width()); j++) 
      for (int j = 0; j < 12; j++) 
    {
      matrix.drawLine((false ? 0 : j), (false ? j : 0), (false ? matrix.width() : j), (false ? j : matrix.height()), matrix.Color(200,0,0));
      updateScreen();
      delay(10);
    }

        for (int j = 12; j < 24; j++) 
    {
      matrix.drawLine((false ? 0 : j), (false ? j : 0), (false ? matrix.width() : j), (false ? j : matrix.height()), matrix.Color(200,200,200));
      updateScreen();
      delay(10);
    }

          for (int j = 24; j < 36; j++) 
    {
      matrix.drawLine((false ? 0 : j), (false ? j : 0), (false ? matrix.width() : j), (false ? j : matrix.height()), matrix.Color(0,0,200));
      updateScreen();
      delay(10);
    }
  }
}
// ----------------------------------------------------------------------

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
