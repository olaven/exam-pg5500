#include "Adafruit_ST7735.h"
#include "Particle.h"
#include "screen.h"

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
    clear_screen(screen_pointer); 
}

void write_text(Screen * screen_pointer, String text, int x, int y, int text_size)
{
    screen_pointer->setTextSize(text_size);
    screen_pointer->setCursor(x, y);
    screen_pointer->setTextColor(ST7735_WHITE, ST7735_BLACK);
    //screen.setTextWrap(true);
    screen_pointer->print(text);
}

void clear_screen(Screen * screen_pointer) 
{
    Serial.println("Clearing screen");
    //TODO: fix clearing 
    screen_pointer->fillScreen(ST7735_BLACK); 
}