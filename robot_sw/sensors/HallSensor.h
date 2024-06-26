#ifndef __HALL_SENSOR_H__
#define __HALL_SENSOR_H__

#include "mobrob.h"

class HallSensor
{
protected:
  uint8_t m_pin_out;

public:
  HallSensor(uint8_t m_pin_out);
  ~HallSensor();
};

/**
 * TODO.
*/
HallSensor::HallSensor(uint8_t pin_out)
  : m_pin_out(pin_out)
{}

/**
 * TODO.
*/
HallSensor::~HallSensor() {}

///////////////////////////////////////////////////////////
// Nonpublic methods
///////////////////////////////////////////////////////////

#endif /* __HALL_SENSOR_H__ */
