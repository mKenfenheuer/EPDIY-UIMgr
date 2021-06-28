#ifndef _EPD_UI_SENSOR_STATUS_DEF
#define _EPD_UI_SENSOR_STATUS_DEF

#include "UIElement.h"
#include "DisplayHighlevel.h"
#include "UIManager.h"
#include "Arduino.h"

class UISensorStatus : public UIElement
{
private:
    String sensorName;
    String sensorValue;

public:
    UISensorStatus(UIManager *manager, UIPoint location)
    {
        this->manager = manager;
        this->location = location;
        this->manager->registerElement((UIElement *)this);
    }
    UISensorStatus() {}
    ~UISensorStatus() {}

    bool handleTouch(UIPoint point) override
    {
        return false;
    }

    void setSensorName(String text)
    {
        sensorName = text;
    }

    void setSensorValue(String text)
    {
        sensorValue = text;
    }

    void drawUI(DisplayHighlevel *display) override
    {

        display->drawLine(UIPoint(location.getX(), location.getY()), UIPoint(location.getX() + display->width(), location.getY()), 0);
        display->drawLine(UIPoint(location.getX(), location.getY() + 1), UIPoint(location.getX() + display->width(), location.getY() + 1), 0);

        display->setFont(&OpenSans12B);
        display->drawTextLeftAligned(value.display_name.c_str(), UIPoint(location.getX() + 10, location.getY() + 57), 0);
        display->setFont(&OpenSans16B);
        display->drawTextRightAligned((value.state + " " + value.unit_of_measurement).c_str(), UIPoint(location.getX() + display->width() - 10 - 5, location.getY() + 57), 0);

        display->drawLine(UIPoint(location.getX(), location.getY() + 93), UIPoint(location.getX() + display->width(), location.getY() + 93), 0);
        display->drawLine(UIPoint(location.getX(), location.getY() + 94), UIPoint(location.getX() + display->width(), location.getY() + 94), 0);
    }
};

#endif
