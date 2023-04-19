#include "WiFi.h"
#include "AsyncUDP.h"

#define BLINKER_PIN 27
#define L1_PIN      25
#define L2_PIN      13
#define LEN_PIN     26
#define R1_PIN      32
#define R2_PIN      12
#define REN_PIN     33

#define MSPEED      180 // 0..255

const char * ssid = "";
const char * password = "";

AsyncUDP udp;

// TODO: Add a small stop delay when changing directions!
void leftTrackFW()
{
  digitalWrite(L1_PIN, HIGH);
  digitalWrite(L2_PIN, LOW);
  analogWrite(LEN_PIN, MSPEED);
}

void leftTrackBW()
{
  digitalWrite(L1_PIN, LOW);
  digitalWrite(L2_PIN, HIGH);
  analogWrite(LEN_PIN, MSPEED);
}

void leftTrackStop()
{
  digitalWrite(L1_PIN, LOW);
  digitalWrite(L2_PIN, LOW);
  analogWrite(LEN_PIN, 0);
}

void rightTrackFW()
{
  digitalWrite(R1_PIN, HIGH);
  digitalWrite(R2_PIN, LOW);
  analogWrite(REN_PIN, MSPEED);
}

void rightTrackBW()
{
  digitalWrite(R1_PIN, LOW);
  digitalWrite(R2_PIN, HIGH);
  analogWrite(REN_PIN, MSPEED);
}

void rightTrackStop()
{
  digitalWrite(R1_PIN, LOW);
  digitalWrite(R2_PIN, LOW);
  analogWrite(REN_PIN, 0);
}

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
              leftTrackFW();
              break;
            case 2:
              Serial.print("backward");
              leftTrackBW();
              break;
            case 3:
              Serial.print("stop");
              leftTrackStop();
              break;
            default:
              Serial.print("[none]");
              break;
          }

          Serial.print(", right track: ");
          switch ((cmd_byte & 0b0011) >> 0) {
            case 1:
              Serial.print("forward");
              rightTrackFW();
              break;
            case 2:
              Serial.print("backward");
              rightTrackBW();
              break;
            case 3:
              Serial.print("stop");
              rightTrackStop();
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
    pinMode(L1_PIN, OUTPUT);
    pinMode(L2_PIN, OUTPUT);
    pinMode(LEN_PIN, OUTPUT);
    pinMode(R1_PIN, OUTPUT);
    pinMode(R2_PIN, OUTPUT);
    pinMode(REN_PIN, OUTPUT);
}

void loop()
{
  digitalWrite(BLINKER_PIN, HIGH);
  delay(1000);
  digitalWrite(BLINKER_PIN, LOW);
  delay(1000);
}
