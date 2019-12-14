#ifndef EMBEDDED_EXAM_SCREEN
#define EMBEDDED_EXAM_SCREEN

#include "Adafruit_ST7735.h"
#include "../sd/sd.h"
typedef Adafruit_ST7735 Screen; 

Screen init_screen(int cs, int dc, int rst);
void setup_screen(Screen * screen_pointer);
void write_text(Screen * screen_pointer, String text, int x, int y, int text_size); 
void clear_screen(Screen * screen_pointer); 
void write_image(Screen * screen_pointer, String filename, SD * sd_pointer);

#endif
