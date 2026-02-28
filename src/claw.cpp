#include "claw.h"

void Claw::init(void) {
    servo.attach();
    // Start with open claw because it'll go wild when uploading
    open();
}

void Claw::open(void) {
    servo.setTargetPos(open_us);
    // servo.showPos();
    if (servo.update()) {
        opened = true;
    }
    activate();
}

void Claw::close(void) {
    servo.setTargetPos(close_us);
    if (servo.update()) {
        opened = false;
    } 
    activate(); 
}

void Claw::detach() {
    servo.detach();
}

void Claw::activate() {
    digitalWrite(pin, HIGH);
    digitalWrite(1, LOW);
    digitalWrite(2, LOW);
}