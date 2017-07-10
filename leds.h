#include <FastLED.h>
#include "funcs.h"

class Leds {
  #define DATA_PIN 5
  #define NUM_LEDS 150
  
  CRGB leds[NUM_LEDS];

  int hue = 0;
  int hueMode = 0;
  float hueSpeed = 0.0;
  
  int saturation = 255;
  int saturationMode = 0;
  float saturationSpeed = 0.1;
  
  int value = 255;
  int valueMode = 0;
  float valueSpeed = 0.1;

  int (*hueFunc)(int, int, float, int) = hueMono;
  int (*valueFunc)(int, int, float, int) = valueMono;
  int (*saturationFunc)(int, int, float, int) = saturationMono;

  public:
    void init() {
      FastLED.addLeds<WS2811, DATA_PIN>(leds, NUM_LEDS);
    }

    void render(int beat) {
      for(int index = 0; index < NUM_LEDS; index++) {
        leds[index] = CHSV(hueFunc(beat, index, hueSpeed, hue), saturationFunc(beat, index, saturationSpeed, saturation), valueFunc(beat, index, valueSpeed, value));
      }

      FastLED.show();
    }

    void setHue(int newHue) {
      hue = newHue;
    }
    
    void setHueMode(int newHueMode) {
      hueMode = newHueMode;
      
      switch(hueMode) {
        case 0: {
          hueFunc = hueMono; break;
        }
        case 1: {
          hueFunc = hueRainbow; break;
        }
        case 2: {
          hueFunc = hueSpectrum; break;
        }
      }
    }
    
    void setHueSpeed(float newHueSpeed) {
      hueSpeed = newHueSpeed;
    }

    void setSaturation(int newSaturation) {
      saturation = newSaturation;
    }
    
    void setSaturationMode(int newSaturationMode) {
      saturationMode = newSaturationMode;
      
      switch(saturationMode) {
        case 0: {
          saturationFunc = saturationMono; break;
        }
      }
    }
    
    void setSaturationSpeed(float newSaturationSpeed) {
      saturationSpeed = newSaturationSpeed;
    }

    void setValue(int newValue) {
      value = newValue;
    }
    
    void setValueMode(int newValueMode) {
      valueMode = newValueMode;
      
      switch(valueMode) {
        case 0: {
          valueFunc = valueMono; break;
        }
        case 1: {
          valueFunc = valueChase; break;
        }
        case 2: {
          valueFunc = valueBlink; break;
        }
        case 3: {
          valueFunc = valueStrobe; break;
        }
      }
    }
    
    void setValueSpeed(float newValueSpeed) {
      valueSpeed = newValueSpeed;
    }
};
