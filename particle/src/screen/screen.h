#ifndef EMBEDDED_EXAM_SCREEN
#define EMBEDDED_EXAM_SCREEN

Adafruit_ST7735 init_screen(int cs, int dc, int rst);
void setup_screen(Adafruit_ST7735 screen);
void write_text(Adafruit_ST7735 screen, String text);

#endif
