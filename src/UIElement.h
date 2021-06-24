#ifndef _EPD_UI_ELEMENT_DEF
#define _EPD_UI_ELEMENT_DEF

#include "UIManager.fwd.h"
#include "UIPoint.h"
#include "DisplayHighlevel.h"

class UIElement
{
public:
    UIPoint location;
    UIManager *manager = nullptr;
    String text;
    void (*handler)(UIElement *) = nullptr;

    virtual bool handleTouch(UIPoint point)
    {
        return false;
    }
    virtual void drawUI(DisplayHighlevel *display) {}

    void setUIManager(UIManager *manager)
    {
        this->manager = manager;
    }

    void setOnClickHandler(void (*handler)(UIElement *))
    {
        this->handler = handler;
    }

    void setText(String text)
    {
        this->text = text;
    }

    void setLocation(UIPoint location)
    {
        this->location = location;
    }

    String getText()
    {
        return text;
    }

    UIPoint GetLocation()
    {
        return location;
    }
};

#endif
