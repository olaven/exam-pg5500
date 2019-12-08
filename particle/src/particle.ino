#include "Adafruit_ST7735.h"
#include "./render/render.h"
#include "./layout/layout.h"
#include "./http/get_test.h"

Adafruit_ST7735 screen = init_screen(A2, D0, A0);

//TODO: these should be separate screens / folders

struct Layout layouts[3] = {
  {
    .screen = screen,   
    .elements = {
      {
        .text = "1center", 
        .position = CENTER, 
      }, 
      {
        .text = "1bottom", 
        .position = BOTTOM_LEFT_CORNER, 
      }, 
    }
  }, 
  {
    .screen = screen,   
    .elements = {
      {
        .text = "2center", 
        .position = CENTER, 
      }, 
      {
        .text = "2bottom", 
        .position = BOTTOM_LEFT_CORNER, 
      }, 
    }
  },
  {
    .screen = screen,   
    .elements = {
      {
        .text = "3center", 
        .position = CENTER, 
      }, 
      {
        .text = "3bottom", 
        .position = BOTTOM_LEFT_CORNER, 
      }, 
    }
  }
};

LayoutState layout_state = setup_layout_state(D2, D1, 3, layouts);
TCPClient client; 

void setup()
{
  Serial.begin(9600);
  setup_screen(screen);
}

void loop()
{
  render(&layout_state);
}

/*

TODO: 
- [X] Skjerm  
- [X] Splitt opp kode 
- [X] Bytte mellom skjermer med knapp 
- [ ] Skjerm 1: 
  - [ ] Viser klokkeslett
  - [ ] Vise neste kollektivtransportmulighet 
  - [ ] Sette stasjon via web-grensesnitt 
- [ ] Skjerm 2 -> Temperatur
  - [ ] Temperatursensor
  - [ ] Temeperatur fra vaermelding 
- [ ] Skjerm 3 -> Soevnlogger
  - [ ] Knapp for aa registrere sove/vaakne 
  - [ ] Lagre dem paa SD-kort 
- [ ] Skjerm 4 -> bilderamme 
  - [ ] Vise bilder 
  - [ ] Vise bilde fra SD-kort
*/