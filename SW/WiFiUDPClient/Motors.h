#ifndef __MOTORS_H__
#define __MOTORS_H__

/***************************************************
 * Simple motor control demo for ESP32
 ***************************************************
 * Author: Miika Sikala, 2023
 *
 * Runs 2 motors forwards and backwards.
 * Speed is limited by using PWM.
 *
 ***************************************************
 * Schematic:
 ****************************************************
 *
 *                /---------------\
 *              o-| EN        D23 |-o
 *              o-| VP   |E|  D22 |-o
 *              o-| VN   |S|  TX0 |-o
 *              o-| D34  |P|  RX0 |-o
 *              o-| D35  |3|  D21 |-o
 *      (IN1)---o-| D32  |2|  D19 |-o
 *      (IN2)---o-| D33       D18 |-o
 *      (IN3)---o-| D25       D5  |-o
 *      (IN4)---o-| D26       TX2 |-o
 *              o-| D27       RX2 |-o
 *              o-| D14       D4  |-o
 *      (ENA)---o-| D12       D2  |-o
 *      (ENB)---o-| D13       D15 |-o
 *      (GND)---o-| GND       GND |-o
 *       (5V)---o-| VIN       3V3 |-o
 *                \---------------/
 *
 ***************************************************
 */

// Motor A pins
const int motorAPin1      = 32; // 2
const int motorAPin2      = 33; // 3
const int motorAPinEnable = 12;

// Motor B pins
const int motorBPin1      = 25; // 4
const int motorBPin2      = 26; // 5
const int motorBPinEnable = 13;

// PWM properties
const int freq            = 30000;
const int pwmChannel      = 0;
const int resolution      = 8;
const int dutyCycle       = 200; // 0 - 255

class Motors {
public:
  Motors();
  ~Motors();

  void setup();
  void forwards();
  void backwards();
  void stop();
};

// Motors implementation

Motors::Motors() {};

Motors::~Motors() {};

void Motors::setup() {
  // setup control pins
  pinMode(motorAPin1, OUTPUT);
  pinMode(motorAPin2, OUTPUT);
  pinMode(motorAPinEnable, OUTPUT);
  pinMode(motorBPin1, OUTPUT);
  pinMode(motorBPin2, OUTPUT);
  pinMode(motorBPinEnable, OUTPUT);

  // setup speed control
  ledcSetup(pwmChannel, freq, resolution);
  ledcAttachPin(motorAPinEnable, pwmChannel);
  ledcAttachPin(motorBPinEnable, pwmChannel);

  // set motor speed
  ledcWrite(pwmChannel, dutyCycle);
};

void Motors::forwards() {
  // Both motors forwards
  Serial.println("Forwards...");
  digitalWrite(motorAPin1, LOW);
  digitalWrite(motorAPin2, HIGH);

  digitalWrite(motorBPin1, LOW);
  digitalWrite(motorBPin2, HIGH);
};

void Motors::backwards() {
  // Both motors backwards
  Serial.println("Backwards...");
  digitalWrite(motorAPin1, HIGH);
  digitalWrite(motorAPin2, LOW);

  digitalWrite(motorBPin1, HIGH);
  digitalWrite(motorBPin2, LOW);
};

void Motors::stop() {
  // Both motors stop
  Serial.println("Stop...");
  digitalWrite(motorAPin1, LOW);
  digitalWrite(motorAPin2, LOW);

  digitalWrite(motorBPin1, LOW);
  digitalWrite(motorBPin2, LOW);
}

#endif /* __MOTORS_H__ */
