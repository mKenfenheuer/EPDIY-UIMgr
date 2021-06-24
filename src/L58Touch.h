#ifndef _EPD_L58_TOUCH_DEF
#define _EPD_L58_TOUCH_DEF

#include <Arduino.h>
#include <Wire.h>
#include "UIPoint.h"
#include "TouchManager.h"

#define TOUCH_SLAVE_ADDRESS 0x5A

class L58Touch : public TouchManager
{
    typedef struct
    {
        uint8_t id;
        uint8_t state;
        uint16_t x;
        uint16_t y;
    } TouchData_t;

public:


    bool begin(gpio_num_t touch_int = GPIO_NUM_13, TwoWire &port = Wire, uint8_t addr = TOUCH_SLAVE_ADDRESS);

    uint8_t scanPoint();
    void getPoint(uint16_t &x, uint16_t &y, uint16_t &s, uint8_t index);
    void sleep(void);
    void wakeup(void);
    void loop();
    TouchData_t data[5];

private:
    void clearFlags(void);
    void readBytes(uint8_t *data, uint8_t nbytes);
    uint8_t _address;
    gpio_num_t _touch_int;
    bool initialization = false;

    TwoWire *_i2cPort;
};

#endif
