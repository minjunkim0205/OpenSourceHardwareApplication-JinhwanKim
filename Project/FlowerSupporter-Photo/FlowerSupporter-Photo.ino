#define POTENTIOMETER_PIN 12

void setup() {
  Serial.begin(9600);
  pinMode(POTENTIOMETER_PIN, OUTPUT);
}

void loop() {
  int value = analogRead(POTENTIOMETER_PIN);
  Serial.print(value);
  Serial.print("\n");
  //sleep(200);
}
