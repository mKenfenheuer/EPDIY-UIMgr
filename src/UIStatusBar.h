#ifndef _EPD_UI_STATUS_BAR_DEF
#define _EPD_UI_STATUS_BAR_DEF

#include "UIElement.h"
#include "DisplayHighlevel.h"
#include "UIManager.h"
#include "Arduino.h"

class UIStatusBar : public UIElement
{
private:
    String leftText;
    String centerText;
    String rightText;

public:
    UIStatusBar(UIManager *manager, UIPoint location)
    {
        this->manager = manager;
        this->location = location;
        this->manager->registerElement((UIElement *)this);
    }
    UIStatusBar() {}
    ~UIStatusBar() {}

    bool handleTouch(UIPoint point) override
    {
        return false;
    }

    void setLeftText(String text)
    {
        leftText = text;
    }

    void setRightText(String text)
    {
        rightText = text;
    }

    void setCenterText(String text)
    {
        centerText = text;
    }

    void drawUI(DisplayHighlevel *display) override
    {
        display->drawLine(UIPoint(location.getX(), location.getY() + 30), UIPoint(location.getX() + display->width(), location.getY() + 30), 0);
        display->drawLine(UIPoint(location.getX(), location.getY() + 31), UIPoint(location.getX() + display->width(), location.getY() + 31), 0);
        display->drawTextRightAligned(rightText.c_str(), UIPoint(location.getX() + display->width() - 5, location.getY() + 23), 0);
        display->drawTextCenterAligned(centerText.c_str(), UIPoint(location.getX() + display->width() / 2, location.getY() + 23), 0);
        display->drawTextLeftAligned(leftText.c_str(), UIPoint(location.getX() + 5, location.getY() + 23), 0);
    }
};

#endif
