#include <FastLED.h>

class Leds {
  #define DATA_PIN 5
  #define NUM_LEDS 150
  
  CRGB leds[NUM_LEDS];

  int hue = 0;
  int saturation = 255;
  int value = 255;

  public:
    void init() {
      FastLED.addLeds<WS2811, DATA_PIN>(leds, NUM_LEDS);
    }

    void render(int beat) {
      FastLED.showColor(CHSV(beat % 255, saturation, value));
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
};
