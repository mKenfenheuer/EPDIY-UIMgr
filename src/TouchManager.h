#ifndef _EPD_TOUCH_MANAGER_DEF
#define _EPD_TOUCH_MANAGER_DEF
#include "epd_driver.h"
#include "TouchCalibration.h"

enum TouchRotation
{
    TOUCH_ROT_LANDSCAPE = 0,
    TOUCH_ROT_PORTRAIT = 1,
    TOUCH_ROT_INVERTED_LANDSCAPE = 2,
    TOUCH_ROT_INVERTED_PORTRAIT = 3,
};

class TouchManager
{
public:
    uint32_t touch_width = 0;
    uint32_t touch_height = 0;

    TouchRotation rotation = TOUCH_ROT_LANDSCAPE;

    TouchCalibration *calibration = nullptr;

    void (*handler)(UIPoint) = nullptr;
    
    void setTouchDimension(uint32_t width, uint32_t height)
    {
        this->touch_width = width;
        this->touch_height = height;
    }

    void setTouchHandler(void (*handler)(UIPoint))
    {
        this->handler = handler;
    }

    void setTouchCalibration(TouchCalibration *calibration)
    {
        this->calibration = calibration;
    }

    void setRotation(TouchRotation rotation)
    {
        this->rotation = rotation;
    }

    UIPoint rotateTouch(UIPoint point)
    {
        if (touch_height == 0 ||
            touch_width == 0)
            return point;

        uint32_t x = point.getX();
        uint32_t y = point.getY();

        switch (rotation)
        {
        case TOUCH_ROT_LANDSCAPE:
            x = x;
            y = touch_height - y;
            break;

        case TOUCH_ROT_PORTRAIT:
            x = touch_height - y;
            y = touch_width - x;
            break;

        case TOUCH_ROT_INVERTED_PORTRAIT:
            x = y;
            y = x;
            break;

        case TOUCH_ROT_INVERTED_LANDSCAPE:
            x = touch_width - x;
            y = y;
            break;
        default:
            break;
        }
        return UIPoint(x, y);
    }
};

#endif