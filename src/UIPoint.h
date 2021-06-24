#ifndef _EPD_UI_POINT_DEF
#define _EPD_UI_POINT_DEF

#include <Arduino.h>

class UIPoint
{
private:
    uint32_t x = 0;
    uint32_t y = 0;

public:
    UIPoint(uint32_t x, uint32_t y)
    {
        this->x = x;
        this->y = y;
    }
    UIPoint() {}
    ~UIPoint() {}
    uint32_t getX()
    {
        return x;
    }
    uint32_t getY()
    {
        return y;
    }
};

#endif