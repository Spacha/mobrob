//#include <Ticker.h>
#include "WiFi.h"
#include "AsyncUDP.h"
#include "network_credentials.h"

// Pin assignments

#define BLINKER_PIN 27  // LED

#define LHALL_PIN 35    // Left track hall sensor
#define RHALL_PIN 34    // Right track hall sensor

#define UT_TRIG_PIN 4   // Ultrasonic sensor trigger
#define UT_ECHO_PIN 23  // Ultrasonic sensor echo

#define L1_PIN      25  // Left motor control 1
#define L2_PIN      13  // Left motor control 2
#define LEN_PIN     26  // Left motor enable
#define R1_PIN      32  // Right motor control 1
#define R2_PIN      12  // Right motor control 2
#define REN_PIN     33  // Right motor enable

// Buffers
#define MEAS_BUFSIZE 4  // Measurement buffer size
#define MSG_BUFSIZE 64  // Maximum length of an outgoing server message

// server address
IPAddress g_server_addr(192, 168, 1, 168);
uint16_t g_server_port = 3333;

// speed for both tracks
uint8_t g_speed = 180;

// controls whether the robot should take distance measurements
bool g_should_measure = false;

// map 4-bit values into various speed levels (in range 0 - 255)
uint8_t speed_map[16] = { 0, 0, 0, 130, 140, 150, 160, 170, 180, 190, 200, 210, 220, 230, 240, 250 };

AsyncUDP udp;

void setup()
{
  Serial.begin(115200);
  WiFi.mode(WIFI_STA);
  WiFi.begin(NETWORK_NAME, NETWORK_PASSWORD);
  if (WiFi.waitForConnectResult() != WL_CONNECTED) {
      Serial.println("WiFi Failed");
      while(1) {
          delay(1000);
      }
  }

  Serial.println("WiFi connected!");

  if(udp.connect(g_server_addr, g_server_port)) {
    Serial.println("UDP connected");
    //udp.print("Hello Server!");
    udp.onPacket([](AsyncUDPPacket packet) {
      // packet.data(), packet.length()

      //Serial.println("Packet received from server!");

      if (packet.length() == 0)
        return;

      // separate command key and value from the command byte
      uint8_t cmd_byte = packet.data()[0];
      uint8_t cmd_key = cmd_byte >> 4;
      uint8_t cmd_value = cmd_byte & 0b1111;

      // TODO: use handle table (interface?):
      // 0 => motorControl
      // 1 => speedControl
      // 2 => taskControl
      switch (cmd_key) {
        case 0:
          motorControl(cmd_value);
          break;
        case 1:
          speedControl(cmd_value);
          break;
        case 2:
          taskControl(cmd_value);
          break;
        default:
          break;
      }
    });

    // send a unicast message right after connecting
    udp.print("Hello Server!");
  }

  pinMode(BLINKER_PIN, OUTPUT);
  pinMode(LHALL_PIN, INPUT);
  pinMode(RHALL_PIN, INPUT);
  pinMode(UT_TRIG_PIN, OUTPUT);
  pinMode(UT_ECHO_PIN, INPUT);
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
  //digitalWrite(BLINKER_PIN, HIGH);
  //delay(1000);
  //digitalWrite(BLINKER_PIN, LOW);
  //delay(1000);

  //uint16_t left_hall = analogRead(LHALL_PIN);
  //uint16_t right_hall = analogRead(RHALL_PIN);
  //Serial.print("left: ");
  //Serial.print(left_hall);
  //Serial.print(", right: ");
  //Serial.print(right_hall);
  //Serial.println();
  //delay(100);

#if 0
#define TEMPBUF_SZ 10

  uint16_t meas_buffer[TEMPBUF_SZ];

  for (int i = 0; i < TEMPBUF_SZ; i++) {
    meas_buffer[i] = analogRead(LHALL_PIN);
    delay(100);
  }

  AsyncUDPMessage msg_buffer(MSG_BUFSIZE);
  msg_buffer.printf("R_HALL: ");

  for (int i = 0; i < MEAS_BUFSIZE; i++) {
    msg_buffer.printf("%d", meas_buffer[i]);
    if (i < MSG_BUFSIZE)
      msg_buffer.printf(", ");
  }

  udp.sendTo(msg_buffer, g_server_addr, g_server_port);
  msg_buffer.flush();
  delay(100);
#endif

#if 0
  // take a series of measurements if tasked to do so
  if (g_should_measure) {
    long meas_buffer[MEAS_BUFSIZE];

    for (int i = 0; i < MEAS_BUFSIZE; i++) {
      meas_buffer[i] = measureDistance();
      delay(100);
    }

    AsyncUDPMessage msg_buffer(MSG_BUFSIZE);
    msg_buffer.printf("Distance measurements: ");

    for (int i = 0; i < MEAS_BUFSIZE; i++) {
      msg_buffer.printf("%ld cm", meas_buffer[i]);
      if (i < MSG_BUFSIZE)
        msg_buffer.printf(", ");
    }

    udp.sendTo(msg_buffer, g_server_addr, g_server_port);
    msg_buffer.flush();
    delay(100);
  }
#endif
}

// TODO: Add a small stop delay when changing directions!
/**
 * Left track forward.
 */
void leftTrackFW()
{
  digitalWrite(L1_PIN, HIGH);
  digitalWrite(L2_PIN, LOW);
  analogWrite(LEN_PIN, g_speed);
}

/**
 * Left track backward.
 */
void leftTrackBW()
{
  digitalWrite(L1_PIN, LOW);
  digitalWrite(L2_PIN, HIGH);
  analogWrite(LEN_PIN, g_speed);
}

/**
 * Left track stop.
 */
void leftTrackStop()
{
  digitalWrite(L1_PIN, LOW);
  digitalWrite(L2_PIN, LOW);
  analogWrite(LEN_PIN, 0);
}

/**
 * Right track forward.
 */
void rightTrackFW()
{
  digitalWrite(R1_PIN, HIGH);
  digitalWrite(R2_PIN, LOW);
  analogWrite(REN_PIN, g_speed);
}

/**
 * Right track backward.
 */
void rightTrackBW()
{
  digitalWrite(R1_PIN, LOW);
  digitalWrite(R2_PIN, HIGH);
  analogWrite(REN_PIN, g_speed);
}

/**
 * Right track stop.
 */
void rightTrackStop()
{
  digitalWrite(R1_PIN, LOW);
  digitalWrite(R2_PIN, LOW);
  analogWrite(REN_PIN, 0);
}

/**
 * Motor control.
 */
void motorControl(uint8_t cmd_byte)
{
  if (cmd_byte >= 16)
    return;

  //Serial.print("C> left track: ");
  switch ((cmd_byte & 0b1100) >> 2) {
    case 1:
      //Serial.print("forward");
      leftTrackFW();
      break;
    case 2:
      //Serial.print("backward");
      leftTrackBW();
      break;
    case 3:
      //Serial.print("stop");
      leftTrackStop();
      break;
    default:
      //Serial.print("[none]");
      break;
  }

  //Serial.print(", right track: ");
  switch ((cmd_byte & 0b0011) >> 0) {
    case 1:
      //Serial.print("forward");
      rightTrackFW();
      break;
    case 2:
      //Serial.print("backward");
      rightTrackBW();
      break;
    case 3:
      //Serial.print("stop");
      rightTrackStop();
      break;
    default:
      //Serial.print("[none]");
      break;
  }

    //Serial.println();
}

/**
 * Speed control.
 */
void speedControl(uint8_t speed_byte)
{
  if (speed_byte >= 16)
    return;

  g_speed = speed_map[speed_byte];
  //Serial.print("C> speed set to: ");
  //Serial.println(g_speed);
}

/**
 * Task control.
 */
void taskControl(uint8_t task_byte)
{
  if (task_byte >= 16)
    return;

  g_should_measure = task_byte == 1;
  //Serial.print("C> measurement control set to: ");
  //Serial.println(g_should_measure ? 'active' : 'inactive');
}

//void sendMessage(std::string message)
//{
//  AsyncUDPMessage msg_buffer(MSG_BUFSIZE);
//
//  msg_buffer.printf("Counter value: %d", counter);
//  udp.sendTo(msg_buffer, g_server_addr, g_server_port);
//}

/**
 * Measure distance
 * @return distance in centimeters
 */
long measureDistance()
{
  long duration;

  digitalWrite(UT_TRIG_PIN, LOW);
  delayMicroseconds(2);
  digitalWrite(UT_TRIG_PIN, HIGH);
  delayMicroseconds(10);
  digitalWrite(UT_TRIG_PIN, LOW);

  duration = pulseIn(UT_ECHO_PIN, HIGH);

  return microsecondsToCentimeters(duration);
}

/**
 * Microseconds to centimeters.
 */
long microsecondsToCentimeters(long microseconds) {
  return microseconds / 29 / 2;
}
