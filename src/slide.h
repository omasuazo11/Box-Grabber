#ifndef SLIDE_H
#define SLIDE_H
#include "../lib/BlueMotor/src/BlueMotor.h"

class Slide {
    protected:
        float const rps_est = 0.4;
        float currentPosition = 0;
        float diameter = 12.0;
        
    public:
        BlueMotor motor;
        void init(void);
        void moveDist(int distance);
        bool positionReached = false;
        int currentIndex = 0;
        int slideMovements[7] = {45, -40, 52, -30, 82, -30, -25};
};
#endif