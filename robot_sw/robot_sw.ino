#include "Drive.h"

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

Drive drive(PIN_L1, PIN_L2, PIN_LEN,
            PIN_R1, PIN_R2, PIN_REN);

status g_status = UNCONNECTED;

void setup()
{
  Serial.begin(115200);
  delay(100);

  ///////////////////////////////////////
  // Set up tasks
  ///////////////////////////////////////

  xTaskCreate(TaskBlink, "Blink", 2048, NULL, 5, NULL);
  xTaskCreate(TaskReceiveSerial, "ReceiveSerial", 2048, NULL, 3, NULL);

  pinMode(PIN_LEN, OUTPUT);
  pinMode(PIN_L1, OUTPUT);
  pinMode(PIN_L2, OUTPUT);
  pinMode(PIN_REN, OUTPUT);
  pinMode(PIN_R1, OUTPUT);
  pinMode(PIN_R2, OUTPUT);

  Serial.print("Initialized.");

  Serial.println("Enter commands:");
  Serial.println("1. drive <left_speed> <right_speed>");
  Serial.println("2. brake <1 (apply) | 0 (release)>");
  Serial.println("3. status <0 (UNCONNECTED) | 1 (CONNECTED)>");
}

void loop()
{

}


///////////////////////////////////////////////////////////////////////////////
// Task definitions
///////////////////////////////////////////////////////////////////////////////

void TaskReceiveSerial(void *params) {
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

void TaskBlink(void *params) {
  (void)params;

  const int delay_unconnected = 250;
  const int delay_connected   = 1000;

  pinMode(PIN_STATUS_LED, OUTPUT);

  for (;;) {
    digitalWrite(PIN_STATUS_LED, HIGH);
    if (g_status == CONNECTED)
      delay(delay_connected);
    else
      delay(delay_unconnected);

    digitalWrite(PIN_STATUS_LED, LOW);
    if (g_status == CONNECTED)
      delay(delay_connected);
    else
      delay(delay_unconnected);
  }
}
