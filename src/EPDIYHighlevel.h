#ifndef _EPD_EPDIY_HIGHLEVEL_DEF
#define _EPD_EPDIY_HIGHLEVEL_DEF

#include "epd_driver.h"
#include "epd_highlevel.h"
#include "DisplayHighlevel.h"
#include "Firasans/Firasans.h"

class EPDIYHighlevel : public DisplayHighlevel
{
private:
    const EpdFont *font = &FiraSans_12;
    uint8_t *fb;
    EpdRotation orientation = EPD_ROT_INVERTED_PORTRAIT;
    EpdInitOptions options;
    const EpdWaveform *waveform;
    EpdRotation rotation;
    EpdiyHighlevelState hl;
    void epd_full_refresh();

public:
    EPDIYHighlevel(EpdInitOptions options , EpdRotation orientation, const EpdWaveform *waveform = EPD_BUILTIN_WAVEFORM);
    void setFont(EpdFont *font);
    void wakeDisplay() override;
    void sleepDisplay() override;
    void updateDisplay() override;
    void clearDisplay() override;
    void drawTextLeftAligned(const char *text, UIPoint point, int c) override;
    void drawTextRightAligned(const char *text, UIPoint point, int c) override;
    void drawTextCenterAligned(const char *text, UIPoint point, int c) override;
    void drawCircle(UIPoint point, int r, int c) override;
    void fillCircle(UIPoint point, int r, int c) override;
    void drawRect(UIPoint point, int width, int height, int c) override;
    void fillRect(UIPoint point, int width, int height, int c) override;
};

#endif
