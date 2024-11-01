#define TOUCH_PIN 7
#define DEBOUNCE_TIME 100

void setup() {
  Serial.begin (9600);
  pinMode(TOUCH_PIN, INPUT);
}

void loop() {
  if(digitalRead(TOUCH_PIN) == HIGH) {
    Serial.println("1");
    delay(DEBOUNCE_TIME);
    while(digitalRead(TOUCH_PIN) == HIGH);
  }
}