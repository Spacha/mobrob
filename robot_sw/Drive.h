#ifndef __DRIVE_H__
#define __DRIVE_H__

// Should be between 0-255
#define MAX_SPEED 180

// Track speed calibration values
#ifndef __TESTING__
#define CALIBRATED_LEFT(s) ((s)  - (s) * 0.01)
#define CALIBRATED_RIGHT(s) ((s) + (s) * 0.01)
#else
#define CALIBRATED_LEFT(s) (s)
#define CALIBRATED_RIGHT(s) (s)
#endif

///////////////////////////////////////////////////////////////////////////////
// Motor
///////////////////////////////////////////////////////////////////////////////

// x1    x2    xEN
//  0     0     0     free-running motor stop
//  0     1     1     drive forward
//  1     0     1     drive backward
//  1     1     1     fast motor stop

/**
 * The object for managing a single DC motor.
 */
class Motor
{
protected:
  uint8_t m_pin_1;
  uint8_t m_pin_2;
  uint8_t m_pin_en;

public:
  Motor(uint8_t pin_1, uint8_t pin_2, uint8_t pin_en); 
  ~Motor();

  void drive_forward(float speed);
  void drive_backward(float speed);
  void stop(bool brake = false);
};

/**
 * Construct the Motor class.
 * @param pin_1 
 */
Motor::Motor(uint8_t pin_1, uint8_t pin_2, uint8_t pin_en)
  : m_pin_1(pin_1),
    m_pin_2(pin_2),
    m_pin_en(pin_en)
{}

/**
 * Destruct the Motor class.
 */
Motor::~Motor() {}

/**
 * Drive the motor forward.
 * 
 * @param speed The speed of the motor, between [0, 1]
 */
void Motor::drive_forward(float speed)
{
  // clamp speed
  if (speed > 1.0) speed = 1.0;
  if (speed < 0.0) speed = 0.0;

  digitalWrite(m_pin_1, LOW);
  digitalWrite(m_pin_2, HIGH);
  analogWrite(m_pin_en, (int)(speed * MAX_SPEED));
}

/**
 * Drive the motor backward.
 * 
 * @param speed The speed of the motor, between [0, 1]
 */
void Motor::drive_backward(float speed)
{
  // clamp speed
  if (speed > 1.0) speed = 1.0;
  if (speed < 0.0) speed = 0.0;

  digitalWrite(m_pin_1, HIGH);
  digitalWrite(m_pin_2, LOW);
  analogWrite(m_pin_en, (int)(speed * MAX_SPEED));
}

/**
 * Stop the motor from moving, optionally with hard brake.
 * 
 * @param brake Whether to apply the hard brake to disallow free rolling
 */
void Motor::stop(bool brake)
{
  digitalWrite(m_pin_1, HIGH);
  digitalWrite(m_pin_2, HIGH);
  analogWrite(m_pin_en, brake ? 255 : 0);
}


///////////////////////////////////////////////////////////////////////////////
// Drive
///////////////////////////////////////////////////////////////////////////////

/**
 * The object for managing the tank's movement.
 */
class Drive
{
public:
  Drive(uint8_t pin_l1, uint8_t pin_l2, uint8_t pin_len, uint8_t pin_r1, uint8_t pin_r2, uint8_t pin_ren);
  ~Drive();

  void control(float left_speed, float right_speed);
  void apply_brake();
  void release_brake();

protected:
  Motor m_left_motor;
  Motor m_right_motor;
};

/**
 * Construct the Drive class.
 */
Drive::Drive(uint8_t pin_l1, uint8_t pin_l2, uint8_t pin_len, uint8_t pin_r1, uint8_t pin_r2, uint8_t pin_ren)
  : m_left_motor(pin_l1, pin_l2, pin_len), 
    m_right_motor(pin_r1, pin_r2, pin_ren) 
{}

/**
 * Destruct the Drive class.
 */
Drive::~Drive() {}

/**
 * Control the movement of the robot.
 * 
 * @param left_speed The speed of the left track [-1, 1]. Negative
 *                   values drive the motor backward, while positive
 *                   values drive it forward.
 * @param left_speed The speed of the right track [-1, 1]. Negative
 *                   values drive the motor backward, while positive
 *                   values drive it forward.
 */
void Drive::control(float left_speed, float right_speed)
{
  if (left_speed > 0)
    m_left_motor.drive_forward(CALIBRATED_LEFT(left_speed));
  else if (left_speed < 0)
    m_left_motor.drive_backward(-CALIBRATED_LEFT(left_speed));
  else
    m_left_motor.stop();

  if (right_speed > 0)
    m_right_motor.drive_forward(CALIBRATED_RIGHT(right_speed));
  else if (right_speed < 0)
    m_right_motor.drive_backward(-CALIBRATED_RIGHT(right_speed));
  else
    m_right_motor.stop();
}

/**
 * Apply the hard brake to disallow free rolling. Applies to both tracks.
 */
void Drive::apply_brake()
{
  m_left_motor.stop(true);
  m_right_motor.stop(true);
}

/**
 * Release the hard brake to allow free rolling.
 */
void Drive::release_brake()
{
  m_left_motor.stop(false);
  m_right_motor.stop(false);
}

#endif /* __DRIVE_H__ */
