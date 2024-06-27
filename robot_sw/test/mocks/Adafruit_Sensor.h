#ifndef __ADAFRUIT_SENSOR_H__
#define __ADAFRUIT_SENSOR_H__

// THIS IS A STUB FOR TESTING ONLY

typedef struct
{
    float x;
    float y;
    float z;
} acc_t;

typedef struct
{
    float temperature;
    acc_t acceleration;
} sensors_event_t;

#endif /* __ADAFRUIT_SENSOR_H__ */
