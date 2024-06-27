#ifndef __MOBROB_H__
#define __MOBROB_H__

#include "network_credentials.h"

#define FW_VERSION "1.0.0"

#define __DEBUG__

///////////////////////////////////////////////////////////////////////////////
// Pin assignments
///////////////////////////////////////////////////////////////////////////////

#define PIN_STATUS_LED  13

#define PIN_UT_TRIG     21
#define PIN_UT_ECHO      4
#define PIN_IMU_SDA     22
#define PIN_IMU_SCL     23
#define PIN_LHALL       36
#define PIN_RHALL       39

#define PIN_LEN         14    // Left motor enable:     3,4EN
#define PIN_L1          27    // Left motor control 1:  3A
#define PIN_L2          26    // Left motor control 2:  4A
#define PIN_REN         25    // Right motor enable:    1,2EN
#define PIN_R1          33    // Right motor control 1: 1A
#define PIN_R2          32    // Right motor control 2: 2A

///////////////////////////////////////////////////////////////////////////////

#if CONFIG_FREERTOS_UNICORE
# define ARDUINO_RUNNING_CORE 0
#else
# define ARDUINO_RUNNING_CORE 1
#endif

///////////////////////////////////////////////////////////////////////////////
// Definitions
///////////////////////////////////////////////////////////////////////////////

enum Status { UNCONNECTED, CONNECTED };
enum Mode { MANUAL = 0, EXPLORE = 1 };

///////////////////////////////////////////////////////////////////////////////
// Forward declarations
///////////////////////////////////////////////////////////////////////////////

void update_configuration(float track_speed, Mode mode);
void control(float left_track, float right_track);

void TaskControl(void *params);
void TaskKeepWifiAlive(void *params);
void TaskSendUpdate(void *params);
void TaskReceiveSerial(void *params);
void TaskBlink(void *params);

#endif /* __MOBROB_H__ */
