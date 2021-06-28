#include "EPDIYHighlevel.h"

void EPDIYHighlevel::wakeDisplay()
{
    epd_poweron();
}

void EPDIYHighlevel::sleepDisplay()
{
    epd_poweroff();
}

void EPDIYHighlevel::updateDisplay()
{
    epd_full_refresh();
}

void EPDIYHighlevel::clearDisplay() 
{
    epd_hl_set_all_white(&hl); 
}

int EPDIYHighlevel::width() 
{
    return epd_rotated_display_width(); 
}

int EPDIYHighlevel::height() 
{
    epd_rotated_display_height(); 
}

EPDIYHighlevel::EPDIYHighlevel(EpdInitOptions options , EpdRotation orientation, const EpdWaveform *waveform)
{
    this->waveform = waveform;
    this->options = options;
    this->orientation = orientation;
    epd_init(options);
    hl = epd_hl_init(waveform);
    epd_set_rotation(orientation);
    fb = epd_hl_get_framebuffer(&hl);
    display_initialized = true;
}

void EPDIYHighlevel::epd_full_refresh()
{
    epd_draw_base(epd_full_screen(), fb, epd_full_screen(), (EpdDrawMode)(MODE_PACKING_2PPB | PREVIOUSLY_WHITE | MODE_GC16), 25, NULL, (EpdWaveform *)EPD_BUILTIN_WAVEFORM);
}

void EPDIYHighlevel::setFont(const EpdFont *font)
{
    this->font = font;
}

void EPDIYHighlevel::drawTextLeftAligned(const char *text, UIPoint point, int c)
{
    EpdFontProperties font_props = epd_font_properties_default();
    font_props.flags = EPD_DRAW_ALIGN_LEFT;
    font_props.fg_color = c;
    font_props.bg_color = 255 - c;
    int x = point.getX();
    int y = point.getY();
    Serial.printf("Printing text LeftAligned: %s at: %d,%d\n", text, point.getX(), point.getY());
    epd_write_string(font, text, &x, &y, fb, &font_props);
}

void EPDIYHighlevel::drawTextRightAligned(const char *text, UIPoint point, int c)
{
    EpdFontProperties font_props = epd_font_properties_default();
    font_props.flags = EPD_DRAW_ALIGN_RIGHT;
    font_props.fg_color = c;
    font_props.bg_color = 255 - c;
    int x = point.getX();
    int y = point.getY();
    Serial.printf("Printing text RightAligned: %s at: %d,%d\n", text, point.getX(), point.getY());
    epd_write_string(font, text, &x, &y, fb, &font_props);
}

void EPDIYHighlevel::drawTextCenterAligned(const char *text, UIPoint point, int c)
{
    EpdFontProperties font_props = epd_font_properties_default();
    font_props.flags = EPD_DRAW_ALIGN_CENTER;
    font_props.fg_color = c;
    font_props.bg_color = 255 - c;
    int x = point.getX();
    int y = point.getY();
    Serial.printf("Printing text CenterAligned: %s at: %d,%d\n", text, point.getX(), point.getY());
    epd_write_string(font, text, &x, &y, fb, &font_props);
}

void EPDIYHighlevel::drawCircle(UIPoint point, int r, int c)
{
    int x = point.getX();
    int y = point.getY();
    Serial.printf("Drawing circle with r=%d at: %d,%d\n", r, point.getX(), point.getY());
    epd_draw_circle(x, y, r, c, fb);
}

void EPDIYHighlevel::fillCircle(UIPoint point, int r, int c)
{
    int x = point.getX();
    int y = point.getY();
    Serial.printf("Filling circle with r=%d at: %d,%d\n", r, point.getX(), point.getY());
    epd_fill_circle(x, y, r, c, fb);
}

void EPDIYHighlevel::drawRect(UIPoint point, int width, int height, int c)
{
    EpdRect rect;
    rect.x = point.getX();
    rect.y = point.getY();
    rect.width = width;
    rect.height = height;

    Serial.printf("Drawing rect with w=%d, h=%d at: %d,%d\n", width, height, point.getX(), point.getY());
    epd_draw_rect(rect, c, fb);
}

void EPDIYHighlevel::fillRect(UIPoint point, int width, int height, int c)
{
    EpdRect rect;
    rect.x = point.getX();
    rect.y = point.getY();
    rect.width = width;
    rect.height = height;

    Serial.printf("Filling rect with w=%d, h=%d at: %d,%d\n", width, height, point.getX(), point.getY());
    epd_fill_rect(rect, c, fb);
}

void EPDIYHighlevel::drawLine(UIPoint start, UIPoint end, int c) {
    epd_draw_line(start.getX(), start.getY(), end.getX(), end.getY(), c, fb);
}