#define PIN_3A 25

void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200);

  pinMode(PIN_3A, OUTPUT);
}

void loop() {
  // put your main code here, to run repeatedly:
  digitalWrite(PIN_3A, HIGH);
  delay(5000);

  digitalWrite(PIN_3A, LOW);
  delay(5000);
}
