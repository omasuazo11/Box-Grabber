#ifndef CLAW_H
#define CLAW_H
#include "../lib/Servo32u4/src/servo32u4.h"

class Claw {
    protected:
        Servo32U4Pin12 servo;
        uint16_t open_us = 1120;
        uint16_t close_us = 1300;
    public:
        
        bool opened = false;
        void init(void);
        void detach(void);
        void open(void);
        void close(void);
};
#endif