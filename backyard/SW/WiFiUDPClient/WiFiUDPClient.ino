/*
 *  This sketch sends random data over UDP on a ESP32 device
 *
 */
#include <WiFi.h>
#include <WiFiUdp.h>
#include "NetworkCredentials.h"
#include "Motors.h"

// Commands for testing
const char * cmdFwd   = "W";
const char * cmdLeft  = "A";
const char * cmdBwd   = "S";
const char * cmdRight = "D";
const char * cmdStop  = "X";

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

// The class controlling the motors
Motors motors;

int loopCounter = 0;

void setup() {
  // Initilize hardware serial:
  Serial.begin(115200);
  
  // Connect to the WiFi network
  connectToWiFi(networkName, networkPswd);

  motors.setup();
}

void loop() {
  // only send data when connected
  if ((loopCounter % 8) == 0 && connected) {
    Serial.println("Sending a UDP packet...");
    
    // Send a packet
    udp.beginPacket(udpAddress, udpPort);
    //udp.printf("Seconds since boot: %lu", millis() / 1000);
    udp.printf("I am alive.");
    udp.endPacket();
  }

  // TEST: Receive from the network...
  uint8_t buffer[recvBufLen];
  memset(buffer, 0, recvBufLen);
  udp.parsePacket();

  if (udp.read(buffer, recvBufLen) > 0) {
    Serial.print("Server to client: ");
    Serial.println((char *)buffer);

    if (strcmp((char *)buffer, cmdFwd) == 0) {
      Serial.println(">> I was asked to move forwards!");
      motors.forwards();
    }
    else if (strcmp((char *)buffer, cmdBwd) == 0) {
      Serial.println(">> I was asked to move backwards!");
      motors.backwards();
    }
    else if (strcmp((char *)buffer, cmdStop) == 0) {
      Serial.println(">> I was asked to stop!");
      motors.stop();
    }
  }

  // Wait for 1 second
  delay(500);
  loopCounter++;  
}

void connectToWiFi(const char * ssid, const char * pwd) {
  Serial.println("Connecting to WiFi network: " + String(ssid));

  // delete old config
  WiFi.disconnect(true);

  //register event handler
  WiFi.onEvent(WiFiEvent);
  
  // Initiate connection
  WiFi.begin(ssid, pwd);

  // FIXME: Probably not needed!
  while(WiFi.status() != WL_CONNECTED){
    Serial.print(".");
    delay(100);
  }

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
