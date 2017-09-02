#include <stdint.h>
#include <WebSocketsServer.h>
#include <ArduinoJson.h>

class SocketServer {
  WebSocketsServer socket = WebSocketsServer(81);
  int wait = 500;
  int lastBeat = 0;
  
  public:
    void start(Leds *leds) {
      socket.begin();
      socket.onEvent([this, leds](uint8_t num, WStype_t type, uint8_t * payload, size_t payloadLength) {
        this->handleEvent(num, type, payload, payloadLength, leds);  
      });
      
      Serial.println("WebSocket server started");
    };

    void loop(Leds *leds, uint32_t now) {
      socket.loop();

      /*
      if(now - lastBeat > wait) {
        lastBeat = now;
        
        sendValues(leds);
      }
      */
    }

  private:
    void handleEvent(uint8_t num, WStype_t type, uint8_t * payload, size_t payloadLength, Leds *leds) {
      IPAddress ip = socket.remoteIP(num);
      
      switch(type) {
        case WStype_DISCONNECTED: {
          Serial.printf("#%u disconnected\n", num, ip[0], ip[1], ip[2], ip[3]);
          
          break;
        }
        case WStype_CONNECTED: {
          Serial.printf("%d.%d.%d.%d (#%u) connected\n", ip[0], ip[1], ip[2], ip[3], num);

          sendValues(leds);

          break;
        }
        case WStype_TEXT: {
          StaticJsonBuffer<100> jsonBuffer;
          JsonObject& root = jsonBuffer.parseObject(payload);

          if(root.success()) {
            this->setValues(leds, root);
          } else {
            Serial.println("JSON parse failed");
          }

          break;
        }
      }

      Serial.println(type);
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
      
      if(root.containsKey("saturationMode")) {
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

    void sendValues(Leds *leds) {
      StaticJsonBuffer<250> jsonBuffer;
      JsonObject& init = jsonBuffer.createObject();
      
      JsonObject& hue = init.createNestedObject("hue");
      JsonObject& saturation = init.createNestedObject("saturation");
      JsonObject& value = init.createNestedObject("value");

      hue["value"] = leds->getHue();
      hue["mode"] = leds->getHueMode();
      hue["speed"] =  leds->getHueSpeed();

      saturation["value"] = leds->getSaturation();
      saturation["mode"] = leds->getSaturationMode();
      saturation["speed"] =  leds->getSaturationSpeed();

      value["value"] = leds->getValue();
      value["mode"] = leds->getValueMode();
      value["speed"] =  leds->getValueSpeed();

      char buffer[200];

      init.printTo(buffer, sizeof(buffer));

      socket.broadcastTXT(buffer);
    }
};
