#include "WiFi.h"
#include "AsyncUDP.h"

#define BLINKER_PIN 32
#define LF_PIN      13
#define LB_PIN      26
#define RF_PIN      12
#define RB_PIN      25

const char * ssid = "";
const char * password = "";

AsyncUDP udp;

void setup()
{
    Serial.begin(115200);
    WiFi.mode(WIFI_STA);
    WiFi.begin(ssid, password);
    if (WiFi.waitForConnectResult() != WL_CONNECTED) {
        Serial.println("WiFi Failed");
        while(1) {
            delay(1000);
        }
    }

    Serial.println("WiFi connected!");
    
    if(udp.connect(IPAddress(192,168,1,168), 3333)) {
        Serial.println("UDP connected");
        //udp.print("Hello Server!");
        udp.onPacket([](AsyncUDPPacket packet) {
          // packet.data(), packet.length()

          Serial.println("Packet received from server!");

          // Packet (1 byte): 0b[left track, 2 bits][right track, 2 bits]
          // 01 (1) -> forward, 10 (2) -> backward, 11 (3) -> stop
          if (packet.length() == 0)
            return;

          uint8_t cmd_byte = packet.data()[0];
                        
          Serial.print("Command: Left track: ");
          switch ((cmd_byte & 0b1100) >> 2) {
            case 1:
              Serial.print("forward");
              digitalWrite(LF_PIN, HIGH);
              digitalWrite(LB_PIN, LOW);
              break;
            case 2:
              Serial.print("backward");
              digitalWrite(LF_PIN, LOW);
              digitalWrite(LB_PIN, HIGH);
              break;
            case 3:
              Serial.print("stop");
              digitalWrite(LF_PIN, LOW);
              digitalWrite(LB_PIN, LOW);
              break;
            default:
              Serial.print("[none]");
              break;
          }

          Serial.print(", right track: ");
          switch ((cmd_byte & 0b0011) >> 0) {
            case 1:
              Serial.print("forward");
              digitalWrite(RF_PIN, HIGH);
              digitalWrite(RB_PIN, LOW);
              break;
            case 2:
              Serial.print("backward");
              digitalWrite(RF_PIN, LOW);
              digitalWrite(RB_PIN, HIGH);
              break;
            case 3:
              Serial.print("stop");
              digitalWrite(RF_PIN, LOW);
              digitalWrite(RB_PIN, LOW);
              break;
            default:
              Serial.print("[none]");
              break;
          }

          Serial.println();
        });

        // Send unicast right after connecting
        udp.print("Hello Server!");
    }

    pinMode(BLINKER_PIN, OUTPUT);
    pinMode(LF_PIN, OUTPUT);
    pinMode(LB_PIN, OUTPUT);
    pinMode(RF_PIN, OUTPUT);
    pinMode(RB_PIN, OUTPUT);
}

void loop()
{
  digitalWrite(BLINKER_PIN, HIGH);
  delay(1000);
  digitalWrite(BLINKER_PIN, LOW);
  delay(1000);
}
