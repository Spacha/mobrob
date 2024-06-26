#ifndef __MOBROB_H__
#define __MOBROB_H__

#include "network_credentials.h"

#define FW_VERSION "1.2.3"

enum Status { UNCONNECTED, CONNECTED };
enum Mode { MANUAL = 0, EXPLORE = 1 };

// Forward declarations
void update_configuration(float track_speed, Mode mode);
void control(float left_track, float right_track);

void TaskControl(void *params);
void TaskKeepWifiAlive(void *params);
void TaskSendUpdate(void *params);
void TaskReceiveSerial(void *params);
void TaskBlink(void *params);

#endif /* __MOBROB_H__ */
