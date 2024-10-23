#define PHOTORESISTOR A3
#define PIEZO 7
#define PIN_R A2
#define PIN_G A1
#define PIN_B A0

const int SCALE[8] = {262, 294, 330, 249, 392, 440, 494, 523}; // 피에조를 음계

void setRGBLed(int r, int g, int b){
  analogWrite(PIN_R, r);
  analogWrite(PIN_G, g);
  analogWrite(PIN_B, b);
}

void setup(){
  Serial.begin(9600);
  pinMode(PHOTORESISTOR, INPUT);
  pinMode(PIEZO, OUTPUT);
  pinMode(PIN_R, OUTPUT);
  pinMode(PIN_G, OUTPUT);
  pinMode(PIN_B, OUTPUT);
}

void loop() {
  if(analogRead(PHOTORESISTOR) > 350){
    setRGBLed(255, 0, 0);
  }
  else{
    setRGBLed(0, 0, 0);
    tone(PIEZO, SCALE[3], 250);
    delay(500);
  }
}
