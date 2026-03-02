#include "slide.h"

void Slide::init(void) {
    motor.setup();
}

void Slide::moveDist(int movementIndex) {
    long distance = slideMovements[movementIndex];
    if (distance > 0) {
        motor.move(true);
    } else {
        motor.move(false);
    }
    if (motor.encCount > abs(distance)) {
        // Stop the motor when target distance is reached
        motor.stop();
        positionReached = true;
    }
}