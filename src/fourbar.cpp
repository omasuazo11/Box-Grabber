#include "fourbar.h"

void FourBar::init() {
    servo.attach();
    Serial.println("GETS HERE");
    // Start motor in claw lowered position
    changePos(0);
}

void FourBar::changePos(int targetPos) {
    servo.setTargetPos(positions[targetPos]);
    if (servo.update()) {
        posiitionReached = true;
    }
    activate();
    // servo.showPos();
}

void FourBar::detach(void) {
    servo.detach();
}

void FourBar::activate(void) {
    digitalWrite(pin, HIGH);
    digitalWrite(1, LOW);
    digitalWrite(3, LOW);
}