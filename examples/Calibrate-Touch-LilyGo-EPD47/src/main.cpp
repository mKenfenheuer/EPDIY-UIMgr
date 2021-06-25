#include <Arduino.h>
#include "UISwitch.h"
#include "UIManager.h"
#include "EPDIYHighlevel.h"
#include "Wire.h"
#include "L58Touch.h"
#include "TouchCalibration.h"

L58Touch touch;
EPDIYHighlevel *display;

#define POINT_COUNT 5

int coffset = 25;

UIPoint points[POINT_COUNT] = {
    UIPoint(coffset, coffset),
    UIPoint(EPD_WIDTH - coffset, coffset),
    UIPoint(EPD_WIDTH / 2, EPD_HEIGHT / 2),
    UIPoint(coffset, EPD_HEIGHT - coffset),
    UIPoint(EPD_WIDTH - coffset, EPD_HEIGHT - coffset)};

UIPoint calibrations[POINT_COUNT] = {
    UIPoint(),
    UIPoint(),
    UIPoint(),
    UIPoint(),
    UIPoint()};

int indx = 0;

TouchCalibration *calibration;

void drawCalibrationPoint(UIPoint point)
{
    display->clearDisplay();
    display->fillCircle(point, 15, 0);
    display->updateDisplay();
}

void calculateCalibrationMap()
{
    calibration = new TouchCalibration(points, calibrations);
    touch.setTouchCalibration(calibration);
}

void onTouch(UIPoint point)
{
    if (indx < POINT_COUNT)
    {
        calibrations[indx] = point;
        Serial.printf("Got calibration point for X:%ld Y:%ld at X:%ld Y:%ld\n", points[indx].getX(), points[indx].getY(), point.getX(), point.getY());
        indx++;
        if (indx == POINT_COUNT)
        {
            Serial.printf("Calibration finished. Calculating map.\n");
            calculateCalibrationMap();
        }
        else
        {
            drawCalibrationPoint(points[indx]);
        }
    }
    else
    {
        drawCalibrationPoint(point);
    }
}

void setup()
{
    Serial.begin(115200);

    pinMode(CONFIG_TOUCH_INT, INPUT_PULLUP);
    Wire.begin(CONFIG_TOUCH_SDA, CONFIG_TOUCH_SDL, CONFIG_I2C_MASTER_FREQUENCY);

    display = new EPDIYHighlevel(EPD_OPTIONS_DEFAULT, EPD_ROT_LANDSCAPE, EPD_BUILTIN_WAVEFORM);

    touch.setTouchDimension(EPD_WIDTH, EPD_HEIGHT);
    touch.setRotation(TOUCH_ROT_LANDSCAPE);

    // calib: xo:-19, yo:6, xf:1.024775, yf:0.962672
    //calibration = new TouchCalibration(-19, 6, 1.024775, 0.962672);
    //touch.setTouchCalibration(calibration);

    touch.setTouchHandler(onTouch);
    touch.begin((gpio_num_t)CONFIG_TOUCH_INT);

    drawCalibrationPoint(points[indx]);
}

void loop()
{
    touch.loop();
}