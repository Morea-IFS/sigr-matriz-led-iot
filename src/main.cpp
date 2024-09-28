
#include <Adafruit_GFX.h>
#include <Adafruit_NeoMatrix.h>
#include <Adafruit_NeoPixel.h>


// Which pin on the Arduino is connected to the NeoPixels?
#define PIN 5

// Max is 255, 32 is a conservative value to not overload
// a USB power supply (500mA) for 12x12 pixels.
#define BRIGHTNESS 96

// Define matrix width and height.
#define mw 16
#define mh 16

#define LED_BLACK    0

int counter = 0;
int bilderanzahl = 0;

// When we setup the NeoPixel library, we tell it how many pixels, and which pin to use to send signals.
// Note that for older NeoPixel strips you might need to change the third parameter--see the strandtest
// example for more information on possible values.
Adafruit_NeoMatrix *matrix = new Adafruit_NeoMatrix(mw, mh, PIN,
    NEO_MATRIX_TOP     + NEO_MATRIX_LEFT +
    NEO_MATRIX_ROWS + NEO_MATRIX_ZIGZAG,
    NEO_GRB            + NEO_KHZ800);
    
static const uint16_t PROGMEM
// These bitmaps were written for a backend that only supported
// 4 bits per color with Blue/Green/Red ordering while neomatrix
// uses native 565 color mapping as RGB.
// I'm leaving the arrays as is because it's easier to read
// which color is what when separated on a 4bit boundary
// The demo code will modify the arrays at runtime to be compatible
// with the neomatrix color ordering and bit depth.


RGB_bmp[][256] = {
{
	0x0000, 0x0000, 0x0000, 0x0000, 0xc140, 0xf9c0, 0xf9c0, 0xf9c0, 0xf9c0, 0xf9c0, 0xb900, 0x8900, 0x9120, 0x0000, 0x0000, 0x0000, 
	0x0000, 0x0000, 0x0000, 0x7100, 0xf9c0, 0xf9c0, 0xf9c0, 0xf9c0, 0xf9c0, 0xf9c0, 0xf9c0, 0xf9c0, 0xf9a0, 0x0000, 0x0000, 0x0000, 
	0x0000, 0x0000, 0x0000, 0x8aa0, 0xabe0, 0xabe0, 0xb400, 0xfd08, 0xfd08, 0xb400, 0xfd08, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 
	0x0000, 0x0000, 0x5220, 0xb400, 0xfd08, 0xb400, 0xfd08, 0xfd08, 0xfd08, 0xbc01, 0xfd08, 0xfd08, 0xfd08, 0xbba6, 0x0000, 0x0000, 
	0x0000, 0x0000, 0x5220, 0xb400, 0xf4e7, 0xb400, 0xbc01, 0xfd08, 0xfd08, 0xf4e7, 0xb400, 0xfd08, 0xfd08, 0xfd08, 0x0000, 0x0000, 
	0x0000, 0x0000, 0x5220, 0xabe0, 0xb400, 0xfd08, 0xfd08, 0xfd08, 0xfd08, 0xabe0, 0xabe0, 0xabe0, 0xabe0, 0x0000, 0x0000, 0x0000, 
	0x0000, 0x0000, 0x0000, 0x0000, 0xbc42, 0xfd08, 0xfd08, 0xfd08, 0xfd08, 0xfd08, 0xfd08, 0xfd08, 0x0000, 0x0000, 0x0000, 0x0000, 
	0x0000, 0x0000, 0x0000, 0x8b20, 0xabe0, 0xb3c0, 0xf1e0, 0xabe0, 0xabe0, 0xb3c0, 0xcc42, 0xcc44, 0x9362, 0x0000, 0x0000, 0x0000, 
	0x0000, 0x0000, 0x8b20, 0xabe0, 0xabe0, 0xb3c0, 0xf1e0, 0xb3c0, 0xb3a0, 0xf1e0, 0xabe0, 0xabe0, 0xabe0, 0x8b20, 0x0000, 0x0000, 
	0x0000, 0x0000, 0xabe0, 0xabe0, 0xabe0, 0xb3c0, 0xf9c0, 0xf9c0, 0xf9c0, 0xf1e0, 0xabe0, 0xabe0, 0xabe0, 0xabe0, 0x0000, 0x0000, 
	0x0000, 0x0000, 0xfd08, 0xfd08, 0xb3c0, 0xf9e0, 0xfce8, 0xf9c0, 0xf9e0, 0xfce8, 0xf1e0, 0xb400, 0xfd08, 0xfd08, 0x0000, 0x0000, 
	0x0000, 0x0000, 0xfd08, 0xfd08, 0xfca7, 0xf9c0, 0xf9c0, 0xf9c0, 0xf9c0, 0xf9c0, 0xf9e0, 0xfce8, 0xfd08, 0xfd08, 0x0000, 0x0000, 
	0x0000, 0x0000, 0xfd08, 0xfcc8, 0xf9c0, 0xf9c0, 0xf9c0, 0xf9a0, 0xf9c0, 0xf9c0, 0xf9c0, 0xf9e0, 0xfd08, 0xfd08, 0x0000, 0x0000, 
	0x0000, 0x0000, 0x0000, 0xcb22, 0xf9c0, 0xf9c0, 0xf9a0, 0x0000, 0xa900, 0xf9c0, 0xf9c0, 0xf9c0, 0x0000, 0x0000, 0x0000, 0x0000, 
	0x0000, 0x0000, 0x8b20, 0xabe0, 0xabe0, 0xabe0, 0x0000, 0x0000, 0x0000, 0x9a20, 0xabe0, 0xabe0, 0xabe0, 0x0000, 0x0000, 0x0000, 
	0x0000, 0x0000, 0xabe0, 0xabe0, 0xabe0, 0xabe0, 0x0000, 0x0000, 0x0000, 0x5220, 0xabe0, 0xabe0, 0xabe0, 0xabe0, 0x0000, 0x0000
}
};

// Convert a BGR 4/4/4 bitmap to RGB 5/6/5 used by Adafruit_GFX
void fixdrawRGBBitmap(int16_t x, int16_t y, const uint16_t *bitmap, int16_t w, int16_t h) {
  uint16_t RGB_bmp_fixed[w * h];
  for (uint16_t pixel = 0; pixel < w * h; pixel++) {
    uint8_t r, g, b;
    uint16_t color = pgm_read_word(bitmap + pixel);

    //Serial.print(color, HEX);
    b = (color & 0xF00) >> 8;
    g = (color & 0x0F0) >> 4;
    r = color & 0x00F;
    //Serial.print(" ");
    //Serial.print(b);
    //Serial.print("/");
    //Serial.print(g);
    //Serial.print("/");
    //Serial.print(r);
    //Serial.print(" -> ");
    // expand from 4/4/4 bits per color to 5/6/5
    b = map(b, 0, 15, 0, 31);
    g = map(g, 0, 15, 0, 63);
    r = map(r, 0, 15, 0, 31);
    //Serial.print(r);
    //Serial.print("/");
    //Serial.print(g);
    //Serial.print("/");
    //Serial.print(b);
    RGB_bmp_fixed[pixel] = (r << 11) + (g << 5) + b;
   // Serial.print(" -> ");
    //Serial.print(pixel);
    //Serial.print(" -> ");
    //Serial.println(RGB_bmp_fixed[pixel], HEX);
  }
  matrix->drawRGBBitmap(x, y, RGB_bmp_fixed, w, h);
}

void display_rgbBitmap(uint8_t bmp_num) {
  static uint16_t bmx, bmy;

  matrix->drawRGBBitmap(bmx, bmy, RGB_bmp[bmp_num], 16, 16);
  bmx += 16;
  if (bmx >= mw) bmx = 0;
  if (!bmx) bmy += 16;
  if (bmy >= mh) bmy = 0;
  matrix->show();
}



void setup() {
  Serial.begin(115200);

  matrix->begin();
  matrix->setTextWrap(false);
  matrix->setBrightness(BRIGHTNESS);
  // Test full bright of all LEDs. If brightness is too high
  // for your current limit (i.e. USB), decrease it.
  //matrix->fillScreen(LED_WHITE_HIGH);
  //matrix->show();
  //delay(1000);
  matrix->clear();
  bilderanzahl=(sizeof(RGB_bmp) / sizeof(RGB_bmp[0]));
  Serial.print("Anzahl Bilder: ");
  Serial.println(bilderanzahl);
}



void loop() {

  // clear the screen after X bitmaps have been displayed and we
  // loop back to the top left corner
  // 8x8 => 1, 16x8 => 2, 17x9 => 6
  static uint8_t pixmap_count = ((mw + 15) / 8) * ((mh + 15) / 8);
  // Cycle through red, green, blue, display 2 checkered patterns
  // useful to debug some screen types and alignment.

  Serial.print("Screen pixmap capacity: ");
  Serial.println(pixmap_count);

  display_rgbBitmap(counter++);
  delay(500);

  if (counter >=bilderanzahl){
    counter = 0;
  }

  Serial.println ("----------------------------------------------------------------");
  //delay(1000);
}
