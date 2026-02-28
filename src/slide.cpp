#include "slide.h"

void Slide::init(void) {
    servo.attach();
    servo.setTargetPos(stop_us);
    servo.update();
    servo.update();
    servo.update();
}

void Slide::detach(void) {
    servo.detach();
}

void Slide::moveDist(int movementIndex) {
    int distance = slideMovements[movementIndex];
    if (distance > 0) {
        servo.setTargetPos(forward_us);
    } else {
        servo.setTargetPos(backward_us);
    }
    servo.update();
    activate();
    currentPosition += (float) 3.14 * diameter * rps_est * 20 / (1000);
    Serial.println(currentPosition);
    if (currentPosition > abs(distance)) {
        // Stop the servo when target distance is reached
        servo.setTargetPos(stop_us);
        servo.update();
        servo.update();
        servo.update();
        positionReached = true;
        currentPosition = 0;
    }
}

void Slide::activate(void) {
    digitalWrite(pin, HIGH);
    digitalWrite(2, LOW);
    digitalWrite(3, LOW);
}