#ifndef SLIDE_H
#define SLIDE_H
#include "../lib/BlueMotor/src/BlueMotor.h"

class Slide {
    protected:
        BlueMotor motor;
        uint16_t forward_us = 1200;
        uint16_t backward_us = 1800;
        uint16_t stop_us = 1500;
        float conversionFactor = 540 / (PI * 12);
        
    public:
        uint8_t pin = 2;
        void init(void);
        void moveDist(int distance);
        bool positionReached = false;
        int currentIndex = 0;
        long slideMovements[6] = {25*conversionFactor, -15*conversionFactor, 48*conversionFactor, -38*conversionFactor, 119*conversionFactor, -109*conversionFactor};
};
#endif