#include "WiFi.h"
#include "AsyncUDP.h"

#include "Drive.h"
#include "network_credentials.h"

enum status { UNCONNECTED, CONNECTED };

///////////////////////////////////////////////////////////////////////////////
// Pin assignments
///////////////////////////////////////////////////////////////////////////////

#define PIN_STATUS_LED  13
#define PIN_LEN         14    // Left motor enable:     1,2EN
#define PIN_L1          27    // Left motor control 1:  1A
#define PIN_L2          26    // Left motor control 2:  2A
#define PIN_REN         25    // Right motor enable:    3,4EN
#define PIN_R1          33    // Right motor control 1: 3A
#define PIN_R2          32    // Right motor control 2: 4A

///////////////////////////////////////////////////////////////////////////////

#if CONFIG_FREERTOS_UNICORE
# define ARDUINO_RUNNING_CORE 0
#else
# define ARDUINO_RUNNING_CORE 1
#endif

void TaskBlink(void *params);
void TaskReceiveSerial(void *params);
void TaskKeepWifiAlive(void *params);

// WiFi and UDP
IPAddress g_server_addr(192, 168, 1, 168);
uint16_t g_server_port = 3333;
AsyncUDP udp;

// Drive
Drive drive(PIN_L1, PIN_L2, PIN_LEN,
            PIN_R1, PIN_R2, PIN_REN);

status g_status = UNCONNECTED;

void setup()
{
  Serial.begin(115200);
  delay(100);

  ///////////////////////////////////////
  // Set up pins
  ///////////////////////////////////////

  pinMode(PIN_STATUS_LED, OUTPUT);
  pinMode(PIN_LEN, OUTPUT);
  pinMode(PIN_L1, OUTPUT);
  pinMode(PIN_L2, OUTPUT);
  pinMode(PIN_REN, OUTPUT);
  pinMode(PIN_R1, OUTPUT);
  pinMode(PIN_R2, OUTPUT);


  Serial.println("Initialized. Commands:");
  Serial.println("1. drive <left_speed> <right_speed>");
  Serial.println("2. brake <1 (apply) | 0 (release)>");
  Serial.println("3. status <0 (UNCONNECTED) | 1 (CONNECTED)>");
  Serial.println();

  ///////////////////////////////////////
  // Start tasks
  ///////////////////////////////////////

  xTaskCreate(TaskBlink, "Blink", 2048, NULL, 5, NULL);
  xTaskCreate(TaskReceiveSerial, "ReceiveSerial", 2048, NULL, 3, NULL);
  xTaskCreate(TaskKeepWifiAlive, "KeepWifiAlive", 4096, NULL, 2, NULL);
}

void loop()
{

}


///////////////////////////////////////////////////////////////////////////////
// Task definitions
///////////////////////////////////////////////////////////////////////////////

void TaskReceiveSerial(void *params)
{
  (void)params;

  for (;;)
  {
    if (Serial.available() > 0)
    {
      String input = Serial.readStringUntil('\n');
      input.trim();

      if (input.startsWith("brake "))
      {
        int brakeValue = input.substring(6).toInt();
        if (brakeValue == 1)
        {
          drive.apply_brake();
          Serial.println("Brake applied");
        }
        else if (brakeValue == 0)
        {
          drive.release_brake();
          Serial.println("Brake released");
        }
        else
        {
          Serial.println("Invalid brake command. Use: brake <1 (apply) | 0 (release)>");
        }
      }
      else if (input.startsWith("status "))
      {
        int statusValue = input.substring(7).toInt();
        if (statusValue == 1)
        {
          g_status = CONNECTED;
          Serial.println("Status set to CONNECTED");
        }
        else if (statusValue == 0)
        {
          g_status = UNCONNECTED;
          Serial.println("Status set to UNCONNECTED");
        }
        else
        {
          Serial.println("Invalid status command. Use: status <0 (UNCONNECTED) | 1 (CONNECTED)>");
        }
      }
      else if (input.startsWith("drive "))
      {
        float left_speed = 0.0;
        float right_speed = 0.0;

        int spaceIndex = input.indexOf(' ', 6);
        if (spaceIndex > 0)
        {
          String leftSpeedStr = input.substring(6, spaceIndex);
          String rightSpeedStr = input.substring(spaceIndex + 1);

          left_speed = leftSpeedStr.toFloat();
          right_speed = rightSpeedStr.toFloat();

          drive.control(left_speed, right_speed);
          Serial.print("Left speed: ");
          Serial.print(left_speed);
          Serial.print(", Right speed: ");
          Serial.println(right_speed);
        }
        else
        {
          Serial.println("Invalid input format. Use: <left_speed> <right_speed>");
        }
      } else {
        Serial.println("Invalid command.");
      }
    }

    vTaskDelay(100 / portTICK_PERIOD_MS);
  }
}

void TaskBlink(void *params)
{
  (void)params;

  const int delay_unconnected = 250;
  const int delay_connected   = 1000;

  for (;;) {
    digitalWrite(PIN_STATUS_LED, HIGH);
    if (g_status == CONNECTED)
      vTaskDelay(delay_connected / portTICK_PERIOD_MS);
    else
      vTaskDelay(delay_unconnected / portTICK_PERIOD_MS);

    digitalWrite(PIN_STATUS_LED, LOW);
    if (g_status == CONNECTED)
      vTaskDelay(delay_connected / portTICK_PERIOD_MS);
    else
      vTaskDelay(delay_unconnected / portTICK_PERIOD_MS);
  }
}

void TaskKeepWifiAlive(void *params)
{
  (void)params;

  const int wifi_poll_delay     = 5000;
  const int wifi_timeout        = 20000;
  const int wifi_recover_delay  = 15000;
  //const int wifi_recover_delay  = 1000;

  for (;;)
  {
    // Regularly check if WiFi is still up
    if (WiFi.status() == WL_CONNECTED)
    {
      vTaskDelay(wifi_poll_delay / portTICK_PERIOD_MS);
      continue;
    }

    ///////////////////////////////////////////////////////////
    // WiFi not connected
    ///////////////////////////////////////////////////////////

    g_status = UNCONNECTED;
    Serial.println("[WIFI] Connecting...");
    WiFi.mode(WIFI_STA);
    WiFi.begin(NETWORK_NAME, NETWORK_PASSWORD);

    unsigned long start_attempt_time = millis();

    // if not connected, keep waiting until connected, or timeout reached
    while (WiFi.status() != WL_CONNECTED && (millis() - start_attempt_time) < wifi_timeout) {}

    // if we failed to connect, sleep for a while until we start trying again
    if (WiFi.status() != WL_CONNECTED)
    {
      Serial.println("[WIFI] FAILED");
      vTaskDelay(wifi_recover_delay / portTICK_PERIOD_MS);
      continue;
    }

    ///////////////////////////////////////////////////////////
    // WiFi connected
    ///////////////////////////////////////////////////////////

    Serial.print("[WIFI] Connected: ");
    Serial.println(WiFi.localIP());

    // connect to the server using UDP
    if (udp.connect(g_server_addr, g_server_port))
    {
      // Protocol here before connected!

      Serial.println("[UDP] Connected.");
      g_status = CONNECTED;

      // register receive callback when server sends a packet
      udp.onPacket([](AsyncUDPPacket packet)
      {
        if (packet.length() == 0)
          return;

        Serial.print("Received data: ");
        Serial.write(packet.data(), packet.length());
        Serial.println();
      });

      // send a unicast message right after connecting
      udp.print("Hello Server!");
    }
  }
}
