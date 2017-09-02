#include <EEPROM.h>
#include <FastLED.h>
#include "funcs.h"

class Leds {
  #define DATA_PIN 5
  #define NUM_LEDS 150
  
  int wait = 1000;
  int lastBeat = 0;
  
  CRGB leds[NUM_LEDS];

  int hue = 0;
  int hueMode = 0;
  float hueSpeed = 0.0;
  
  int saturation = 255;
  int saturationMode = 0;
  float saturationSpeed = 0.01;
  
  int value = 255;
  int valueMode = 0;
  float valueSpeed = 0.01;

  int (*hueFunc)(int, int, int, float, int) = hueMono;
  int (*valueFunc)(int, int, float, int) = valueMono;
  int (*saturationFunc)(int, int, float, int) = saturationMono;

  int hueFuncResult;
  int valueFuncResult;
  int saturationFuncResult;

  public:
    void init(int beat) {
      FastLED.addLeds<WS2811, DATA_PIN>(leds, NUM_LEDS);

      hue = EEPROM.read(0);
      hueSpeed = EEPROM.read(2) / 100.0;
      
      saturation = EEPROM.read(3);
      saturationSpeed = EEPROM.read(5) / 100.0;
      
      value = EEPROM.read(6);
      valueSpeed = EEPROM.read(8) / 100.0;

      // Use methods to allow associated function to be set
      setHueMode(EEPROM.read(1));
      setSaturationMode(EEPROM.read(4));
      setValueMode(EEPROM.read(7));

      render(beat, millis());
    }

    void render(int beat, int now) {
      for(int index = 0; index < NUM_LEDS; index++) {
        hueFuncResult = hueFunc(hueFuncResult, beat, index, hueSpeed, hue);
        
        leds[index] = CHSV(hueFuncResult, saturationFunc(beat, index, saturationSpeed, saturation), valueFunc(beat, index, valueSpeed, value));
      }

      FastLED.show();
      
      if(now - lastBeat > wait) {
        lastBeat = now;
        
        EEPROM.commit();
      }
    }

    void setHue(int newHue) {
      hue = newHue;

      EEPROM.write(0, hue);
    }

    int getHue() {
      return hue;
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
          hueFunc = hueHexad; break;
        }
        case 3: {
          hueFunc = hueTriad; break;
        }
        case 4: {
          for(int index = 0; index < NUM_LEDS; index++) {
            leds[index].red = random(0, 255);
          }
      
          hueFunc = hueRandom; break;
        }
      }

      EEPROM.write(1, hueMode);
    }

    int getHueMode() {
      return hueMode;
    }
    
    void setHueSpeed(float newHueSpeed) {
      hueSpeed = newHueSpeed;

      EEPROM.write(2, hueSpeed * 100);
    }

    float getHueSpeed() {
      return hueSpeed;
    }

    void setSaturation(int newSaturation) {
      saturation = newSaturation;

      EEPROM.write(3, saturation);
    }

    int getSaturation() {
      return saturation;
    }
    
    void setSaturationMode(int newSaturationMode) {
      saturationMode = newSaturationMode;
      
      switch(saturationMode) {
        case 0: {
          saturationFunc = saturationMono; break;
        }
        case 1: {
          saturationFunc = saturationChase; break;
        }
      }

      EEPROM.write(4, saturationMode);
    }

    int getSaturationMode() {
      return saturationMode;
    }
    
    void setSaturationSpeed(float newSaturationSpeed) {
      saturationSpeed = newSaturationSpeed;

      EEPROM.write(5, saturationSpeed * 100);
    }

    float getSaturationSpeed() {
      return saturationSpeed;
    }

    void setValue(int newValue) {
      value = newValue;

      EEPROM.write(6, value);
    }

    int getValue() {
      return value;
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

      EEPROM.write(7, valueMode);
    }

    int getValueMode() {
      return valueMode;
    }
    
    void setValueSpeed(float newValueSpeed) {
      valueSpeed = newValueSpeed;

      EEPROM.write(8, valueSpeed * 100);
    }

    float getValueSpeed() {
      return valueSpeed;
    }
};
