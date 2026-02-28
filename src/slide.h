#ifndef SLIDE_H
#define SLIDE_H
#include "../lib/Servo32u4/src/servo32u4.h"

class Slide {
    protected:
        Servo32U4Pin13 servo;
        uint16_t forward_us = 1600;
        uint16_t backward_us = 1400;
        uint16_t stop_us = 1500;
        uint8_t diameter = 12;
        float rps_est = 0.33;
        
    public:
        uint8_t pin = 1;
        void init(void);
        void detach(void);
        void moveDist(int distance);
        void activate(void);
        bool positionReached = false;
        float currentPosition = 0;
        int currentIndex = 0;
        int slideMovements[6] = {25, -10, 42, -10, 72, -10};
};
#endif