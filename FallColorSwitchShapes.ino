/**************************************************************************
  Draws concentric shapes rectangles using drawSmooth
 **************************************************************************/
#include <TFT_eSPI.h> 
#include <SPI.h>

TFT_eSPI tft = TFT_eSPI(); 

void setup() {
  tft.init();
  tft.setRotation(1);   // 1 = landscape, 2 = portrait
}

void loop() {
  concentricInscribedShapes();
}

void concentricInscribedShapes(){
  // black background color
  tft.fillScreen(TFT_BLACK);
  // Colors of fall transitioning: Dark Green, Green, Green Yellow, Yellow, Gold, Orange, Red
  const unsigned long color_arr[7] = {0x03E0, 0x07E0, 0xB7E0, 0xFEA0, 0xFFE0, 0xFDA0, 0xF800};
  for (int16_t x = 0, y = 0; x < tft.width(); x += 10, y += 1) {
    
    // drawSmooth functions handle anti-aliasing. try drawing with inscribed rectangle and circles
    tft.drawSmoothRoundRect(tft.width() / 2 - x / 2, tft.height() / 2 - x / 2, 1, 1, 
      x, x, color_arr[y % (sizeof(color_arr) / sizeof(int))]);
    tft.drawSmoothCircle(tft.width() / 2, tft.height() / 2, x, 1, color_arr[y % (sizeof(color_arr) / sizeof(int))]);
    
    // This is drawing rectangle and circle without anti-aliasing.
    // tft.drawRect(tft.width() / 2 - x / 2, tft.height() / 2 - x / 2 , x, x, color_arr[y % (sizeof(color_arr) / sizeof(int))]);
    // tft.drawCircle(tft.width() / 2, tft.height() / 2 , x, color_arr[y % (sizeof(color_arr) / sizeof(int))]);
    
    // draw circl + rectangle 500 seconds
    delay(500);
  }
}
