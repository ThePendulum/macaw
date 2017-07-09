#include <stdint.h>
#include <WebSocketsServer.h>

class SocketServer {
  WebSocketsServer socket = WebSocketsServer(81);
  
  public:
    void start() {
      // socket.onEvent(this.handleEvent);
      
      socket.begin();
      Serial.println("WebSocket server started");  
    };

    void loop() {
      socket.loop();
    }

  private:
    void handleEvent(uint8_t num, WStype_t type, uint8_t * payload, size_t length) {
      switch(type) {
        case WStype_DISCONNECTED: {
          Serial.printf("[%u] Disconnected!\n", num); break;
        }
        case WStype_CONNECTED: {
          IPAddress ip = socket.remoteIP(num);
          
          Serial.printf("[%u] Connected from %d.%d.%d.%d url: %s\n", num, ip[0], ip[1], ip[2], ip[3], payload);
        }
      }
    };
};
