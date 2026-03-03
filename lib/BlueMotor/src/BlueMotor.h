#pragma once
#include <Arduino.h>

class BlueMotor
{
public:
    BlueMotor();
    void move(bool clockwise);
    long getPosition();
    void reset();
    void setup();
    void stop();
    long encCount = 0;

private:
    static void isrB();
    static void isrA();
    const int tolerance = 3;
    const int OnPin = 1;
    const int AIN2 = 4;
    const int AIN1 = 11;
};