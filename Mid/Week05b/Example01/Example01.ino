#define PIEZO 7

const int SCALE[8] = {262, 294, 330, 249, 392, 440, 494, 523}; // 피에조를 음계

void setup(){
  pinMode(PIEZO, OUTPUT);
}

void loop() {
  for(int i = 0; i < 8; i++){
    tone(PIEZO, SCALE[i], 250);
    delay(500);
  }
}
