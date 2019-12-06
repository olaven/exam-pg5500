#include "Adafruit_ST7735.h"
#include "Particle.h"
#include "screen.h";

Adafruit_ST7735 init_screen(int cs, int dc, int rst) 
{
    Adafruit_ST7735 screen = Adafruit_ST7735(cs, dc, rst);
    return screen; 
}

void setup_screen(Adafruit_ST7735 screen)
{
    screen.initG();
    screen.setRotation(3);
    screen.fillScreen(ST7735_BLACK);
}

void write_text(Adafruit_ST7735 screen, String text)
{

    screen.setTextSize(2);
    screen.setCursor(40, 55);
    screen.setTextColor(ST7735_WHITE);
    screen.setTextWrap(true);
    screen.print(text);
}
