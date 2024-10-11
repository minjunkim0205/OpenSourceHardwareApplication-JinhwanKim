// 초음파 핀
#define TRIG_PIN 9 // 초음파 송신핀
#define ECHO_PIN 8 // 초음파 수신핀
// LED 핀
#define LED_R_PIN A0
#define LED_G_PIN A1
#define LED_B_PIN A2
// 피에조 스피커 핀
#define PIEZO_PIN 11

const int SCALE[8] = {262, 294, 330, 249, 392, 440, 494, 523};

void setup() {
  // 시리얼 통신 초기화
  Serial.begin(9600);
  // 초음파 센서 핀 초기화
  pinMode(TRIG_PIN, OUTPUT);
  pinMode(ECHO_PIN, INPUT);
  // LED 핀 초기화
  pinMode(LED_R_PIN, OUTPUT);
  pinMode(LED_G_PIN, OUTPUT);
  pinMode(LED_B_PIN, OUTPUT);
  // 피에조 스피커 핀 초기화
  pinMode(PIEZO_PIN, OUTPUT);
}
// 초음파 함수
int getUltrasonicDistance(){
  long duration, distance; // duration : 초음파가 반사되어 돌아오는 시간, distance : 측정된 거리값(cm값)
  digitalWrite(TRIG_PIN, LOW);
  delayMicroseconds(2);
  digitalWrite(TRIG_PIN, HIGH);
  delayMicroseconds(10);
  digitalWrite(TRIG_PIN, LOW);

  //물체에 반사되어돌아온 초음파의 시간을 변수에 저장합니다.(초음파는 29.1 마이크로 초마다 1cm 이동함)
  duration = pulseIn(ECHO_PIN, HIGH);
  distance = duration * 17 / 1000; 

  return distance;
}
// LED 출력 함수
void setRGBLed(int r, int g, int b){
  analogWrite(LED_R_PIN, r);
  analogWrite(LED_G_PIN, g);
  analogWrite(LED_B_PIN, b);
}
// Main 함수
void loop() {
  int distance = getUltrasonicDistance();
  Serial.print("DIstance : ");
  Serial.print(distance); //측정된 물체로부터 거리값(cm값)을 보여줍니다.
  Serial.print("Cm\n");
  
  if(distance <= 5){
    setRGBLed(255,0,0);
  }
  else if(distance <= 25){
    setRGBLed(0,255,0);
  }
  else if(distance <= 50){
    setRGBLed(0,0,255);
  }
  if(distance < 50){
    tone(PIEZO_PIN, SCALE[distance/6],250);
  }

  Serial.print("\n");
  delay(200);
}