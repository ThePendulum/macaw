#include <stdint.h>
#include <WebSocketsServer.h>
#include <ArduinoJson.h>

class SocketServer {
  WebSocketsServer socket = WebSocketsServer(81);
  
  public:
    void start(Leds *leds) {
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
    void handleEvent(uint8_t num, WStype_t type, uint8_t * payload, size_t payloadLength, Leds *leds) {
      IPAddress ip = socket.remoteIP(num);
      StaticJsonBuffer<200> jsonBuffer;
      
      switch(type) {
        case WStype_DISCONNECTED: {
          Serial.printf("#%u disconnected\n", num, ip[0], ip[1], ip[2], ip[3]);
          
          break;
        }
        case WStype_CONNECTED: {
          Serial.printf("%d.%d.%d.%d (#%u) connected\n", ip[0], ip[1], ip[2], ip[3], num);

          break;
        }
        case WStype_TEXT: {
          JsonObject& root = jsonBuffer.parseObject(payload);

          if(root.success()) {
            this->setValues(leds, root);
          } else {
            Serial.println("JSON parse failed");
          }

          break;
        }
      }
    };
    
    void setValues(Leds *leds, JsonObject& root) {
      if(root.containsKey("hue")) {
          leds->setHue(root["hue"]);
      }
      
      if(root.containsKey("hueMode")) {
          leds->setHueMode(root["hueMode"]);
      }
      
      if(root.containsKey("hueSpeed")) {
          leds->setHueSpeed(root["hueSpeed"]);
      }
      
      if(root.containsKey("saturation")) {
          leds->setSaturation(root["saturation"]);
      }
      
      if(root.containsKey("saturationmode")) {
          leds->setSaturationMode(root["saturationMode"]);
      }
      
      if(root.containsKey("saturationSpeed")) {
          leds->setSaturationSpeed(root["saturationSpeed"]);
      }
      
      if(root.containsKey("value")) {
          leds->setValue(root["value"]);
      }
      
      if(root.containsKey("valueMode")) {
          leds->setValueMode(root["valueMode"]);
      }
      
      if(root.containsKey("valueSpeed")) {
          leds->setValueSpeed(root["valueSpeed"]);
      }
    };
};
