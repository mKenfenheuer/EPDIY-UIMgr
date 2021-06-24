#ifndef _EPD_UI_BUTTON_DEF
#define _EPD_UI_BUTTON_DEF

#include "UIElement.h"
#include "DisplayHighlevel.h"

class UIButton : public UIElement
{
public:
    UIButton(UIManager *manager, UIPoint location)
    {
        this->manager = manager;
        this->location = location;
        this->manager->registerElement(this);
    }
    ~UIButton() {}

    bool handleTouch(UIPoint point)
    {
        this->handler(this);
        return true;
    }

    void drawUI(DisplayHighlevel *display)
    {
        
    }
};

#endif
