#ifndef EMBEDDED_EXAM_SCREEN
#define EMBEDDED_EXAM_SCREEN

typedef Adafruit_ST7735 Screen; 

Screen init_screen(int cs, int dc, int rst);
void setup_screen(Screen screen);
void write_text(Screen screen, String text, int x = 40, int y = 55, int text_size = 1); 

#endif
