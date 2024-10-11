#include<Servo.h>

// 서보 모터 핀
#define SERVO_PIN 10
// 가변 저항 핀
#define POTENTIOMETER_PIN A0

Servo servo;

void setup() {
  Serial.begin(9600);
  servo.attach(SERVO_PIN);
  pinMode(POTENTIOMETER_PIN, OUTPUT);
}
 
void loop() {
  int value = analogRead(POTENTIOMETER_PIN);
  Serial.print(value);
  Serial.print("\n");

  servo.write(map(value, 0, 1024, 0, 180));
  delay(200);
}