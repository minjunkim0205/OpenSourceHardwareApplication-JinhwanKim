#define POTENTIOMETER_PIN A0

void setup() {
  Serial.begin(9600);
  pinMode(POTENTIOMETER_PIN, OUTPUT);
}

void loop() {
  int value = analogRead(POTENTIOMETER_PIN);
  Serial.print(value);
  Serial.print("\n");
}
