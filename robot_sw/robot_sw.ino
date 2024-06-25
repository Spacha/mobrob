#include "mobrob.h"
#include "Drive.h"
#include "MobrobClient.h"

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

// Drive
Drive drive(PIN_L1, PIN_L2, PIN_LEN,
            PIN_R1, PIN_R2, PIN_REN);

// Client
MobrobClient client(IPAddress(SERVER_ADDR), SERVER_PORT, update_configuration, control);

// Configuration
Status g_status = UNCONNECTED;
Mode g_mode = MANUAL;
float g_track_speed = 0.0;

// TODO: An update struct?
float g_roll = 0.0;
float g_pitch = 0.0;
float g_temperature = 0.0;
float g_travel_dist = 0.0;

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

  xTaskCreate(TaskKeepWifiAlive,  "KeepWifiAlive",  4096, NULL, 2, NULL);
  xTaskCreate(TaskSendUpdate,     "SendUpdate",     4096, NULL, 3, NULL);
  xTaskCreate(TaskReceiveSerial,  "ReceiveSerial",  2048, NULL, 4, NULL);
  xTaskCreate(TaskBlink,          "Blink",          2048, NULL, 5, NULL);
}

void loop()
{
  // ...
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

void TaskSendUpdate(void *params)
{
  (void)params;

  const int update_rate = 2000;

  for (;;)
  {
    if (g_status == CONNECTED)
    {
      // TODO: Take a measurement?

      g_roll = (float)random(0, 10) / 10 - 0.5;
      g_pitch = (float)random(0, 10) / 10 - 0.5;
      g_temperature = (float)random(23, 28);
      g_travel_dist = g_travel_dist + (float)random(0, 5) / 10;

      client.send_robot_update(g_roll, g_pitch, g_temperature, g_travel_dist);
    }

    vTaskDelay(update_rate / portTICK_PERIOD_MS);
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
    // Connected: sleep for a while and then check again
    if (client.connected())
    {
      vTaskDelay(wifi_poll_delay / portTICK_PERIOD_MS);
      continue;
    }

    // Unconnected: try connecting
    g_status = UNCONNECTED;
    
    if (client.try_connect(wifi_timeout))
    {
      // Just connected
      g_status = CONNECTED;
      continue;
    }

    // Connection failed: sleep for a while and try again
    Serial.println("[CLIENT] Error: Connection failed.");
    vTaskDelay(wifi_recover_delay / portTICK_PERIOD_MS);
  }
}


void update_configuration(float track_speed, Mode mode)
{
  // Update the configuration based on the received values
  Serial.print("Track Speed: ");
  Serial.println(track_speed);
  Serial.print("Mode: ");
  Serial.println(mode == MANUAL ? "MANUAL" : "EXPLORE");

  g_track_speed = track_speed;
  g_mode = mode;
}

void control(float left_track, float right_track)
{
  // Update the configuration based on the received values
  Serial.print("Control: left:");
  Serial.print(left_track);
  Serial.print(", right:");
  Serial.println(right_track);

  // TODO: drive
}
