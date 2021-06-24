#include <Arduino.h>
#include "UISwitch.h"
#include "UIManager.h"
#include "EPDIYHighlevel.h"
#include "Wire.h"
#include "L58Touch.h"

L58Touch touch;
EPDIYHighlevel *display;
UIManager *manager;
UISwitch *swtch;

void onTouch(UIPoint point)
{
    manager->handleTouch(point);
}

void onSwitch(UIElement *element)
{
    UISwitch *sw = (UISwitch*) element;
    Serial.printf("SwitchClicked. Its now %s\n", sw->getState() ? "ON" : "OFF");
}

void setup()
{
    Serial.begin(115200);

    pinMode(CONFIG_TOUCH_INT, INPUT_PULLUP);
    Wire.begin(CONFIG_TOUCH_SDA, CONFIG_TOUCH_SDL, CONFIG_I2C_MASTER_FREQUENCY);

    display = new EPDIYHighlevel(EPD_OPTIONS_DEFAULT, EPD_ROT_PORTRAIT, EPD_BUILTIN_WAVEFORM);
    manager = new UIManager(display);
    swtch = new UISwitch(manager, UIPoint(0, 0));
    swtch->setState(false);
    swtch->setOnClickHandler(onSwitch);

    manager->drawUI();

    touch.setTouchDimension(EPD_WIDTH, EPD_HEIGHT);
    touch.setRotation(TOUCH_ROT_PORTRAIT);

    touch.setTouchHandler(onTouch);
    touch.begin((gpio_num_t)CONFIG_TOUCH_INT);
}

void loop()
{
    touch.loop();
}