/*
 *  This sketch sends random data over UDP on a ESP32 device
 *
 */
#include <WiFi.h>
#include <WiFiUdp.h>
#include "NetworkCredentials.h"

const int recvBufLen = 64;

// WiFi network name and password:
const char * networkName = NETWORK_NAME;
const char * networkPswd = NETWORK_PASSWORD;

// IP address to send UDP data to:
//  either use the ip address of the server or 
//  a network broadcast address
const char * udpAddress = "192.168.1.154";
const int udpPort = 3333;

// Are we currently connected?
boolean connected = false;

// The udp library class
WiFiUDP udp;

void setup() {
  // Initilize hardware serial:
  Serial.begin(115200);
  
  // Connect to the WiFi network
  connectToWiFi(networkName, networkPswd);
}

void loop() {
  // only send data when connected
  if (connected) {
    Serial.println("Sending a UDP packet...");
    
    // Send a packet
    udp.beginPacket(udpAddress, udpPort);
    udp.printf("Seconds since boot: %lu", millis() / 1000);
    udp.endPacket();
  }

  // TEST: Receive from the network...
  uint8_t buffer[recvBufLen] ;
  memset(buffer, 0, recvBufLen);
  udp.parsePacket();

  if (udp.read(buffer, recvBufLen) > 0) {
    Serial.print("Server to client: ");
    Serial.println((char *)buffer);
  }

  // Wait for 1 second
  delay(1000);
}

void connectToWiFi(const char * ssid, const char * pwd) {
  Serial.println("Connecting to WiFi network: " + String(ssid));

  // delete old config
  WiFi.disconnect(true);
  //register event handler
  WiFi.onEvent(WiFiEvent);
  
  // Initiate connection
  WiFi.begin(ssid, pwd);

  Serial.println("Waiting for WIFI connection...");
}

// wifi event handler
void WiFiEvent(WiFiEvent_t event) {
    switch(event) {
      case ARDUINO_EVENT_WIFI_STA_GOT_IP:
          // When connected set 
          Serial.print("WiFi connected! IP address: ");
          Serial.println(WiFi.localIP());

          // initializes the UDP state
          // This initializes the transfer buffer
          udp.begin(WiFi.localIP(), udpPort);
          connected = true;
          break;

      case ARDUINO_EVENT_WIFI_STA_DISCONNECTED:
          Serial.println("WiFi lost connection");
          connected = false;
          break;

      default: break;
    }
}
