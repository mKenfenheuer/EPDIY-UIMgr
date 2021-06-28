#ifndef _EPD_UI_SWITCH_DEF
#define _EPD_UI_SWITCH_DEF

#include "UIElement.h"
#include "DisplayHighlevel.h"
#include "UIManager.h"

class UISwitch : public UIElement
{
private:
    bool state = false;
    int display_width = 26 * 2 + 60;
    int display_height = 26 * 2 + 31;

public:
    UISwitch(UIManager *manager, UIPoint location)
    {
        this->manager = manager;
        this->location = location;
        this->manager->registerElement((UIElement *)this);
    }
    UISwitch() {}
    ~UISwitch() {}

    bool handleTouch(UIPoint point) override
    {
        printf("Check Touch\n");
        if (point.getX() - location.getX() >= 0 &&
            point.getX() - location.getX() <= display_width)

            if (point.getY() - location.getY() >= 0 &&
                point.getY() - location.getY() <= display_height)
            {
                printf("Touch matched.\n");
                state = !state;
                if (handler != nullptr)
                {
                    printf("Calling Handler\n");
                    handler(this);
                }
                return true;
            }
        return false;
    }

    bool
    getState()
    {
        return state;
    }

    void setState(bool state)
    {
        this->state = state;
    }

    void drawUI(DisplayHighlevel *display) override
    {
        Serial.printf("Drawing at: %ld,%ld\n", location.getX(), location.getY());

        UIPoint leftCenter = UIPoint(location.getX() + 26, location.getY() + 26);

        display->fillCircle(UIPoint(leftCenter.getX(), leftCenter.getY()), 15, 0);
        display->fillCircle(UIPoint(leftCenter.getX() + 60, leftCenter.getY()), 15, 0);

        display->fillCircle(UIPoint(leftCenter.getX(), leftCenter.getY()), 13, 255);
        display->fillCircle(UIPoint(leftCenter.getX() + 60, leftCenter.getY()), 13, 255);

        display->fillRect(UIPoint(leftCenter.getX(), leftCenter.getY() - 15), 60, 31, 0);
        display->fillRect(UIPoint(leftCenter.getX(), leftCenter.getY() - 13), 60, 27, 255);

        if (state)
        {
            display->fillCircle(UIPoint(leftCenter.getX() + 60, leftCenter.getY()), 26, 0);
        }
        else
        {
            display->fillCircle(UIPoint(leftCenter.getX(), leftCenter.getY()), 26, 0);
            display->fillCircle(UIPoint(leftCenter.getX(), leftCenter.getY()), 24, 255);
        }
    }
};

#endif
