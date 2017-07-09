#include <FastLED.h>

#include "network.cpp"
#include "webserver.cpp"
#include "socketserver.cpp"

#define DATA_PIN 5
#define NUM_LEDS 150

WebServer webServer;
SocketServer socketServer;
Network network;

CRGB leds[NUM_LEDS];

int incoming;

void setup() {
  Serial.begin(115200);
  Serial.println("Initializing Macaw");

  // LEDs
  FastLED.addLeds<WS2811, DATA_PIN>(leds, NUM_LEDS);
  FastLED.showColor(CHSV(120, 255, 255));

  network.goOnline();

  webServer.start();
  socketServer.start();
}

void loop() {
  webServer.loop();
  socketServer.loop();

  if (Serial.available() > 0) {
    incoming = Serial.parseInt();
    Serial.println(incoming);
    
    FastLED.showColor(CHSV((incoming * 255) / 360, 255, 255));
  }
}
