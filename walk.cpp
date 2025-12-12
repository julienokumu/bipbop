#include <Servo.h>

Servo leftLeg;
Servo leftFoot;
Servo rightLeg;
Servo rightFoot;

#define pinLeftLeg 2
#define pinLeftFoot 4
#define pinRightLeg 3
#define pinRightFoot 5

#define neutralLeftLeg 90
#define neutralLeftFoot 90
#define neutralRightLeg 90
#define neutralRightFoot 90

void setup() {
  leftLeg.attach(pinLeftLeg);
  leftFoot.attach(pinLeftFoot);
  rightLeg.attach(pinRightLeg);
  rightFoot.attach(pinRightFoot);

  leftLeg.write(neutralLeftLeg);
  leftFoot.write(neutralLeftFoot);
  rightLeg.write(neutralRightLeg);
  rightFoot.write(neutralRightFoot);

  delay(1000);
}

void walk(int steps) {
  for (int i = 0; i < steps; i++) {
    leftFoot.write(110);
    rightFoot.write(70);
    delay(100);

    leftLeg.write(110);
    delay(100);

    leftFoot.write(70);
    rightFoot.write(110);
    delay(100);

    rightLeg.write(70);
    delay(100);

    leftFoot.write(neutralLeftFoot);
    rightFoot.write(neutralRightFoot);
    delay(100);

    leftLeg.write(neutralLeftLeg);
    rightLeg.write(neutralRightLeg);
    delay(100);
  }
}

void loop() {
  walk(4);
  delay(100);
}
