#include "leds.h"
#include "network.h"
#include "webserver.h"
#include "socketserver.h"

Leds leds;
WebServer webServer;
SocketServer socketServer;
Network network;

int fps = 60;
int wait = 1000 / fps;
int beat = 0;

uint32_t lastBeat = millis();

void setup() {
  Serial.begin(115200);
  Serial.println("Initializing Macaw");

  leds.init();

  network.goOnline();

  webServer.start();
  socketServer.start(&leds);
}

void loop() {
  network.loop();
  webServer.loop();
  socketServer.loop();

  uint32_t now = millis();

  if(now - lastBeat > wait) {
    lastBeat = now;
    
    leds.render(beat++);
  }
}
