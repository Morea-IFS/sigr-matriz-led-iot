#include <Adafruit_GFX.h>
#include <Adafruit_NeoMatrix.h>
#include <Adafruit_NeoPixel.h>

#define PIN D5
#define BRIGHTNESS 96
#define mw 16
#define mh 32

Adafruit_NeoMatrix *matrix = new Adafruit_NeoMatrix(mw, mh, PIN,
    NEO_MATRIX_TOP + NEO_MATRIX_LEFT +
    NEO_MATRIX_ROWS + NEO_MATRIX_ZIGZAG,
    NEO_GRB + NEO_KHZ800);


struct Pixel {
  uint8_t row;
  uint8_t col;
  uint32_t originalColor;
  uint32_t invertedColor;
};

uint32_t hexToColor(const char* hex) {
  uint32_t color = strtol(hex, NULL, 16);
  return ((color & 0xFF0000) >> 8) | ((color & 0x00FF00) << 8) | (color & 0x0000FF);
}


const Pixel pattern[] = {
  {1,0,hexToColor("0000FF"),hexToColor("FFFFFF")}, {1,1,hexToColor("0000FF"),hexToColor("FFFFFF")}, {1,2,hexToColor("0000FF"),hexToColor("FFFFFF")}, {1,3,hexToColor("0000FF"),hexToColor("FFFFFF")}, {1,4,hexToColor("0000FF"),hexToColor("FFFFFF")},
  {2,0,hexToColor("0000FF"),hexToColor("FFFFFF")}, {4,0,hexToColor("0000FF"),hexToColor("FFFFFF")}, {4,1,hexToColor("0000FF"),hexToColor("FFFFFF")}, {4,2,hexToColor("0000FF"),hexToColor("FFFFFF")}, {4,3,hexToColor("0000FF"),hexToColor("FFFFFF")},
  {4,4,hexToColor("0000FF"),hexToColor("FFFFFF")}, {5,11,hexToColor("0000FF"),hexToColor("FFFFFF")}, {5,12,hexToColor("0000FF"),hexToColor("FFFFFF")}, {5,13,hexToColor("0000FF"),hexToColor("FFFFFF")}, {5,14,hexToColor("0000FF"),hexToColor("FFFFFF")},
  {5,15,hexToColor("0000FF"),hexToColor("FFFFFF")}, {6,0,hexToColor("0000FF"),hexToColor("FFFFFF")}, {6,1,hexToColor("0000FF"),hexToColor("FFFFFF")}, {6,2,hexToColor("0000FF"),hexToColor("FFFFFF")}, {6,3,hexToColor("0000FF"),hexToColor("FFFFFF")},
  {6,4,hexToColor("0000FF"),hexToColor("FFFFFF")}, {6,6,hexToColor("FFFFFF"),hexToColor("0000FF")}, {6,7,hexToColor("FFFFFF"),hexToColor("0000FF")}, {6,9,hexToColor("FFFFFF"),hexToColor("0000FF")}, {6,11,hexToColor("0000FF"),hexToColor("FFFFFF")},
  {6,13,hexToColor("0000FF"),hexToColor("FFFFFF")}, {6,14,hexToColor("0000FF"),hexToColor("FFFFFF")}, {7,2,hexToColor("0000FF"),hexToColor("FFFFFF")}, {7,5,hexToColor("FFFFFF"),hexToColor("0000FF")}, {7,7,hexToColor("FFFFFF"),hexToColor("0000FF")},
  {7,9,hexToColor("FFFFFF"),hexToColor("0000FF")}, {7,11,hexToColor("0000FF"),hexToColor("FFFFFF")}, {7,12,hexToColor("0000FF"),hexToColor("FFFFFF")}, {7,13,hexToColor("0000FF"),hexToColor("FFFFFF")}, {7,15,hexToColor("0000FF"),hexToColor("FFFFFF")},
  {8,3,hexToColor("0000FF"),hexToColor("FFFFFF")}, {8,5,hexToColor("FFFFFF"),hexToColor("0000FF")}, {8,7,hexToColor("FFFFFF"),hexToColor("0000FF")}, {8,8,hexToColor("FFFFFF"),hexToColor("0000FF")}, {9,0,hexToColor("0000FF"),hexToColor("FFFFFF")},
  {9,1,hexToColor("0000FF"),hexToColor("FFFFFF")}, {9,2,hexToColor("0000FF"),hexToColor("FFFFFF")}, {9,3,hexToColor("0000FF"),hexToColor("FFFFFF")}, {9,4,hexToColor("0000FF"),hexToColor("FFFFFF")}, {9,11,hexToColor("0000FF"),hexToColor("FFFFFF")},
  {9,12,hexToColor("0000FF"),hexToColor("FFFFFF")}, {9,13,hexToColor("0000FF"),hexToColor("FFFFFF")}, {9,14,hexToColor("0000FF"),hexToColor("FFFFFF")}, {9,15,hexToColor("0000FF"),hexToColor("FFFFFF")}, {10,5,hexToColor("FFFFFF"),hexToColor("0000FF")},
  {10,6,hexToColor("FFFFFF"),hexToColor("0000FF")}, {10,7,hexToColor("FFFFFF"),hexToColor("0000FF")}, {10,8,hexToColor("FFFFFF"),hexToColor("0000FF")}, {10,9,hexToColor("FFFFFF"),hexToColor("0000FF")}, {10,11,hexToColor("0000FF"),hexToColor("FFFFFF")},
  {10,13,hexToColor("0000FF"),hexToColor("FFFFFF")}, {10,15,hexToColor("0000FF"),hexToColor("FFFFFF")}, {11,0,hexToColor("0000FF"),hexToColor("FFFFFF")}, {11,1,hexToColor("0000FF"),hexToColor("FFFFFF")}, {11,2,hexToColor("0000FF"),hexToColor("FFFFFF")},
  {11,3,hexToColor("0000FF"),hexToColor("FFFFFF")}, {11,4,hexToColor("0000FF"),hexToColor("FFFFFF")}, {11,5,hexToColor("FFFFFF"),hexToColor("0000FF")}, {11,7,hexToColor("FFFFFF"),hexToColor("0000FF")}, {11,9,hexToColor("FFFFFF"),hexToColor("0000FF")},
  {12,2,hexToColor("0000FF"),hexToColor("FFFFFF")}, {12,11,hexToColor("0000FF"),hexToColor("FFFFFF")}, {12,12,hexToColor("0000FF"),hexToColor("FFFFFF")}, {12,13,hexToColor("0000FF"),hexToColor("FFFFFF")}, {12,14,hexToColor("0000FF"),hexToColor("FFFFFF")},
  {12,15,hexToColor("0000FF"),hexToColor("FFFFFF")}, {13,0,hexToColor("0000FF"),hexToColor("FFFFFF")}, {13,1,hexToColor("0000FF"),hexToColor("FFFFFF")}, {13,2,hexToColor("0000FF"),hexToColor("FFFFFF")}, {13,3,hexToColor("0000FF"),hexToColor("FFFFFF")},
  {13,4,hexToColor("0000FF"),hexToColor("FFFFFF")}, {13,5,hexToColor("FFFFFF"),hexToColor("0000FF")}, {13,6,hexToColor("FFFFFF"),hexToColor("0000FF")}, {13,7,hexToColor("FFFFFF"),hexToColor("0000FF")}, {13,8,hexToColor("FFFFFF"),hexToColor("0000FF")},
  {13,9,hexToColor("FFFFFF"),hexToColor("0000FF")}, {13,11,hexToColor("0000FF"),hexToColor("FFFFFF")}, {13,15,hexToColor("0000FF"),hexToColor("FFFFFF")}, {14,5,hexToColor("FFFFFF"),hexToColor("0000FF")}, {14,7,hexToColor("FFFFFF"),hexToColor("0000FF")},
  {14,8,hexToColor("FFFFFF"),hexToColor("0000FF")}, {14,12,hexToColor("0000FF"),hexToColor("FFFFFF")}, {14,13,hexToColor("0000FF"),hexToColor("FFFFFF")}, {14,14,hexToColor("0000FF"),hexToColor("FFFFFF")}, {15,1,hexToColor("0000FF"),hexToColor("FFFFFF")},
  {15,2,hexToColor("0000FF"),hexToColor("FFFFFF")}, {15,3,hexToColor("0000FF"),hexToColor("FFFFFF")}, {15,4,hexToColor("0000FF"),hexToColor("FFFFFF")}, {15,5,hexToColor("FFFFFF"),hexToColor("0000FF")}, {15,6,hexToColor("FFFFFF"),hexToColor("0000FF")},
  {15,7,hexToColor("FFFFFF"),hexToColor("0000FF")}, {15,9,hexToColor("FFFFFF"),hexToColor("0000FF")}, {16,0,hexToColor("0000FF"),hexToColor("FFFFFF")}, {16,2,hexToColor("0000FF"),hexToColor("FFFFFF")}, {16,11,hexToColor("0000FF"),hexToColor("FFFFFF")},
  {16,12,hexToColor("0000FF"),hexToColor("FFFFFF")}, {16,13,hexToColor("0000FF"),hexToColor("FFFFFF")}, {16,14,hexToColor("0000FF"),hexToColor("FFFFFF")}, {16,15,hexToColor("0000FF"),hexToColor("FFFFFF")}, {17,1,hexToColor("0000FF"),hexToColor("FFFFFF")},
  {17,2,hexToColor("0000FF"),hexToColor("FFFFFF")}, {17,3,hexToColor("0000FF"),hexToColor("FFFFFF")}, {17,4,hexToColor("0000FF"),hexToColor("FFFFFF")}, {17,11,hexToColor("0000FF"),hexToColor("FFFFFF")}, {17,13,hexToColor("0000FF"),hexToColor("FFFFFF")},
  {17,15,hexToColor("0000FF"),hexToColor("FFFFFF")}, {18,5,hexToColor("FFFFFF"),hexToColor("0000FF")}, {18,6,hexToColor("FFFFFF"),hexToColor("0000FF")}, {18,7,hexToColor("FFFFFF"),hexToColor("0000FF")}, {18,8,hexToColor("FFFFFF"),hexToColor("0000FF")},
  {18,9,hexToColor("FFFFFF"),hexToColor("0000FF")}, {19,5,hexToColor("FFFFFF"),hexToColor("0000FF")}, {19,9,hexToColor("FFFFFF"),hexToColor("0000FF")}, {19,12,hexToColor("0000FF"),hexToColor("FFFFFF")}, {19,13,hexToColor("0000FF"),hexToColor("FFFFFF")},
  {19,15,hexToColor("0000FF"),hexToColor("FFFFFF")}, {20,0,hexToColor("0000FF"),hexToColor("FFFFFF")}, {20,1,hexToColor("0000FF"),hexToColor("FFFFFF")}, {20,2,hexToColor("0000FF"),hexToColor("FFFFFF")}, {20,3,hexToColor("0000FF"),hexToColor("FFFFFF")},
  {20,4,hexToColor("0000FF"),hexToColor("FFFFFF")}, {20,5,hexToColor("FFFFFF"),hexToColor("0000FF")}, {20,9,hexToColor("FFFFFF"),hexToColor("0000FF")}, {20,11,hexToColor("0000FF"),hexToColor("FFFFFF")}, {20,13,hexToColor("0000FF"),hexToColor("FFFFFF")},
  {20,15,hexToColor("0000FF"),hexToColor("FFFFFF")}, {21,0,hexToColor("0000FF"),hexToColor("FFFFFF")}, {21,2,hexToColor("0000FF"),hexToColor("FFFFFF")}, {21,4,hexToColor("0000FF"),hexToColor("FFFFFF")}, {21,6,hexToColor("FFFFFF"),hexToColor("0000FF")},
  {21,7,hexToColor("FFFFFF"),hexToColor("0000FF")}, {21,8,hexToColor("FFFFFF"),hexToColor("0000FF")}, {21,11,hexToColor("0000FF"),hexToColor("FFFFFF")}, {21,13,hexToColor("0000FF"),hexToColor("FFFFFF")}, {21,14,hexToColor("0000FF"),hexToColor("FFFFFF")},
  {22,0,hexToColor("0000FF"),hexToColor("FFFFFF")}, {22,3,hexToColor("0000FF"),hexToColor("FFFFFF")}, {22,4,hexToColor("0000FF"),hexToColor("FFFFFF")}, {23,0,hexToColor("0000FF"),hexToColor("FFFFFF")}, {23,1,hexToColor("0000FF"),hexToColor("FFFFFF")},
  {23,2,hexToColor("0000FF"),hexToColor("FFFFFF")}, {23,3,hexToColor("0000FF"),hexToColor("FFFFFF")}, {23,4,hexToColor("0000FF"),hexToColor("FFFFFF")}, {23,5,hexToColor("FFFFFF"),hexToColor("0000FF")}, {23,6,hexToColor("FFFFFF"),hexToColor("0000FF")},
  {23,7,hexToColor("FFFFFF"),hexToColor("0000FF")}, {23,8,hexToColor("FFFFFF"),hexToColor("0000FF")}, {23,9,hexToColor("FFFFFF"),hexToColor("0000FF")}, {24,5,hexToColor("FFFFFF"),hexToColor("0000FF")}, {24,7,hexToColor("FFFFFF"),hexToColor("0000FF")},
  {24,9,hexToColor("FFFFFF"),hexToColor("0000FF")}, {24,12,hexToColor("FFFFFF"),hexToColor("0000FF")}, {24,14,hexToColor("FFFFFF"),hexToColor("0000FF")}, {25,0,hexToColor("0000FF"),hexToColor("FFFFFF")}, {25,1,hexToColor("0000FF"),hexToColor("FFFFFF")},
  {25,2,hexToColor("0000FF"),hexToColor("FFFFFF")}, {25,3,hexToColor("0000FF"),hexToColor("FFFFFF")}, {25,4,hexToColor("0000FF"),hexToColor("FFFFFF")}, {25,5,hexToColor("FFFFFF"),hexToColor("0000FF")}, {25,7,hexToColor("FFFFFF"),hexToColor("0000FF")},
  {25,9,hexToColor("FFFFFF"),hexToColor("0000FF")}, {26,4,hexToColor("0000FF"),hexToColor("FFFFFF")}, {26,11,hexToColor("FFFFFF"),hexToColor("0000FF")}, {26,15,hexToColor("FFFFFF"),hexToColor("0000FF")}, {27,0,hexToColor("0000FF"),hexToColor("FFFFFF")},
  {27,1,hexToColor("0000FF"),hexToColor("FFFFFF")}, {27,2,hexToColor("0000FF"),hexToColor("FFFFFF")}, {27,3,hexToColor("0000FF"),hexToColor("FFFFFF")}, {27,4,hexToColor("0000FF"),hexToColor("FFFFFF")}, {27,12,hexToColor("FFFFFF"),hexToColor("0000FF")},
  {27,13,hexToColor("FFFFFF"),hexToColor("0000FF")}, {27,14,hexToColor("FFFFFF"),hexToColor("0000FF")}, {29,0,hexToColor("0000FF"),hexToColor("FFFFFF")}, {29,1,hexToColor("0000FF"),hexToColor("FFFFFF")}, {29,2,hexToColor("0000FF"),hexToColor("FFFFFF")},
  {29,3,hexToColor("0000FF"),hexToColor("FFFFFF")}, {29,4,hexToColor("0000FF"),hexToColor("FFFFFF")}, {30,0,hexToColor("0000FF"),hexToColor("FFFFFF")}, {30,2,hexToColor("0000FF"),hexToColor("FFFFFF")}, {30,4,hexToColor("0000FF"),hexToColor("FFFFFF")},
  {31,0,hexToColor("0000FF"),hexToColor("FFFFFF")}, {31,2,hexToColor("0000FF"),hexToColor("FFFFFF")}, {31,4,hexToColor("0000FF"),hexToColor("FFFFFF")}, {0,0,hexToColor("0000FF"),hexToColor("FFFFFF")}
};

const int patternSize = sizeof(pattern) / sizeof(pattern[0]);
bool inverted = false;
unsigned long transitionStart;
const unsigned long transitionDuration = 2000; 


void setup() {
  Serial.begin(115200);
  
  matrix->begin();
  matrix->setTextWrap(false);
  matrix->setBrightness(BRIGHTNESS);
  matrix->clear();
  
  Serial.print("Pattern size: ");
  Serial.println(patternSize);
}

void loop() {
  unsigned long currentTime = millis();
  
 
  if (currentTime % 4000 < 50) { 
    transitionStart = currentTime;
    inverted = !inverted;
  }
  
  matrix->clear();
  
  
  float progress = 0.0;
  if (currentTime - transitionStart < transitionDuration) {
    progress = (float)(currentTime - transitionStart) / transitionDuration;
  } else {
    progress = 1.0;
  }
  
  for (int i = 0; i < patternSize; i++) {
    Pixel p = pattern[i];
    uint32_t startColor = inverted ? p.invertedColor : p.originalColor;
    uint32_t endColor = inverted ? p.originalColor : p.invertedColor;
    
    uint8_t startR = (startColor >> 16) & 0xFF;
    uint8_t startG = (startColor >> 8) & 0xFF;
    uint8_t startB = startColor & 0xFF;
    
    uint8_t endR = (endColor >> 16) & 0xFF;
    uint8_t endG = (endColor >> 8) & 0xFF;
    uint8_t endB = endColor & 0xFF;
    
    uint8_t currentR = startR + (endR - startR) * progress;
    uint8_t currentG = startG + (endG - startG) * progress;
    uint8_t currentB = startB + (endB - startB) * progress;
    
    uint32_t currentColor = (currentR << 16) | (currentG << 8) | currentB;
    
    matrix->drawPixel(p.col, p.row, currentColor);
  }
  
  matrix->show();
  delay(20); 


}