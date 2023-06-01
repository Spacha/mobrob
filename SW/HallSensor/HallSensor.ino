#define HALL_PIN 34

void setup() {
  Serial.begin(115200);

  pinMode(HALL_PIN, INPUT);
}

void loop() {
  uint16_t reading = analogRead(HALL_PIN);

  Serial.println(reading);

  delay(100);
}
