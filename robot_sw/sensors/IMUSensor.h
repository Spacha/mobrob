#ifndef __IMU_SENSOR_H__
#define __IMU_SENSOR_H__

#include "mobrob.h"

class IMUSensor
{
protected:
  uint8_t m_pin_sda;
  uint8_t m_pin_scl;

public:
  IMUSensor(uint8_t pin_sda, uint8_t pin_scl);
  ~IMUSensor();
};

/**
 * TODO.
*/
IMUSensor::IMUSensor(uint8_t pin_sda, uint8_t pin_scl)
  : m_pin_sda(pin_sda),
    m_pin_scl(pin_scl)
{}

/**
 * TODO.
*/
IMUSensor::~IMUSensor() {}

///////////////////////////////////////////////////////////
// Nonpublic methods
///////////////////////////////////////////////////////////

#endif /* __IMU_SENSOR_H__ */
