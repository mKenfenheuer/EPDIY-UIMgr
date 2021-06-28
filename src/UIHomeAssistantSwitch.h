#ifndef _EPD_UI_HOME_ASSISTANT_SWITCH_DEF
#define _EPD_UI_HOME_ASSISTANT_SWITCH_DEF

#include "UIElement.h"
#include "DisplayHighlevel.h"
#include "UIManager.h"
#include "UISwitch.h"

class UIHomeAssistantSwitch : public UIElement
{
private:
    bool state = false;
    int display_width = 26 * 2 + 60;
    int display_height = 26 * 2 + 31;
    int swXOff = 0;
    int swYOff = 0;
    String switchName;

public:
    UIHomeAssistantSwitch(UIManager *manager, UIPoint location)
    {
        this->manager = manager;
        this->location = location;
        this->manager->registerElement((UIElement *)this);
    }
    UIHomeAssistantSwitch() {}
    ~UIHomeAssistantSwitch() {}

    void setLocation(UIPoint location)
    {
        this->location = location;
    }

    void registerWithManager(UIManager *manager)
    {
        if (this->manager == nullptr)
            this->manager = manager;
        manager->registerElement((UIElement *)this);
    }

    bool handleTouch(UIPoint point) override
    {
        if (point.getX() - (location.getX() + swXOff) >= 0 &&
            point.getX() - (location.getX() + swXOff) <= display_width)

            if (point.getY() - (location.getY() + swYOff) >= 0 &&
                point.getY() - (location.getY() + swYOff) <= display_height)
            {
                state = !state;
                if (handler != nullptr)
                {
                    handler(this);
                }
                return true;
            }
        return false;
    }

    bool getState()
    {
        return state;
    }

    void setState(bool state)
    {
        this->state = state;
    }

    void setSwitchName(String name)
    {
        this->switchName = name;
    }

    void drawUI(DisplayHighlevel *display) override
    {
        swXOff = display->width() - display_width - 5;
        swYOff = 93 / 2;

        UIPoint leftCenter = UIPoint(swXOff + location.getX(), swYOff + location.getY());

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

        display->drawTextLeftAligned(switchName.c_str(), UIPoint(location.getX() + 10, location.getY() + 57), 0);
    }
};

#endif
