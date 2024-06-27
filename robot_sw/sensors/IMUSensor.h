#ifndef __IMU_SENSOR_H__
#define __IMU_SENSOR_H__

/*
 * This file is part of the Mobrob project.
 *
 * This is the IMU sensor for the robot for reading IMU data.
 */

#ifndef __TESTING__
#include <Adafruit_MPU6050.h>
#include <Adafruit_Sensor.h>
#include <Wire.h>
#else
#include "test/mocks/Adafruit_MPU6050.h"
#include "test/mocks/Adafruit_Sensor.h"
#endif
#include <math.h>
#include "mobrob.h"

///////////////////////////////////////////////////////////////////////////////
// Calibration values
///////////////////////////////////////////////////////////////////////////////

#define TEMP_CALIBRATED(t)  ((t) - 6.0)
#define PITCH_CALIBRATED(p) ((p) - 1.1)
#define ROLL_CALIBRATED(r)  ((r) + 5.9)

///////////////////////////////////////////////////////////////////////////////

// A container for the preprocessed IMU data
typedef struct
{
  float temperature;
  float pitch;
  float roll;
} imu_data_t;

/**
 * Interacts with the MPU6050 intertial measurement unit.
 */
class IMUSensor
{
protected:
  Adafruit_MPU6050 m_mpu;
  uint8_t m_pin_sda;
  uint8_t m_pin_scl;

  void preprocess_data(imu_data_t *data, sensors_event_t *a, sensors_event_t *g, sensors_event_t *t);

public:
  IMUSensor(uint8_t pin_sda, uint8_t pin_scl);
  ~IMUSensor();

  bool setup();
  void measure_all(imu_data_t *data);
};


///////////////////////////////////////////////////////////////////////////////
// Method definitions
///////////////////////////////////////////////////////////////////////////////

/**
 * Construct the IMUSensor class.
 * 
 * @param pin_sda The serial data (SDA) pin
 * @param pin_scl The serial clock (SCL) pin
*/
IMUSensor::IMUSensor(uint8_t pin_sda, uint8_t pin_scl)
  : m_pin_sda(pin_sda),
    m_pin_scl(pin_scl)
{}

/**
 * Destruct the IMUSensor class.
 * 
 * @param pin_sda The serial data (SDA) pin
 * @param pin_scl The serial clock (SCL) pin
*/
IMUSensor::~IMUSensor() {}

/**
 * Setup the sensor. This tries connecting with the sensor unit and configures it.
 * 
 * @return True if the connection was successful, false otherwise
*/
bool IMUSensor::setup() {
  // set up pins for I2C / wire
  //Wire.setPins(m_pin_sda, m_pin_scl);

  if (!m_mpu.begin())
    return false;

  // set up MPU
  m_mpu.setAccelerometerRange(MPU6050_RANGE_8_G);
  m_mpu.setGyroRange(MPU6050_RANGE_500_DEG);
  m_mpu.setFilterBandwidth(MPU6050_BAND_5_HZ);

  return true;
}

/**
 * Take all measurements from the sensor at once.
 * 
 * @param data The data container to store the preprocessed measurements into
*/
void IMUSensor::measure_all(imu_data_t *data) {
  sensors_event_t a, g, temp;
  m_mpu.getEvent(&a, &g, &temp);
  preprocess_data(data, &a, &g, &temp);
}

///////////////////////////////////////////////////////////
// Nonpublic methods
///////////////////////////////////////////////////////////

/**
 * Preprocess the measurement data. This converts the raw measurements
 * into the measurements the robot needs.
 * 
 * @param data The data container to store the preprocessed measurements into
 * @param a The accelerometer sensor event
 * @param g The gyroscope sensor event
 * @param t The temperature sensor event
*/
void IMUSensor::preprocess_data(imu_data_t *data, sensors_event_t *a, sensors_event_t *g, sensors_event_t *t) {
  data->temperature = TEMP_CALIBRATED(t->temperature);

  // in degrees
  data->pitch = PITCH_CALIBRATED(-atan2(a->acceleration.y, sqrt(a->acceleration.x * a->acceleration.x + a->acceleration.z * a->acceleration.z)) * 180.0 / PI);
  data->roll = ROLL_CALIBRATED(-atan2(a->acceleration.z, sqrt(a->acceleration.x * a->acceleration.x + a->acceleration.y * a->acceleration.y)) * 180.0 / PI);
}

#endif /* __IMU_SENSOR_H__ */
