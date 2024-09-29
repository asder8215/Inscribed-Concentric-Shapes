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

  // Colors of fall transitioning: Dark Green, Green, Green Yellow, Yellow, Gold, Orange, Red, Brown
  const unsigned long color_arr[8] = {0x03E0, 0x07E0, 0xB7E0, 0xFEA0, 0xFFE0, 0xFDA0, 0xF800, 0x9A60};
  int32_t color_ind = 0;

  // square top left coor + length
  int32_t sqr_length = 4;
  int32_t sqr_x = (tft.width() / 2) - ceil((sqr_length * sqrt(2))/2);
  int32_t sqr_y = (tft.height() / 2) - ceil((sqr_length * sqrt(2))/2);

  // circle center coor + radius
  int32_t cir_x = tft.width() / 2;
  int32_t cir_y = tft.height() / 2;
  int32_t cir_r = (int32_t) ceil(((sqr_length * sqrt(2))/2));

  // keep drawing on the board until either the circle or square has gone out of bound
  // of the display
  for (int32_t x = min(sqr_x, cir_x - cir_r), y = min(sqr_y, cir_y - cir_r); 
    x > 0 && y > 0; x = min(sqr_x, cir_x - cir_r), y = min(sqr_y, cir_y - cir_r)) {
  // for (int32_t x = 10, y = 10; 
  //   x < 0 && sqr_y < 0; x -= 1, y -= 1) {
    
    // because we're using ints to draw the circle, we should always ceil
    // so that the circle drawn at least is over the square rather than being drawn below
    cir_r = (int32_t) ceil(((sqr_length * sqrt(2))/2));

    // draws a square
    tft.drawSmoothRoundRect(sqr_x, sqr_y, 1, 1, sqr_length, sqr_length,
      color_arr[color_ind % (sizeof(color_arr) / sizeof(int))]);

    // transition to the next color
    color_ind += 1;

    // This is drawing a circle without anti-aliasing.
    tft.drawCircle(cir_x, cir_y , cir_r, color_arr[color_ind % (sizeof(color_arr) / sizeof(int))]);

    // transition to the next color
    color_ind += 1;

    // again, since drawing squares and rectangles need ints, we can't have floating numbers
    // to represent the coordinates of the square. we take the ceil so that the square's top
    // left corner is definitely over the circle. 
    sqr_x -= ceil(cir_r - sqr_length/2);
    sqr_y -= ceil(cir_r - sqr_length/2);
    sqr_length = 2 * cir_r;
    
    // wait 500 seconds after drawing circle + rectangle
    delay(500);
  }
}
