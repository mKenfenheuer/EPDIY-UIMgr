#ifndef _EPD_DISPLAY_HIGHLEVEL_DEF
#define _EPD_DISPLAY_HIGHLEVEL_DEF

#include "UIPoint.h"

class DisplayHighlevel
{
private:
    /* data */
public:
    bool display_initialized = false;
    bool initialized(){
        return display_initialized;
    }
    virtual void wakeDisplay();
    virtual void sleepDisplay();
    virtual void updateDisplay();
    virtual void clearDisplay();
    virtual void drawTextLeftAligned(const char* text, UIPoint point, int c);
    virtual void drawTextRightAligned(const char* text, UIPoint point, int c);
    virtual void drawTextCenterAligned(const char* text, UIPoint point, int c);
    virtual void drawCircle(UIPoint point, int r, int c);
    virtual void fillCircle(UIPoint point, int r, int c);
    virtual void drawRect(UIPoint point, int width, int height, int c);
    virtual void fillRect(UIPoint point, int width, int height, int c);
    virtual void drawLine(UIPoint start, UIPoint end, int c);
    virtual int width();
    virtual int height();
};

#endif