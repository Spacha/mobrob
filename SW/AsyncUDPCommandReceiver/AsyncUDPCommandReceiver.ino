#include "WiFi.h"
#include "AsyncUDP.h"

// pin assignments
#define BLINKER_PIN 27
#define L1_PIN      25
#define L2_PIN      13
#define LEN_PIN     26
#define R1_PIN      32
#define R2_PIN      12
#define REN_PIN     33

// speed for both tracks
uint8_t g_speed = 180;

// map 4-bit values into various speed levels (in range 0 - 255)
uint8_t speed_map[16] = { 0, 0, 0, 130, 140, 150, 160, 170, 180, 190, 200, 210, 220, 230, 240, 250 };

// WiFi network credentials
const char * ssid = "";
const char * password = "";

AsyncUDP udp;

// TODO: Add a small stop delay when changing directions!
void leftTrackFW()
{
  digitalWrite(L1_PIN, HIGH);
  digitalWrite(L2_PIN, LOW);
  analogWrite(LEN_PIN, g_speed);
}

void leftTrackBW()
{
  digitalWrite(L1_PIN, LOW);
  digitalWrite(L2_PIN, HIGH);
  analogWrite(LEN_PIN, g_speed);
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
  analogWrite(REN_PIN, g_speed);
}

void rightTrackBW()
{
  digitalWrite(R1_PIN, LOW);
  digitalWrite(R2_PIN, HIGH);
  analogWrite(REN_PIN, g_speed);
}

void rightTrackStop()
{
  digitalWrite(R1_PIN, LOW);
  digitalWrite(R2_PIN, LOW);
  analogWrite(REN_PIN, 0);
}

void motorControl(uint8_t cmd_byte)
{
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
}

void speedControl(uint8_t speed_byte)
{
  if (speed_byte < 16) {
    g_speed = speed_map[speed_byte];
    Serial.print("speed set to: ");
    Serial.println(g_speed);
  }
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

        if (packet.length() == 0)
          return;

        // separate command key and value from the command byte
        uint8_t cmd_byte = packet.data()[0];
        uint8_t cmd_key = cmd_byte >> 4;
        uint8_t cmd_value = cmd_byte & 0b1111;

        // TODO: use handle table (interface?):
        // 0 => motorControl
        // 1 => speedControl
        switch (cmd_key) {
          case 0:
            motorControl(cmd_value);
            break;
          case 1:
            speedControl(cmd_value);
            break;
          default:
            break;
        }
      });

      // send a unicast message right after connecting
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
  // TODO: Blink LED asynchronously
  digitalWrite(BLINKER_PIN, HIGH);
  delay(1000);
  digitalWrite(BLINKER_PIN, LOW);
  delay(1000);
}
