// "C:\\Users\\miika\\AppData\\Local\\Arduino15\\packages\\esp32\\tools\\xtensa-esp32-elf-gcc\\esp-2021r2-patch5-8.4.0/bin/xtensa-esp32-elf-objdump" -d BasicMultiThreading.ino.elf >> BasicMultiThreading.ino.asm

#include <Arduino.h>  // millis
#include "WiFi.h"
#include "AsyncUDP.h"
//#include "network_credentials.h"
/////////////////////////////////////////////
// Fill in your credentials here...
#define NETWORK_NAME     ""
#define NETWORK_PASSWORD ""
/////////////////////////////////////////////

//#include "driving.h"

#if CONFIG_FREERTOS_UNICORE
#define ARDUINO_RUNNING_CORE 0
#else
#define ARDUINO_RUNNING_CORE 1
#endif

// Pin assignments

#ifndef LED_BUILTIN
#define LED_BUILTIN 14
#endif

#define LHALL_PIN 39  // Left track hall sensor
#define RHALL_PIN 36  // Right track hall sensor

#define UT_TRIG_PIN 4   // Ultrasonic sensor trigger
#define UT_ECHO_PIN 23  // Ultrasonic sensor echo

#define L1_PIN 25   // Left motor control 1
#define L2_PIN 13   // Left motor control 2
#define LEN_PIN 26  // Left motor enable
#define R1_PIN 32   // Right motor control 1
#define R2_PIN 12   // Right motor control 2
#define REN_PIN 33  // Right motor enable

#define WIFI_POLL_MS          10000
#define WIFI_TIMEOUT_MS       20000
#define WIFI_RECOVER_TIME_MS  30000

#define HALL_POLL_MS          1
#define SEND_DATA_MS          1000
#define BLINK_CONNECTING_MS   250
#define BLINK_CONNECTED_MS    1000

// speed for both tracks
uint8_t g_speed = 180;

// map 4-bit values into various speed levels (in range 0 - 255)
uint8_t speed_map[16] = { 0, 0, 0, 130, 140, 150, 160, 170, 180, 190, 200, 210, 220, 230, 240, 250 };

// UDP setup
IPAddress g_server_addr(192, 168, 1, 168);
uint16_t g_server_port = 3333;
AsyncUDP udp;
bool udp_connected = false;

int leftTrackDir  = 1;
int rightTrackDir = 1;

#define NUM_MEASUREMENTS 8192
uint16_t measurements[NUM_MEASUREMENTS] = {0};
int measurements_idx = 0;
//uint32_t data_buffer[64] = {0};
//int data_buffer_idx = 0;
int lcycle_delta = 0;
int rcycle_delta = 0;

// task definitions
void TaskBlink(void *params);
void TaskReadHallSensors(void *params);
void TaskKeepWifiAlive(void *params);
void TaskSendData(void *params);

TaskHandle_t analog_read_task_handle;

void setup() {
  Serial.begin(115200);

  //uint32_t blink_delay = 1000;
  xTaskCreate(
    TaskBlink,
    "Blink",               // Task name
    2048,                  // Stack size (bytes)
    NULL, //(void *)&blink_delay,  // Parameter
    5,                     // Task priority
    NULL                   // Task handle
  );

  xTaskCreatePinnedToCore(
    TaskReadHallSensors,
    "ReadHallSensors",         // Task name
    2048,                      // Stack size (bytes)
    NULL,                      // Parameter
    1,                         // Task priority
    &analog_read_task_handle,  // Task handle
    ARDUINO_RUNNING_CORE);

  xTaskCreatePinnedToCore(
    TaskKeepWiFiAlive,
    "KeepWiFiAlive",  // Task name
    5000,             // Stack size (bytes)
    NULL,             // Parameter
    2,                // Task priority
    NULL,             // Task handle
    ARDUINO_RUNNING_CORE);

  xTaskCreatePinnedToCore(
    TaskSendData,
    "TaskSendData",   // Task name
    5000,             // Stack size (bytes)
    NULL,             // Parameter
    2,                // Task priority
    NULL,             // Task handle
    ARDUINO_RUNNING_CORE);

  pinMode(UT_TRIG_PIN, OUTPUT);
  pinMode(UT_ECHO_PIN, INPUT);
  pinMode(L1_PIN, OUTPUT);
  pinMode(L2_PIN, OUTPUT);
  pinMode(LEN_PIN, OUTPUT);
  pinMode(R1_PIN, OUTPUT);
  pinMode(R2_PIN, OUTPUT);
  pinMode(REN_PIN, OUTPUT);

  //analogWrite(LEN_PIN, 0);
  //analogWrite(REN_PIN, 0);

  Serial.println("Initialized.");
}

void loop() {
  //if (analog_read_task_handle != NULL) {
  //  delay(120000);
  //  vTaskDelete(analog_read_task_handle);
  //  analog_read_task_handle = NULL;
  //}
}

/*--------------------------------------------------*/
/*---------------------- Tasks ---------------------*/
/*--------------------------------------------------*/

/**
 * Task: Blink LED repeatedly.
 *
 * TODO: Indicate the connection status by adjusting the period
 * and/or using an RGB LED.
 */
void TaskBlink(void *params) {
  //uint32_t blink_delay = *((uint32_t *)params);
  (void)params;

  pinMode(LED_BUILTIN, OUTPUT);

  for (;;) {
    digitalWrite(LED_BUILTIN, HIGH);
    if (udp_connected)
      delay(BLINK_CONNECTED_MS);
    else
      delay(BLINK_CONNECTING_MS);

    digitalWrite(LED_BUILTIN, LOW);
    if (udp_connected)
      delay(BLINK_CONNECTED_MS);
    else
      delay(BLINK_CONNECTING_MS);
  }
}

/**
 * Task: Read hall sensors.
 */
void TaskReadHallSensors(void *params) {
  (void)params;

  //if (!adcAttachPin(LHALL_PIN) || !adcAttachPin(RHALL_PIN)) {
  //  Serial.printf("TaskReadHallSensors cannot work because the given pin %d or %d cannot be used for ADC - the task will delete itself.\n", LHALL_PIN, RHALL_PIN);
  //  analog_read_task_handle = NULL;
  //  vTaskDelete(NULL);
  //}

#define HALL_UPPER 3300 // 4050
#define HALL_LOWER 2600 // 3800

#if 0
  int pin = LHALL_PIN;
  for (;;) {
    int a = analogRead(pin);
    if (a >= HALL_UPPER) {
      Serial.print(" UP ");
    } else if (a <= HALL_LOWER) {
      Serial.print("DOWN");
    } else {
      Serial.print("    ");
    }

    delay(1);

    if (pin == LHALL_PIN) {
      pin = RHALL_PIN;
      Serial.print(" ");
    } else {
      pin = LHALL_PIN;
      Serial.println("\n");
      delay(90);
    }
#endif

  int lup_cnt = 0;
  int ldown_cnt = 0;
  delay(100);
  bool lis_up = analogRead(LHALL_PIN) >= HALL_UPPER;

  int rup_cnt = 0;
  int rdown_cnt = 0;
  delay(100);
  bool ris_up = analogRead(RHALL_PIN) >= HALL_UPPER;

  // TODO: Use convolution (https://youtu.be/oeyW9x7r2Xw)

  for (;;) {
    delay(1);
    int lHallValue = analogRead(LHALL_PIN);

    if (lis_up) {
      if (lHallValue <= HALL_LOWER) {
        ldown_cnt++;
        if (ldown_cnt >= 3) {
          lis_up = false;
          ldown_cnt = 0;
          lcycle_delta += leftTrackDir;
        }
      }
    } else {
      if (lHallValue >= HALL_UPPER) {
        lup_cnt++;
        if (lup_cnt >= 3) {
          lis_up = true;
          lup_cnt = 0;
          lcycle_delta += leftTrackDir;
        }
      }
    }

    delay(1);
    int rHallValue = analogRead(RHALL_PIN);

    if (ris_up) {
      if (rHallValue <= HALL_LOWER) {
        rdown_cnt++;
        if (rdown_cnt >= 3) {
          ris_up = false;
          rdown_cnt = 0;
          rcycle_delta += rightTrackDir;
        }
      }
    } else {
      if (rHallValue >= HALL_UPPER) {
        rup_cnt++;
        if (rup_cnt >= 3) {
          ris_up = true;
          rup_cnt = 0;
          rcycle_delta += rightTrackDir;
        }
      }
    }

#if 0
    //measurements[measurements_idx++] = rHallValue;
    measurements[measurements_idx++] = lHallValue;

    if (measurements_idx >= NUM_MEASUREMENTS) {
      for (int i = 0; i < NUM_MEASUREMENTS; i++) {
        Serial.println(measurements[i]);
        measurements[i] = 0;
      }
      measurements_idx = 0;
    }
#endif

#if 0
  bool isDown = analogRead(RHALL_PIN) <= HALL_LOWER;

  int measurementIdx = 0;

  for (;;) {
    int rHallValue = analogRead(RHALL_PIN);

    if (measurementIdx >= NUM_MEASUREMENTS) {
      Serial.println("Batch:");
      Serial.println(0);
      Serial.println(0);
      for (int i = 0; i < NUM_MEASUREMENTS; i++) {
        Serial.println(measurements[i]);
        measurements[i] = 0;
      }
      measurementIdx = 0;
    }

    measurements[measurementIdx] = (uint16_t)rHallValue;
    measurementIdx += 1;
#endif

#if 0
    if (lHallValue <= HALL_LOWER) {
      if (!isDown) {
        Serial.println("Cycle!");
      }
      isDown = true;
    } else if (lHallValue >= HALL_UPPER) {
      if (isDown) {}
      isDown = false;
    }
#endif
    //int rHallValue = analogRead(RHALL_PIN);
    //Serial.println(lHallValue);
    //Serial.println(rHallValue);
    // TODO: Enable this?
    //vTaskDelay(HALL_POLL_MS / portTICK_PERIOD_MS);
  }
}

/**
 * Task: monitor the WiFi connection and keep it alive!
 * 
 * When a WiFi connection is established, this task will check it every 10 seconds 
 * to make sure it's still alive.
 * 
 * If not, a reconnect is attempted. If this fails to finish within the timeout,
 * the ESP32 will wait for it to recover and try again.
 */
void TaskKeepWiFiAlive(void *params) {
  (void)params;

  for (;;) {
    // check WiFi status regularly
    if (WiFi.status() == WL_CONNECTED) {
      vTaskDelay(WIFI_POLL_MS / portTICK_PERIOD_MS);
      continue;
    }

    Serial.println("[WIFI] Connecting...");
    WiFi.mode(WIFI_STA);
    WiFi.begin(NETWORK_NAME, NETWORK_PASSWORD);

    unsigned long startAttemptTime = millis();

    // keep looping while we're not connected and haven't reached the timeout
    while (WiFi.status() != WL_CONNECTED && (millis() - startAttemptTime) < WIFI_TIMEOUT_MS) {}

    // when we couldn't make a WiFi connection (or the timeout expired),
    // sleep for a while and then retry
    if (WiFi.status() != WL_CONNECTED) {
      Serial.println("[WIFI] FAILED");
      vTaskDelay(WIFI_RECOVER_TIME_MS / portTICK_PERIOD_MS);
      continue;
    }

    Serial.print("[WIFI] Connected: ");
    Serial.println(WiFi.localIP());

    // connect to the server using UDP
    if (udp.connect(g_server_addr, g_server_port)) {
      Serial.println("UDP connected");
      udp_connected = true;

      // register receive callback when server sends a packet
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
  }
}

/**
 * Task: Send messages in the buffer.
 */
void TaskSendData(void *params) {
  (void)params;

  char msgbuf[16] = {0};

  for (;;) {
    if (udp_connected) {
      sprintf(msgbuf, "TD: (%d, %d)", lcycle_delta, rcycle_delta);
      udp.print(msgbuf);
      lcycle_delta = 0;
      rcycle_delta = 0;
    }

    vTaskDelay(SEND_DATA_MS / portTICK_PERIOD_MS);
  }
}






// TODO: Add a small stop delay when changing directions!
/**
 * Left track forward.
 */
void leftTrackFW() {
  leftTrackDir = 1;
  digitalWrite(L1_PIN, HIGH);
  digitalWrite(L2_PIN, LOW);
  analogWrite(LEN_PIN, g_speed - 22); // FIXME: Calibration
}

/**
 * Left track backward.
 */
void leftTrackBW() {
  leftTrackDir = -1;
  digitalWrite(L1_PIN, LOW);
  digitalWrite(L2_PIN, HIGH);
  analogWrite(LEN_PIN, g_speed - 22); // FIXME: Calibration
}

/**
 * Left track stop.
 */
void leftTrackStop() {
  digitalWrite(L1_PIN, LOW);
  digitalWrite(L2_PIN, LOW);
  analogWrite(LEN_PIN, 0);
}

/**
 * Right track forward.
 */
void rightTrackFW() {
  rightTrackDir = 1;
  digitalWrite(R1_PIN, HIGH);
  digitalWrite(R2_PIN, LOW);
  analogWrite(REN_PIN, g_speed);
}

/**
 * Right track backward.
 */
void rightTrackBW() {
  rightTrackDir = -1;
  digitalWrite(R1_PIN, LOW);
  digitalWrite(R2_PIN, HIGH);
  analogWrite(REN_PIN, g_speed);
}

/**
 * Right track stop.
 */
void rightTrackStop() {
  digitalWrite(R1_PIN, LOW);
  digitalWrite(R2_PIN, LOW);
  analogWrite(REN_PIN, 0);
}

/**
 * Motor control.
 */
void motorControl(uint8_t cmd_byte) {
  if (cmd_byte >= 16)
    return;

  Serial.print("C> left track: ");
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

/**
 * Speed control.
 */
void speedControl(uint8_t speed_byte) {
  if (speed_byte >= 16)
    return;

  g_speed = speed_map[speed_byte];
  //Serial.print("C> speed set to: ");
  //Serial.println(g_speed);
}

/**
 * Task control.
 */
void taskControl(uint8_t task_byte) {
  if (task_byte >= 16)
    return;

  //g_should_measure = task_byte == 1;
  //Serial.print("C> measurement control set to: ");
  //Serial.println(g_should_measure ? 'active' : 'inactive');
}
