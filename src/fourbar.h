#ifndef FOURBAR_H
#define FOURBAR_H
#include "../lib/Servo32u4/src/servo32u4.h"

class FourBar {
    protected:
        uint16_t positions[4] = {1000, 1420, 1625, 2000};
    public:
        Servo32U4Pin5 servo;
        void changePos(int targetPos);
        void init();
        void detach();
        uint8_t positionIndex = 0;
        bool posiitionReached = false;
};
#endif