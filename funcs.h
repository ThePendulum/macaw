#include <math.h>

int hueMono(int beat, int index, float pace, int hue) {
  return pace * beat + hue;
}

int hueRainbow(int beat, int index, float pace, int hue) {
  return pace * beat + index + hue;
}

int hueSpectrum(int beat, int index, float pace, int hue) {
  return pace * beat + index * 42.5 + hue;
}

int saturationMono(int beat, int index, float pace, int saturation) {
  return saturation;
}

int valueMono(int beat, int index, float pace, int value) {
  return value;
}

int valueChase(int beat, int index, float pace, int value) {
  return (.5 + .5 * sin(index + pace * beat)) * value;
}

int valueBlink(int beat, int index, float pace, int value) {
  return round(pace * beat) % 2 ? 0 : value;
}

int valueStrobe(int beat, int index, float pace, int value) {
  return round(pace * beat) % 5 ? 0 : value;
}