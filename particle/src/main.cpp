#include "Adafruit_ST7735.h"
#include "./render/render.h"
#include "./layout/layout.h"
#include "./layout/temperature/temperature.h"
#include "./layout/clock/clock.h"
#include "./christmas/christmas.h"

//PINS
// -- SPI - shared
const int spi_cs = A2;
// -- screen
const int screen_dc = D0;
const int screen_rst = A0;
// -- buttons 
const int next_button = D2; 
const int previous_button = D1; 
// - temperature sensor LM35
const int temperature_sensor = A1; 

SerialDebugOutput debugOutput; //adding extra logging

const int layout_count = 2; 

Adafruit_ST7735 screen = init_screen(spi_cs, screen_dc, screen_rst);
struct Layout layouts[layout_count] = {
  get_temperature_layout(&screen, temperature_sensor), 
  get_clock_layout(&screen),
};
LayoutState layout_state = setup_layout_state(next_button, previous_button, layout_count, layouts);

void setup()
{
  Serial.begin(9600);
  Particle.publishVitals(5);

  setup_screen(&screen);
  setup_christmas_mode(D5, D3, D4);
}


void loop()
{
  render(&layout_state);
  //christmas_mode();
}

/*

Todo: 
- [X] Skjerm  
- [X] Splitt opp kode 
- [X] Bytte mellom skjermer med knapp 
- [ ] Skjerm 1: 
  - [X] Viser klokkeslett
  - [ ] Vise neste kollektivtransportmulighet 
  - [ ] Sette stasjon via web-grensesnitt 
- [ ] Skjerm 2 -> Temperatur
  - [X] Temperatursensor
  - [ ] Temeperatur fra vaermelding 
- [ ] Skjerm 3 -> Soevnlogger
  - [ ] Knapp for aa registrere sove/vaakne 
  - [ ] Lagre dem paa SD-kort 
- [ ] Skjerm 4 -> bilderamme 
  - [ ] Vise bilder 
  - [ ] Vise bilde fra SD-kort
- [ ] Misc 
  - [ ] Flammesensor som "brannalarm"
  - [ ] Christmas mode
*/
