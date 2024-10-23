#define PIN_R A2
#define PIN_G A1
#define PIN_B A0

void setRGBLed(int r, int g, int b){
  analogWrite(PIN_R, r);
  analogWrite(PIN_G, g);
  analogWrite(PIN_B, b);
}

void setup() {
  Serial.begin(9600);
  pinMode(PIN_R, OUTPUT);
  pinMode(PIN_G, OUTPUT);
  pinMode(PIN_B, OUTPUT);
}

void loop() {
  setRGBLed(255, 0, 0);
  delay(100);
  setRGBLed(0, 255, 0);
  delay(100);
  setRGBLed(0, 0, 255);
  delay(100);
}
