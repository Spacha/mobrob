#ifndef __ADAFRUIT_MPU6050_H__
#define __ADAFRUIT_MPU6050_H__

#include "Adafruit_Sensor.h"

// THIS IS A STUB FOR TESTING ONLY

#define MPU6050_RANGE_8_G       1
#define MPU6050_RANGE_500_DEG   1
#define MPU6050_BAND_5_HZ       1

class Adafruit_MPU6050
{
public:
    Adafruit_MPU6050();
    ~Adafruit_MPU6050();

    void getEvent(sensors_event_t *a, sensors_event_t *g, sensors_event_t *t);
    bool begin();
    void setAccelerometerRange(int v);
    void setGyroRange(int v);
    void setFilterBandwidth(int v);
};

Adafruit_MPU6050::Adafruit_MPU6050() {}

Adafruit_MPU6050::~Adafruit_MPU6050() {}

void Adafruit_MPU6050::getEvent(sensors_event_t *a, sensors_event_t *g, sensors_event_t *t)
{
    a->acceleration.x = 1.2;
    a->acceleration.y = -1.0;
    a->acceleration.z = 0.0;
    t->temperature = 20.2;
}

bool Adafruit_MPU6050::begin() { return true; }
void Adafruit_MPU6050::setAccelerometerRange(int v) {}
void Adafruit_MPU6050::setGyroRange(int v) {}
void Adafruit_MPU6050::setFilterBandwidth(int v) {}


#endif /* __ADAFRUIT_MPU6050_H__ */
