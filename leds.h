#include <FastLED.h>
#include "funcs.h"

class Leds {
  #define DATA_PIN 5
  #define NUM_LEDS 150
  
  CRGB leds[NUM_LEDS];

  int hueMode = 0;

  int hue = 0;
  int saturation = 255;
  int value = 255;

  int (*hueFunc)(int, int, int) = mono;

  public:
    void init() {
      FastLED.addLeds<WS2811, DATA_PIN>(leds, NUM_LEDS);
    }

    void render(int beat) {
      for(int index = 0; index < NUM_LEDS; index++) {
        leds[index] = CHSV(hueFunc(beat, index, hue), saturation, value);
      }

      FastLED.show();
    }

    void setHue(int newHue) {
      hue = newHue;
    }

    void setSaturation(int newSaturation) {
      saturation = newSaturation;
    }

    void setValue(int newValue) {
      value = newValue;
    }
    
    int setHueMode(int newHueMode) {
      hueMode = newHueMode;
      
      switch(newHueMode) {
        case 0: {
          hueFunc = mono; break;
        }
        case 1: {
          hueFunc = cycle; break;
        }
        case 2: {
          hueFunc = rainbow; break;
        }
        case 3: {
          hueFunc = spectrum; break;
        }
      }
    }
};
