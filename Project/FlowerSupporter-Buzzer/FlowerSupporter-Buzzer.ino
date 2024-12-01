// 피에조 스피커 핀
#define PIEZO_PIN 13

const int SCALE[8] = {262, 294, 330, 249, 392, 440, 494, 523};

void setup() {
  // 피에조 스피커 핀 초기화
  pinMode(PIEZO_PIN, OUTPUT);
}

// Main 함수
void loop() {
  tone(PIEZO_PIN, SCALE[0],250);
  delay(1000);
  tone(PIEZO_PIN, SCALE[3],250);
  delay(1000);
  tone(PIEZO_PIN, SCALE[6],250);
  delay(1000);
}