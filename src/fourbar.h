#ifndef FOURBAR_H
#define FOURBAR_H
#include "../lib/Servo32u4/src/servo32u4.h"

class FourBar {
    protected:
        uint16_t positions[4] = {1000, 1200, 1600, 2000};
    public:
        uint8_t pin = 2;
        Servo32U4Pin5 servo;
        void changePos(int targetPos);
        void init();
        void detach();
        void activate(void);
        uint8_t positionIndex = 0;
        bool posiitionReached = false;
};
#endif