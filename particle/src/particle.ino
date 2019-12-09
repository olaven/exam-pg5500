#include "Adafruit_ST7735.h"
#include "./render/render.h"
#include "./layout/layout.h"
#include "./layout/temperature/temperature.h"

//PINS
// -- screen 
const int screen_cs = A2; 
const int screen_dc = D0; 
const int screen_rst = A0; 
// -- buttons 
const int next_button = D2; 
const int previous_button = D1; 
// - temperaturen sensor LM35
const int temperature_sensor = A1; 

const int layout_count = 1; 

Adafruit_ST7735 screen = init_screen(screen_cs, screen_dc, screen_rst);

Layout temp_layout = get_temperature_layout(screen, temperature_sensor); 
struct Layout layouts[layout_count] = {
  temp_layout 
};

LayoutState layout_state = setup_layout_state(next_button, previous_button, layout_count, layouts);

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