#include <Servo.h>

Servo leftFoot;
Servo leftLeg;
Servo rightFoot;
Servo rightLeg;

#define pinLeftLeg 2
#define pinLeftFoot 4
#define pinRightLeg 3
#define pinRightFoot 5

#define neutralLeftLeg 90
#define neutralLeftFoot 90
#define neutralRightLeg 90
#define neutralRightFoot 90

#define strideAngle 60
#define liftAngle 30
#define step_Delay 1

void setup() {
  leftLeg.attach(pinLeftLeg);
  leftFoot.attach(pinLeftFoot);
  rightLeg.attach(pinRightLeg);
  rightFoot.attach(pinRightFoot);

  leftLeg.write(neutralLeftLeg);
  rightLeg.write(neutralRightLeg);
  leftFoot.write(neutralLeftFoot);
  rightFoot.write(neutralRightFoot);

  delay(500);
}

void smoothMove(Servo &servo, int targetAngle, int stepDelay) {
  int currentAngle = servo.read();

  if (currentAngle < targetAngle) {
    for (int angle = currentAngle; angle <= targetAngle; angle++) {
      servo.write(angle);
      delay(stepDelay);
    }
  } else {
    for (int angle = currentAngle; angle >= targetAngle; angle--) {
      servo.write(angle);
      delay(stepDelay);
    }
  }
}

void smoothMoveMultiple(Servo &servo1, int target1, Servo &servo2, int target2, Servo &servo3, int target3, Servo &servo4, int target4, int stepDelay) {
  int current1 = servo1.read();
  int current2 = servo2.read();
  int current3 = servo3.read();
  int current4 = servo4.read();

  int diff1 = abs(target1 - current1);
  int diff2 = abs(target2 - current2);
  int diff3 = abs(target3 - current3);
  int diff4 = abs(target4 - current4);

  int maxSteps = max(max(diff1, diff2), max(diff3, diff4));

  for (int step = 0; step <= maxSteps; step++) {
    float progress= (float)step / maxSteps;

    servo1.write(current1 + (target1 - current1) * progress);
    servo2.write(current2 + (target2 - current2) * progress);
    servo3.write(current3 + (target3 - current3) * progress);
    servo4.write(current4 + (target4 - current4) * progress);

    delay(stepDelay);
  }
}

void walkGait() {
  smoothMoveMultiple(leftFoot, neutralLeftFoot + liftAngle, rightFoot, neutralRightFoot, leftLeg, neutralLeftLeg, rightLeg, neutralRightLeg, step_Delay);
  smoothMove(leftLeg, neutralLeftLeg + strideAngle, step_Delay);
  smoothMove(leftFoot, neutralLeftFoot, step_Delay);

  smoothMoveMultiple(leftFoot, neutralLeftFoot, rightFoot, neutralRightFoot + liftAngle, leftLeg, neutralLeftLeg + strideAngle, rightLeg, neutralRightLeg, step_Delay);
  smoothMove(rightLeg, neutralRightLeg + strideAngle, step_Delay);
  smoothMove(rightFoot, neutralRightFoot, step_Delay);

  smoothMoveMultiple(leftLeg, neutralLeftLeg, rightLeg, neutralLeftLeg, leftFoot, neutralLeftFoot, rightFoot, neutralRightFoot, step_Delay);
}

void loop() {
  walkGait();

  delay(200);
}
