#include <stdint.h>
#include <WebSocketsServer.h>
#include <ArduinoJson.h>

class SocketServer {
  WebSocketsServer socket = WebSocketsServer(81);
  
  public:
    void start(Leds leds) {
      socket.begin();
      socket.onEvent([this, leds](uint8_t num, WStype_t type, uint8_t * payload, size_t payloadLength) {
        this->handleEvent(num, type, payload, payloadLength, leds);  
      });
      
      Serial.println("WebSocket server started");  
    };

    void loop() {
      socket.loop();
    }

  private:
    void handleEvent(uint8_t num, WStype_t type, uint8_t * payload, size_t payloadLength, Leds leds) {
      StaticJsonBuffer<200> jsonBuffer;
      
      switch(type) {
        case WStype_DISCONNECTED: {
          Serial.printf("[%u] Disconnected!\n", num); break;
        }
        case WStype_CONNECTED: {
          IPAddress ip = socket.remoteIP(num);
          
          Serial.printf("[%u] Connected from %d.%d.%d.%d url: %s\n", num, ip[0], ip[1], ip[2], ip[3], payload);

          break;
        }
        case WStype_TEXT: {
          JsonObject& root = jsonBuffer.parseObject(payload);

          if(root.success()) {
            int hue = root["hue"];
            leds.setHue(hue);
            
            Serial.println(hue);
          } else {
            Serial.println("JSON parse failed");
          }

          break;
        }
      }
    };
};
