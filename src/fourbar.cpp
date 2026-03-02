#include "fourbar.h"

void FourBar::init() {
    servo.attach();
    // Start motor in claw lowered position
    // changePos(0);
}

void FourBar::changePos(int targetPos) {
    servo.setTargetPos(positions[targetPos]);
    if (servo.update()) {
        posiitionReached = true;
    }
    // servo.showPos();
}

void FourBar::detach(void) {
    servo.detach();
}