#ifndef _EPD_TOUCH_CALIBRATION_DEF
#define _EPD_TOUCH_CALIBRATION_DEF

#include "UIPoint.h"
#include "Arduino.h"

class TouchCalibration
{
private:
    long xoffset = 0, yoffset = 0;
    double xfactor = 1, yfactor = 1;

public:
    TouchCalibration(UIPoint _points[5], UIPoint _calibrations[5])
    {
        double xlavg = (_calibrations[0].getX() + _calibrations[3].getX()) / 2.0;
        double xravg = (_calibrations[1].getX() + _calibrations[4].getX()) / 2.0;

        double ytavg = (_calibrations[0].getY() + _calibrations[1].getY()) / 2.0;
        double ybavg = (_calibrations[3].getY() + _calibrations[4].getY()) / 2.0;

        printf("input: xla:%f, xra:%f, yta:%f, yba:%f\n", xlavg, xravg, ytavg, ybavg);

        double xrange = xravg - xlavg;
        double yrange = ybavg - ytavg;

        long calibxrange = _points[1].getX() - _points[0].getX();
        long calibyrange = _points[3].getY() - _points[0].getY();

        printf("calc: xir:%f, yir:%f, xcr:%ld, ycr:%ld\n", xrange, yrange, calibxrange, calibyrange);

        xfactor = calibxrange / xrange;
        yfactor = calibyrange / yrange;

        xoffset = (long)_points[2].getX() - (long)_calibrations[2].getX();
        yoffset = (long)_points[2].getY() - (long)_calibrations[2].getY();

        printf("calib: xo:%ld, yo:%ld, xf:%f, yf:%f\n", xoffset, yoffset, xfactor, yfactor);
    }
    
    TouchCalibration(long xoffset = 0, long yoffset = 0, double xfactor = 1, double  yfactor = 1) {
        this->xoffset = xoffset;
        this->yoffset = yoffset;
        this->xfactor = xfactor;
        this->yfactor = yfactor;
    }

    TouchCalibration() {}

    UIPoint translatePoint(UIPoint point)
    {
        return UIPoint((long)(point.getX() * xfactor + xoffset), (long)(point.getY() * yfactor + yoffset));
    }
};

#endif