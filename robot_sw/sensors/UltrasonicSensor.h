#ifndef __ULTRASONIC_SENSOR_H__
#define __ULTRASONIC_SENSOR_H__

/*
 * This file is part of the Mobrob project.
 *
 * This is the UT sensor for the robot for measuring distance.
 */

#include "mobrob.h"

// how many measurements to take for averaging
#define NUM_MEASUREMENTS 3

/**
 * The class for communicating with the ultrasonic sensor.
 */
class UltrasonicSensor
{
protected:
  uint8_t m_pin_trig;
  uint8_t m_pin_echo;

  void send_echo();
  float us_to_cm(long us);

public:
  UltrasonicSensor(uint8_t pin_trig, uint8_t pin_echo);
  ~UltrasonicSensor();

  float measure_distance();
};


///////////////////////////////////////////////////////////////////////////////
// Method definitions
///////////////////////////////////////////////////////////////////////////////

/**
 * Construct the UltrasonicSensor class.
 * 
 * @param pin_trig The trigger pin of the sensor
 * @param pin_echo The echo pin of the sensor
*/
UltrasonicSensor::UltrasonicSensor(uint8_t pin_trig, uint8_t pin_echo)
  : m_pin_trig(pin_trig),
    m_pin_echo(pin_echo)
{}

/**
 * Destruct the UltrasonicSensor class.
*/
UltrasonicSensor::~UltrasonicSensor() {}

/**
 * Measure distance to an obstacle.
 * 
 * @return Obstacle distance in centimeters
*/
float UltrasonicSensor::measure_distance()
{
  // calculate the average over multiple measurements
  long sum_durations = 0;
  for (int i = 0; i < NUM_MEASUREMENTS; i++)
  {
    send_echo();
    sum_durations += pulseIn(m_pin_echo, HIGH);
    delay(2);
  }

  return us_to_cm(sum_durations / NUM_MEASUREMENTS);
}

///////////////////////////////////////////////////////////
// Nonpublic methods
///////////////////////////////////////////////////////////

/**
 * Send an echo from the ultrasonic transducer.
*/
void UltrasonicSensor::send_echo()
{
  digitalWrite(m_pin_trig, LOW);
  delayMicroseconds(2);
  digitalWrite(m_pin_trig, HIGH);
  delayMicroseconds(10);
  digitalWrite(m_pin_trig, LOW);
}

/**
 * Convert microseconds (of sound travel) to centimeters.
 * 
 * @param us Delay in microseconds
 * @return The corresponding distance in centimeters
*/
float UltrasonicSensor::us_to_cm(long us)
{
  return static_cast<float>(us / 29 / 2);
}

#endif /* __ULTRASONIC_SENSOR_H__ */
