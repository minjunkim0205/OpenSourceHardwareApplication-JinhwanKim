#include <Stepper.h>

#define STEPPER_IN01_PIN 11
#define STEPPER_IN02_PIN 10
#define STEPPER_IN03_PIN 9
#define STEPPER_IN04_PIN 8
#define STEPS 2048 // 360/11.25 = 32

Stepper stepper(STEPS, STEPPER_IN04_PIN, STEPPER_IN02_PIN, STEPPER_IN03_PIN, STEPPER_IN01_PIN);

void setup() {
  stepper.setSpeed(12); // Max 20
}

void loop() {
  for(int i = 0; i < 4; i++){ // 90', 4 time
    stepper.step(STEPS/360.0*90);
    delay(1000);
  }
}