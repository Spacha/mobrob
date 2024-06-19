///////////////////////////////////////////////////////////////////////////////
// Motor
///////////////////////////////////////////////////////////////////////////////

// x1    x2    xEN
//  0     0     0     free-running motor stop
//  0     1     1     drive forward
//  1     0     1     drive backward
//  1     1     1     fast motor stop

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

Motor::Motor(uint8_t pin_1, uint8_t pin_2, uint8_t pin_en)
  : m_pin_1(pin_1),
    m_pin_2(pin_2),
    m_pin_en(pin_en)
{}

Motor::~Motor() {}

void Motor::drive_forward(float speed)
{
  assert(speed >= 0 && speed <= 1);

  digitalWrite(m_pin_1, LOW);
  digitalWrite(m_pin_2, HIGH);
  analogWrite(m_pin_en, speed * 255);
}

void Motor::drive_backward(float speed)
{
  assert(speed >= 0 && speed <= 1);

  digitalWrite(m_pin_1, HIGH);
  digitalWrite(m_pin_2, LOW);
  analogWrite(m_pin_en, speed * 255);
}

void Motor::stop(bool brake)
{
  digitalWrite(m_pin_1, HIGH);
  digitalWrite(m_pin_2, HIGH);
  analogWrite(m_pin_en, brake ? 255 : 0);
}


///////////////////////////////////////////////////////////////////////////////
// Drive
///////////////////////////////////////////////////////////////////////////////

class Drive
{
public:
  Drive(int pin_l1, int pin_l2, int pin_len, int pin_r1, int pin_r2, int pin_ren);
  ~Drive();

  void control(float left_speed, float right_speed);
  void apply_brake();
  void release_brake();

protected:
  Motor m_left_motor;
  Motor m_right_motor;
};

Drive::Drive(int pin_l1, int pin_l2, int pin_len, int pin_r1, int pin_r2, int pin_ren)
  : m_left_motor(pin_l1, pin_l2, pin_len), 
    m_right_motor(pin_r1, pin_r2, pin_ren) 
{}

Drive::~Drive() {}

void Drive::control(float left_speed, float right_speed)
{
  if (left_speed > 0)
    m_left_motor.drive_forward(left_speed);
  else if (left_speed < 0)
    m_left_motor.drive_backward(-left_speed);
  else
    m_left_motor.stop();

  if (right_speed > 0)
    m_right_motor.drive_forward(right_speed);
  else if (right_speed < 0)
    m_right_motor.drive_backward(-right_speed);
  else
    m_right_motor.stop();
}

void Drive::apply_brake()
{
  m_left_motor.stop(true);
  m_right_motor.stop(true);
}

void Drive::release_brake()
{
  m_left_motor.stop(false);
  m_right_motor.stop(false);
}
