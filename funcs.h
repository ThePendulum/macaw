int mono(int beat, int index, int hue) {
  return hue;
}

int cycle(int beat, int index, int hue) {
  return beat + hue;
}

int rainbow(int beat, int index, int hue) {
  return beat + index + hue;
}

int spectrum(int beat, int index, int hue) {
  return index * 42.5 + hue;
}
