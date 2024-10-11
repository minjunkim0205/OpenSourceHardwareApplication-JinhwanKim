#define SERVO_PIN 10

#include<Servo.h> //Servo 라이브러리를 추가
Servo servo;      //Servo 클래스로 servo객체 생성

void setup() {
  Serial.begin(9600);
  servo.attach(SERVO_PIN);
}
 
void loop() {
  for(int i = 0; i <= 180; i++){
    servo.write(i);
    delay(20);
  }
  delay(1000);
  for(int i = 180; i >= 0; i--){
    servo.write(i);
    delay(20);
  }
  delay(1000);
}