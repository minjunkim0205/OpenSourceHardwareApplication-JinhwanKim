#include <Stepper.h>

#define TOUCH_PIN 7
#define DEBOUNCE_TIME 100
#define STEPPER_IN01_PIN 11
#define STEPPER_IN02_PIN 10
#define STEPPER_IN03_PIN 9
#define STEPPER_IN04_PIN 8
#define STEPS 2048 // 360/11.25 = 32

Stepper stepper(STEPS, STEPPER_IN04_PIN, STEPPER_IN02_PIN, STEPPER_IN03_PIN, STEPPER_IN01_PIN);

void setup() {
  pinMode(TOUCH_PIN, INPUT);
  stepper.setSpeed(6); // Max 20
}

void loop() {
  if(digitalRead(TOUCH_PIN) == HIGH) {
    stepper.step(STEPS/360.0*90); // 90'
    delay(DEBOUNCE_TIME);
    while(digitalRead(TOUCH_PIN) == HIGH);
  }
}