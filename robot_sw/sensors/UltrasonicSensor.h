#ifndef __ULTRASONIC_SENSOR_H__
#define __ULTRASONIC_SENSOR_H__

#include "mobrob.h"

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

  float measure_distance(uint8_t num_measurements = 1);
};

/**
 * TODO.
*/
UltrasonicSensor::UltrasonicSensor(uint8_t pin_trig, uint8_t pin_echo)
  : m_pin_trig(pin_trig),
    m_pin_echo(pin_echo)
{}

/**
 * TODO.
*/
UltrasonicSensor::~UltrasonicSensor() {}

/**
 * TODO.
*/
float UltrasonicSensor::measure_distance(uint8_t num_measurements)
{
  send_echo();
  long duration = pulseIn(m_pin_echo, HIGH);

  return us_to_cm(duration);
}

///////////////////////////////////////////////////////////
// Nonpublic methods
///////////////////////////////////////////////////////////

/**
 * TODO.
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
 * TODO.
*/
float UltrasonicSensor::us_to_cm(long us)
{
  return static_cast<float>(us / 29 / 2);
}

#endif /* __ULTRASONIC_SENSOR_H__ */
