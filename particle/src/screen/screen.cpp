#include "Particle.h"
#include "Adafruit_ST7735.h"
#include "screen.h"
#include "colors.h"


#define BUFFPIXEL 20

Screen init_screen(int cs, int dc, int rst)
{
    Adafruit_ST7735 screen = Adafruit_ST7735(cs, dc, rst);
    return screen; 
}

void setup_screen(Screen * screen_pointer)
{
    screen_pointer->initG();
    screen_pointer->setRotation(3);
    screen_pointer->invertDisplay(true); 
    register_color_changers();
}

void write_text(Screen * screen_pointer, String text, int x, int y, int text_size)
{
    screen_pointer->setTextSize(text_size);
    screen_pointer->setCursor(x, y);
    screen_pointer->setTextColor(get_selected_text_color(), get_selected_background_color());
    screen_pointer->print(text);
}

void clear_screen(Screen *screen_pointer)
{
    const int background_color = get_selected_background_color();
    screen_pointer->fillScreen(background_color);
}