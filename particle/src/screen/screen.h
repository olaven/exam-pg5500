#ifndef EMBEDDED_EXAM_SCREEN
#define EMBEDDED_EXAM_SCREEN

#include "Adafruit_ST7735.h"
typedef Adafruit_ST7735 Screen; 

Screen init_screen(int cs, int dc, int rst);
void setup_screen(Screen screen);
void write_text(Screen screen, String text, int x, int y, int text_size); 
void clear_screen(Screen screen); 

#endif
