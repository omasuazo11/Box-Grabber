#include "slide.h"

void Slide::init(void) {
    motor.setup();
}

void Slide::moveDist(int movementIndex) {
    int distance = slideMovements[movementIndex];
    if (distance < 0) {
        motor.move(true);
    } else {
        motor.move(false);
    }
    currentPosition += (float) 3.14 * diameter * rps_est * 20 / (1000);
    if (currentPosition > abs(distance)) {
        // Stop the motor when target distance is reached
        motor.stop();
        positionReached = true;
        currentPosition = 0;
    }
}