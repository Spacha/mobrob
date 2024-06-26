/*
 * This file is part of the Mobrob project.
 *
 * This is the main entrypoint of the robot software.
 *
 * Miika & Essi
 */

#include "mobrob.h"
#include "Drive.h"
#include "MobrobClient.h"
#include "sensors/UltrasonicSensor.h"
#include "sensors/IMUSensor.h"

///////////////////////////////////////
// Set up modules
///////////////////////////////////////

Drive drive(PIN_L1, PIN_L2, PIN_LEN,
            PIN_R1, PIN_R2, PIN_REN);

MobrobClient client(IPAddress(SERVER_ADDR), SERVER_PORT,
                    update_configuration, control);

UltrasonicSensor ut_sensor(PIN_UT_TRIG, PIN_UT_ECHO);

IMUSensor imu_sensor(PIN_IMU_SDA, PIN_IMU_SCL);

///////////////////////////////////////
// Configuration
///////////////////////////////////////

Status g_status = UNCONNECTED;
Mode g_mode = MANUAL;

float g_track_speed = 0.0;
float g_left_track_speed = 0.0;
float g_right_track_speed = 0.0;

// TODO: An update struct?
float g_roll = 0.0;
float g_pitch = 0.0;
float g_temperature = 0.0;
float g_travel_dist = 0.0;
float g_obstacle_dist = 999.9;


void setup()
{
  Wire.setPins(PIN_IMU_SDA, PIN_IMU_SCL);

  Serial.begin(115200);
  delay(100);

  client.setup();
  if (!imu_sensor.setup())
    PRINTLN("Error: failed to initiate IMU sensor!");

  ///////////////////////////////////////
  // Set up pins
  ///////////////////////////////////////

  pinMode(PIN_STATUS_LED, OUTPUT);
  pinMode(PIN_UT_TRIG, OUTPUT);
  pinMode(PIN_UT_ECHO, INPUT);
  pinMode(PIN_LEN, OUTPUT);
  pinMode(PIN_L1, OUTPUT);
  pinMode(PIN_L2, OUTPUT);
  pinMode(PIN_REN, OUTPUT);
  pinMode(PIN_R1, OUTPUT);
  pinMode(PIN_R2, OUTPUT);

  PRINTLN("Initialized. Commands:");
  PRINTLN("1. drive <left_direction> <right_direction>");
  PRINTLN("2. brake <1 (apply) | 0 (release)>");
  PRINTLN("3. speed <speed>");
  PRINTLN("4. status <0 (UNCONNECTED) | 1 (CONNECTED)>");
  PRINTLN();

  drive.control(0.0, 0.0);

  ///////////////////////////////////////
  // Start tasks
  ///////////////////////////////////////

  xTaskCreate(TaskControl,            "Control",            2048, NULL, 1, NULL);
  xTaskCreate(TaskMaintainConnection, "MaintainConnection", 4096, NULL, 2, NULL);
  xTaskCreate(TaskSendUpdate,         "SendUpdate",         4096, NULL, 3, NULL);
  xTaskCreate(TaskReceiveSerial,      "ReceiveSerial",      2048, NULL, 4, NULL);
  xTaskCreate(TaskBlink,              "Blink",              2048, NULL, 5, NULL);
}

void loop() { /* Not used with FreeRTOS */ }

///////////////////////////////////////////////////////////////////////////////
// Task definitions
///////////////////////////////////////////////////////////////////////////////

/**
 * Task for controlling the robot's movement in 'real-time',
 * based on the current control commands.
 *
 * @param params No parameters used.
 */
void TaskControl(void *params)
{
  (void)params;

  //long started_turning_at = -1;
  bool turning = false;

  for (;;) {
    // TODO: hall measurements - move from the old FW version

    // if connected and in the EXPLORE mode,
    // drive avoiding obstacles by turning
    if (g_status == CONNECTED && g_mode == EXPLORE)
    {
      if (turning)
      {
        if (g_obstacle_dist > 30.0)
        {
          PRINTLN("[EXP] Stop turning");
          g_left_track_speed = 0;
          g_right_track_speed = 0;
          turning = false;
        }
      }

      if (!turning)
      {
        // start turning
        if (g_obstacle_dist <= 15.0)
        {
          PRINTLN("[EXP] Start turning");
          g_left_track_speed = g_track_speed;
          g_right_track_speed = -g_track_speed;
          turning = true;
        }
        // drive forward
        else
        {
          g_left_track_speed = g_track_speed;
          g_right_track_speed = g_track_speed;
        }
      }
    }

    drive.control(g_left_track_speed, g_right_track_speed);
    vTaskDelay(25 / portTICK_PERIOD_MS);
  }
}

/**
 * Task for receiving commands from the serial port when in debug mode.
 *
 * @param params No parameters used.
 */
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
          PRINTLN("Brake applied");
        }
        else if (brakeValue == 0)
        {
          drive.release_brake();
          PRINTLN("Brake released");
        }
        else
        {
          PRINTLN("Invalid brake command. Use: brake <1 (apply) | 0 (release)>");
        }
      }
      else if (input.startsWith("status "))
      {
        int statusValue = input.substring(7).toInt();
        if (statusValue == 1)
        {
          g_status = CONNECTED;
          PRINTLN("Status set to CONNECTED");
        }
        else if (statusValue == 0)
        {
          g_status = UNCONNECTED;
          PRINTLN("Status set to UNCONNECTED");
        }
        else
        {
          PRINTLN("Invalid status command. Use: status <0 (UNCONNECTED) | 1 (CONNECTED)>");
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

          g_left_track_speed = g_track_speed * left_speed;
          g_right_track_speed = g_track_speed * right_speed;

          PRINT("Left speed: ");
          PRINT(left_speed);
          PRINT(", Right speed: ");
          PRINTLN(right_speed);
        }
        else
        {
          PRINTLN("Invalid input format. Use: <left_speed> <right_speed>");
        }
      }
      else if (input.startsWith("speed "))
      {
        int speed = input.substring(6).toFloat();

        g_track_speed = speed;

        PRINT("Speed set to ");
        PRINTLN(speed);
      }
      else
      {
        PRINTLN("Invalid command.");
      }
    }

    vTaskDelay(100 / portTICK_PERIOD_MS);
  }
}

/**
 * Task for blinking the status LED.
 *
 * @param params No parameters used.
 */
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

/**
 * Task for sending data updates to the server.
 *
 * @param params No parameters used.
 */
void TaskSendUpdate(void *params)
{
  (void)params;

  const int update_rate = 250;

  imu_data_t imu_data;

  for (;;)
  {
    // if connected, take a measurement and send an update to the server
    if (g_status == CONNECTED)
    {
      imu_sensor.measure_all(&imu_data);
      g_roll = imu_data.roll;
      g_pitch = imu_data.pitch;
      g_temperature = imu_data.temperature;

      //g_travel_dist = g_travel_dist + (float)random(0, 5) / 10;
      g_obstacle_dist = ut_sensor.measure_distance();

      client.send_robot_update(g_roll, g_pitch, g_temperature, g_travel_dist, g_obstacle_dist);
    }

    vTaskDelay(update_rate / portTICK_PERIOD_MS);
  }
}

/**
 * Task for maintaining the robot's connection with the server.
 *
 * @param params No parameters used.
 */
void TaskMaintainConnection(void *params)
{
  (void)params;

  const int wifi_poll_delay     = 5000;
  const int wifi_timeout        = 20000;
  const int wifi_recover_delay  = 15000;

  for (;;)
  {
    // connected: sleep for a while and then check again
    if (client.connected())
    {
      vTaskDelay(wifi_poll_delay / portTICK_PERIOD_MS);
      continue;
    }

    // unconnected: try connecting
    g_status = UNCONNECTED;
    drive.control(0.0, 0.0);
    
    if (client.try_connect(wifi_timeout))
    {
      // just connected
      g_status = CONNECTED;
      continue;
    }

    // connection failed: sleep for a while and try again
    PRINTLN("[CLIENT] Error: Connection failed.");
    vTaskDelay(wifi_recover_delay / portTICK_PERIOD_MS);
  }
}

/**
 * Update the robot's configuration.
 *
 * @param track_speed The track speed of both tracks [0, 1]
 * @param mode The robot's mode {MANUAL, EXPLORE}
 */
void update_configuration(float track_speed, Mode mode)
{
  // Update the configuration based on the received values
  PRINT("Track Speed: ");
  PRINTLN(track_speed);
  PRINT("Mode: ");
  PRINTLN(mode == MANUAL ? "MANUAL" : "EXPLORE");

  if (g_mode == EXPLORE && mode == MANUAL)
  {
    g_left_track_speed = 0;
    g_right_track_speed = 0;
  }

  g_track_speed = track_speed;
  g_mode = mode;
}

/**
 * Control the robot's driving.
 *
 * @param left_track The direction of the left track {-1, 0, 1}
 * @param right_track The direction of the right track {-1, 0, 1}
 */
void control(float left_track, float right_track)
{
  g_left_track_speed = left_track * g_track_speed;
  g_right_track_speed = right_track * g_track_speed;
}
