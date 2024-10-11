#define TRIG_PIN 9 // 초음파 송신핀
#define ECHO_PIN 8 // 초음파 수신핀

void setup() {
  // 시리얼 통신 초기화
  Serial.begin(9600);
  // 핀 초기화
  pinMode(TRIG_PIN, OUTPUT);
  pinMode(ECHO_PIN, INPUT);
}

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

void loop() {
  Serial.print("DIstance : ");
  Serial.print(getUltrasonicDistance(TRIG_PIN, ECHO_PIN)); //측정된 물체로부터 거리값(cm값)을 보여줍니다.
  Serial.println(" Cm");

  delay(100); //1초마다 측정값을 보여줍니다.
}
