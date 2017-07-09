#include <stdint.h>
#include <ESP8266WiFi.h>
#include <ArduinoOTA.h>

class Network {
  const char* clientSsid = "niels-wifi";
  const char* clientPassword = "alphase42#omegalaxy43";
  
  const char* hostSsid = "macaw";
  const char* hostPassword = "lettherebelight";

  int localNetworkTries = 5;

  public:
    void goOnline() {
      WiFi.begin(clientSsid, clientPassword);
      
      Serial.printf("Attempting to connect to '%s'", clientSsid);
    
      ping(0);
    }

    void loop() {
      ArduinoOTA.handle();
    }

  private:
    void ping(int pings) {
      if(WiFi.status() == WL_CONNECTED) {
        connectionHandler();
      } else if(pings <= localNetworkTries) {
        Serial.print(".");
      
        delay(1000);
        ping(++pings);
      } else {
        hostHandler();
      }
    }

    void connectionHandler() {
      IPAddress ip = WiFi.localIP();
      Serial.printf("\nConnected to '%s', IP address is %u.%u.%u.%u.\n", clientSsid, ip[0], ip[1], ip[2], ip[3]);

      startOta();
    }

    void hostHandler() {
        Serial.printf("\n'%s' not found, setting up access point\n", clientSsid);
        
        WiFi.softAP(hostSsid, hostPassword);
        IPAddress ip = WiFi.softAPIP();
    
        Serial.printf("Set up access point '%s' with IP address %u.%u.%u.%u\n", hostSsid, ip[0], ip[1], ip[2], ip[3]);
    }

    void startOta() {
      ArduinoOTA.onStart([]() {
        Serial.println("Uploading sketch...");
      });
      
      ArduinoOTA.onProgress([](unsigned int progress, unsigned int total) {
        Serial.printf("Progress: %u%%\r", (progress / (total / 100)));
      });
      
      ArduinoOTA.onEnd([]() {
        Serial.println("Sketch uploaded");
      });

      ArduinoOTA.onError([](ota_error_t error) {
        Serial.printf("Error[%u]: ", error);
        if (error == OTA_AUTH_ERROR) Serial.println("Auth Failed");
        else if (error == OTA_BEGIN_ERROR) Serial.println("Begin Failed");
        else if (error == OTA_CONNECT_ERROR) Serial.println("Connect Failed");
        else if (error == OTA_RECEIVE_ERROR) Serial.println("Receive Failed");
        else if (error == OTA_END_ERROR) Serial.println("End Failed");
      });
  
      ArduinoOTA.begin();
      
      Serial.println("Listening for OTA updates");
    }
};
