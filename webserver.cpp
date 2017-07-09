#include <stdint.h>
#include <ESP8266WebServer.h>
#include "FS.h"

class WebServer {
  private:
    ESP8266WebServer server = ESP8266WebServer(80);

  public:
    void start() {
      bool fs = SPIFFS.begin();
  
      server.serveStatic("/", SPIFFS, "/index.html");
      server.serveStatic("/", SPIFFS, "/");
    
      server.begin();
      Serial.println("HTTP server started");
    }

    void loop() {
      server.handleClient();
    }
};
