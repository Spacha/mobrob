/***************************************************
 * Simple motor control demo for ESP32
 ***************************************************
 * Author: Miika Sikala, 2023
 *
 * Does things. Or not, I don't know.
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
 *        (2)---o-| D32  |2|  D19 |-o
 *        (1)---o-| D33       D18 |-o
 *       (10)---o-| D25       D5  |-o
 *        (9)---o-| D26       TX2 |-o
 *              o-| D27       RX2 |-o
 *              o-| D14       D4  |-o
 *        (7)---o-| D12       D2  |-o
 *       (15)---o-| D13       D15 |-o
 *      (GND)---o-| GND       GND |-o
 *       (5V)---o-| VIN       3V3 |-o
 *                \---------------/
 *
 ***************************************************
 * EN  3A  4A
 * 1   1   0     forwards
 * 1   0   1     backwards
 *
 * EN  1A  2A
 * 1   1   0     forwards
 * 1   0   1     backwards
 */

// Motor A pins
const int motorA_en   = 26;
const int motorA_1    = 25;
const int motorA_2    = 13;

// Motor B pins
const int motorB_en   = 33;
const int motorB_1    = 32;
const int motorB_2    = 12;

void setup() {
  // setup control pins
  pinMode(motorA_en, OUTPUT);
  pinMode(motorA_1, OUTPUT);
  pinMode(motorA_2, OUTPUT);
  pinMode(motorB_en, OUTPUT);
  pinMode(motorB_1, OUTPUT);
  pinMode(motorB_2, OUTPUT);

  // setup speed control
  //ledcSetup(pwmChannel, freq, resolution);
  //ledcAttachPin(motorAPinEnable, pwmChannel);
  //ledcAttachPin(motorBPinEnable, pwmChannel);

  Serial.begin(9600);
  Serial.println("Starting operation...");
}

void loop() {

  delay(5000);

  analogWrite(motorA_en, 0);
  analogWrite(motorB_en, 0);
  delay(500);

  // forwards
  digitalWrite(motorA_1, HIGH);
  digitalWrite(motorA_2, LOW);

  // forwards
  digitalWrite(motorB_1, HIGH);
  digitalWrite(motorB_2, LOW);

  //digitalWrite(motorA_en, HIGH);
  //digitalWrite(motorB_en, HIGH);
  analogWrite(motorA_en, 180);
  analogWrite(motorB_en, 180);

  delay(5000);

  //digitalWrite(motorA_en, LOW);
  //digitalWrite(motorB_en, LOW);

  analogWrite(motorA_en, 0);
  analogWrite(motorB_en, 0);
  delay(500);

  // backwards
  digitalWrite(motorA_1, LOW);
  digitalWrite(motorA_2, HIGH);

  // backwards
  digitalWrite(motorB_1, LOW);
  digitalWrite(motorB_2, HIGH);

  //digitalWrite(motorA_en, HIGH);
  //digitalWrite(motorB_en, HIGH);
  analogWrite(motorA_en, 180);
  analogWrite(motorB_en, 180);
  
  //while (1) {}
  // set motor speed
  //ledcWrite(pwmChannel, dutyCycle);

  //motorsForwards();
  //delay(1000);

  // motorsStop();
  // delay(1000);

  // motorsBackwards();
  // delay(1000);

  // motorsStop();
  // delay(1000);
}
