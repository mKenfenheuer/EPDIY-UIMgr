#ifndef _EPD_UI_MANAGER_DEF
#define _EPD_UI_MANAGER_DEF

#include "Arduino.h"
#include <vector>
#include "DisplayHighlevel.h"
#include "UIElement.h"
#include "TouchManager.h"

class UIManager
{
private:
    std::vector<UIElement *> elements;
    DisplayHighlevel *display;

public:
    UIManager(DisplayHighlevel *display)
    {
        this->display = display;
    }
    UIManager() {}
    ~UIManager() {}

    void registerElement(UIElement *element)
    {
        elements.push_back(element);
    }

    void handleTouch(UIPoint point)
    {
        bool updateNeeded = false;
        for (int i = 0; i < elements.size(); i++)
        {
            UIElement *e = elements.at(i);
            updateNeeded = updateNeeded || e->handleTouch(point);
        }

        if (updateNeeded)
        {
            drawUI();
        }
    }

    void drawUI()
    {
        display->clearDisplay();
        for (int i = 0; i < elements.size(); i++)
        {
            UIElement *e = elements.at(i);
            e->drawUI(display);
        }
        display->updateDisplay();
    }
};

#endif