#ifndef _EPD_UI_POINT_DEF
#define _EPD_UI_POINT_DEF

#include <Arduino.h>

class UIPoint
{
private:
    long x = 0;
    long y = 0;

public:
    UIPoint(long x, long y)
    {
        this->x = x;
        this->y = y;
    }
    UIPoint() {}
    ~UIPoint() {}
    long getX()
    {
        return x;
    }
    long getY()
    {
        return y;
    }
};

#endif