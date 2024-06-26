#include "MobrobClient.h"

#define PIN_LEN         14    // Left motor enable:     3,4EN
#define PIN_L1          27    // Left motor control 1:  3A
#define PIN_L2          26    // Left motor control 2:  4A
#define PIN_REN         25    // Right motor enable:    1,2EN
#define PIN_R1          33    // Right motor control 1: 1A
#define PIN_R2          32    // Right motor control 2: 2A

// UDP server address
#define SERVER_ADDR       192,168,1,168
#define SERVER_PORT       3333

void update_configuration(float track_speed, Mode mode)
{
}

void control(float left_track, float right_track)
{

}

MobrobClient client(IPAddress(SERVER_ADDR), SERVER_PORT, update_configuration, control);


void setup() {
  WiFi.mode(WIFI_STA);

  // put your setup code here, to run once:
  pinMode(PIN_REN, OUTPUT);
  pinMode(PIN_R1, OUTPUT);
  pinMode(PIN_R2, OUTPUT);

  pinMode(PIN_LEN, OUTPUT);
  pinMode(PIN_L1, OUTPUT);
  pinMode(PIN_L2, OUTPUT);

  xTaskCreate(TaskBlink,          "Blink",          2048, NULL, 2, NULL);
  xTaskCreate(TaskKeepWifiAlive,  "KeepWifiAlive",  4096, NULL, 3, NULL);
  xTaskCreate(TaskSendUpdate,     "SendUpdate",     2048, NULL, 3, NULL);
}

void loop() {}

void TaskBlink(void *params)
{
  (void)params;

  analogWrite(PIN_REN, 0);

  for (;;)
  {
    vTaskDelay(1000 / portTICK_PERIOD_MS);
    digitalWrite(PIN_R1, HIGH);
    digitalWrite(PIN_R2, LOW);
    analogWrite(PIN_REN, 180);

    // digitalWrite(PIN_L1, HIGH);
    // digitalWrite(PIN_L2, LOW);
    // analogWrite(PIN_LEN, 150);

    vTaskDelay(1000 / portTICK_PERIOD_MS);
    digitalWrite(PIN_R1, HIGH);
    digitalWrite(PIN_R2, HIGH);
    analogWrite(PIN_REN, 0);

    // digitalWrite(PIN_L1, HIGH);
    // digitalWrite(PIN_L2, HIGH);
    // analogWrite(PIN_LEN, 150);
  }
}

void TaskSendUpdate(void *params)
{
  (void)params;

  const int update_rate = 2000;

  for (;;)
  {
    if (client.connected())
    {
      float g_roll = 0.0;
      float g_pitch = 0.0;
      float g_temperature = 0.0;
      float g_travel_dist = 0.0;

      client.send_robot_update(g_roll, g_pitch, g_temperature, g_travel_dist);
    }

    vTaskDelay(update_rate / portTICK_PERIOD_MS);
  }
}

void TaskKeepWifiAlive(void *params)
{
  (void)params;

  for (;;)
  {
    // Connected: sleep for a while and then check again
    if (client.connected())
    {
      vTaskDelay(5000 / portTICK_PERIOD_MS);
      continue;
    }
    
    if (client.try_connect(5000))
    {
      continue;
    }

    vTaskDelay(10000 / portTICK_PERIOD_MS);
  }
}
