#include <Arduino.h>
#include "./BlueMotor.h"
#include <Romi32U4.h>

long oldValue = 0;
long newValue;
volatile long count = 0;
volatile long prevAState = 1;
volatile long prevBState = 1;
volatile long prevTimeA = 0;
volatile long prevTimeB = 0;
unsigned time = 0;
const int ENCA = 2;
const int ENCB = 3;

BlueMotor::BlueMotor()
{
}

void BlueMotor::setup()
{
    pinMode(OnPin, OUTPUT);
    pinMode(AIN2, OUTPUT);
    pinMode(AIN1, OUTPUT);
    pinMode(ENCA, INPUT);
    pinMode(ENCB, INPUT);

    attachInterrupt(digitalPinToInterrupt(ENCA), isrA, CHANGE);
    attachInterrupt(digitalPinToInterrupt(ENCB), isrB, CHANGE);
    reset();
}

long BlueMotor::getPosition()
{
    long tempCount = 0;
    noInterrupts();
    tempCount = count;
    interrupts();
    return tempCount;
}

void BlueMotor::reset()
{
    noInterrupts();
    count = 0;
    interrupts();
}


void BlueMotor::isrA()
{
    if (prevAState == 0) {
        prevAState = 1;
        if (prevBState == 0) {
            count++;
        } else {
            count--;
        }
    } else {
        prevAState = 0;
        if (prevBState == 1) {
            count++;
        } else {
            count--;
        }
    }
}

void BlueMotor::isrB() {
    if (prevBState == 0) {
        prevBState = 1;
        if (prevAState == 1) {
            count++;
        } else {
            count--;
        }
    } else {
        prevBState = 0;
        if (prevAState == 0) {
            count++;
        } else {
            count--;
        }
    }
}
void BlueMotor::move(bool clockwise)
{
    // if (encCount % 2 == 0) {
    //     digitalWrite(OnPin, HIGH);
    // } else {
    //     digitalWrite(OnPin, LOW);
    // }
    // encCount++;
    digitalWrite(OnPin, HIGH);
    if (clockwise)
    {
        digitalWrite(AIN1, HIGH);
        digitalWrite(AIN2, LOW);
    }
    else
    {
        digitalWrite(AIN1, LOW);
        digitalWrite(AIN2, HIGH);
    }
}

void BlueMotor::stop() {
    // if (encCount % 2 == 1) {
    //     encCount++;
    // }
    digitalWrite(OnPin, LOW);
    digitalWrite(AIN1, LOW);
    digitalWrite(AIN2, LOW);
}