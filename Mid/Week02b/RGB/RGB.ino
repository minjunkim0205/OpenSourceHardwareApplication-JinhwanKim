#define PIN_R 9
#define PIN_G 10
#define PIN_B 11

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
  int r = random(0, 3);
  Serial.println(r);
  for(int i = 255; i>=0; i--){
    switch (r) {
      case 0:
        setRGBLed(i, 0, 0);
      case 1:
        setRGBLed(0, i, 0);
      case 2:
        setRGBLed(0, 0, i);
    }
    delay(2);
  }
}
