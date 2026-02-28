#ifndef CLAW_H
#define CLAW_H
#include "../lib/Servo32u4/src/servo32u4.h"

class Claw {
    protected:
        Servo32U4Pin12 servo;
        uint16_t open_us = 1200;
        uint16_t close_us = 1700;
    public:
        uint8_t pin = 3;
        bool opened = false;
        void init(void);
        void detach(void);
        void open(void);
        void close(void);
        void activate(void);
};
#endif