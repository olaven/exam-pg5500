#include "Adafruit_ST7735.h"
#include "./render/render.h"
#include "./layout/layout.h"
#include "./layout/temperature/temperature.h"

Adafruit_ST7735 screen = init_screen(A2, D0, A0);


struct Element element = {
    .text = "hei", 
    .position = CENTER,
};
Element elements[1] = {element}; 
Element * updated_elements() {
  
  return elements; 
}
struct Layout layouts[1] = {
  //get_temperature_layout(screen, A1)
  {
      .screen = screen, 
      .elements = elements, 
      .updated_elements = updated_elements,
  }
};

LayoutState layout_state = setup_layout_state(D2, D1, 3, layouts);

void setup()
{
  Serial.begin(9600);
  setup_screen(screen);
  pinMode(A1, INPUT);
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