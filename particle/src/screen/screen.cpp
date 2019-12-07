#include "Adafruit_ST7735.h"
#include "Particle.h"
#include "screen.h"

Screen init_screen(int cs, int dc, int rst) 
{
    Adafruit_ST7735 screen = Adafruit_ST7735(cs, dc, rst);
    return screen; 
}

void setup_screen(Screen screen)
{
    screen.initG();
    screen.setRotation(3);
    clear_screen(screen); 
}

void write_text(Screen screen, String text, int x, int y, int text_size)
{
    screen.setTextSize(text_size);
    screen.setCursor(x, y);
    screen.setTextColor(ST7735_WHITE);
    //screen.setTextWrap(true);
    screen.print(text);
}

void clear_screen(Screen screen) 
{
    screen.fillScreen(ST7735_BLACK);
}