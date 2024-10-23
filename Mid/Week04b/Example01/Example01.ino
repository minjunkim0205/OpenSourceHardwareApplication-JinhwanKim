#define PIN_R A2
#define PIN_G A1
#define PIN_B A0
#define BUTTON 8

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
  pinMode(BUTTON, INPUT);
}

int state = 0;

void loop() {
  if(digitalRead(BUTTON)){
    state = state + 1;
    state = state%4;
    while(digitalRead(BUTTON)!=0);
  }
  switch (state) {
  case 0:
    setRGBLed(0, 0, 0);
    break;
  case 1:
    setRGBLed(255, 0, 0);
    break;
  case 2:
    setRGBLed(0, 255, 0);
    break;
  case 3:
    setRGBLed(0, 0, 255);
    break;
  }
}
