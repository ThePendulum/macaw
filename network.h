#include <stdint.h>
#include <EEPROM.h>
#include <ESP8266WiFi.h>
#include <DNSServer.h>
#include <ArduinoOTA.h>

class Network {
  DNSServer dns;

  const char* clientSsid = "niels-wifi";
  const char* clientPassword = "alphase42#omegalaxy43";
  
  const char* hostSsid = "macaw2";
  const char* hostPassword = "lettherebelight";

  int localNetworkTries = 5;

  public:
    void goOnline() {
      WiFi.begin(clientSsid, clientPassword);
      
      Serial.printf("Attempting to connect to '%s'", clientSsid);
    
      ping(0);
    }

    void loop() {
      dns.processNextRequest();
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
        WiFi.disconnect();
        hostHandler();
      }
    }

    void connectionHandler() {
      IPAddress ip = WiFi.localIP();
      Serial.printf("\nConnected to '%s', IP address is %u.%u.%u.%u.\n", clientSsid, ip[0], ip[1], ip[2], ip[3]);
    }

    void hostHandler() {
        Serial.printf("\n'%s' not found, setting up access point\n", clientSsid);
        
        WiFi.softAP(hostSsid, hostPassword);
        IPAddress ip = WiFi.softAPIP();

        dns.start(53, "*", ip);
    
        Serial.printf("Set up access point '%s' with IP address %u.%u.%u.%u\n", hostSsid, ip[0], ip[1], ip[2], ip[3]);
    }
};
