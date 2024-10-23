/*라이브러리 불러오기*/
#include<Servo.h>

/*사용할 핀 정의*/
#define PHOTORESISTOR_PIN A0
#define PIEZO_PIN 11
#define BUTTON_PIN 12
#define LED_PIN 8
#define SERVO_PIN 10
#define TRIG_PIN 6 // 초음파 송신핀
#define ECHO_PIN 7 // 초음파 수신핀
#define RGB_LED_R_PIN A3
#define RGB_LED_G_PIN A4
#define RGB_LED_B_PIN A5

/*정의,고정상수*/
const int SCALE[8] = {262, 294, 330, 249, 392, 440, 494, 523}; // 피에조를 음계
Servo servo;

/*초기화*/
void setup() {
  // 레이트 9600으로 설정(시리얼통신)
  Serial.begin(9600);
  // 핀 초기화
  servo.attach(SERVO_PIN);
  pinMode(PIEZO_PIN, OUTPUT);
  pinMode(PHOTORESISTOR_PIN, INPUT);
  pinMode(BUTTON_PIN, INPUT);
  pinMode(LED_PIN, OUTPUT);
  pinMode(TRIG_PIN, OUTPUT);
  pinMode(ECHO_PIN, INPUT);
  pinMode(RGB_LED_R_PIN, OUTPUT);
  pinMode(RGB_LED_G_PIN, OUTPUT);
  pinMode(RGB_LED_B_PIN, OUTPUT);
}
/*함수*/
int getUltrasonicDistance(const int trig_pin, const int echo_pin){
  long duration, distance; // duration : 초음파가 반사되어 돌아오는 시간, distance : 측정된 거리값(cm값)
  digitalWrite(trig_pin, LOW);
  delayMicroseconds(2);
  digitalWrite(trig_pin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trig_pin, LOW);

  //물체에 반사되어돌아온 초음파의 시간을 변수에 저장합니다.
  duration = pulseIn(echo_pin, HIGH);
  distance = duration * 17 / 1000; 

  return distance;
}
void setRGBLed(int r, int g, int b){
  analogWrite(RGB_LED_R_PIN, r);
  analogWrite(RGB_LED_G_PIN, g);
  analogWrite(RGB_LED_B_PIN, b);
}
/*메인 루프*/
void loop() {
  // 조도 센서 값 받기(확인)
  int pho_value = analogRead(PHOTORESISTOR_PIN); // 밝을때 : 300 이하, 어두울때 : 600 이상
  Serial.print("조도센서 값 : ");
  Serial.println(pho_value);
  // 버튼 센서 값 받기(확인)
  int but_value = digitalRead(BUTTON_PIN);
  Serial.print("버튼 값 : ");
  Serial.println(but_value);
  // 초음파 센서 값 받기(확인)
  int ult_value = getUltrasonicDistance(TRIG_PIN, ECHO_PIN);
  Serial.print("DIstance : ");
  Serial.print(ult_value); //측정된 물체로부터 거리값(cm값)을 보여줍니다.
  Serial.println(" Cm");
  // 어두워지면
  if(pho_value >= 600){
    tone(PIEZO_PIN, SCALE[0],250);
    digitalWrite(LED_PIN, HIGH);
    servo.write(180);
  }
  else{
    digitalWrite(LED_PIN, LOW);
    servo.write(0);
  }
  // 만약 버튼이 눌린다면
  if(but_value){
    digitalWrite(LED_PIN, LOW);
  }
  // 사람이 가까이 다가오면
  if(ult_value < 10){
    setRGBLed(255,255,255);
  }
  else{
    setRGBLed(0, 0, 0);
  }
  delay(500);
}
