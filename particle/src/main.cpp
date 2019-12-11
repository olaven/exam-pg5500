#include "./sd/sd.h"
#include "./render/render.h"
#include "./layout/layout.h"
#include "./layout/temperature/temperature.h"
#include "./layout/clock/clock.h"
#include "./christmas/christmas.h"

//PINS
// -- screen
const int screen_cs = A2;
const int screen_dc = D0;
const int screen_rst = A0;
// -- sd reader 
const int sd_cs = D4; 
// -- buttons 
const int next_button = D2; 
const int previous_button = D1; 
// - temperature sensor LM35
const int temperature_sensor = A1;
// - christmas mode 
const int lights_pin = D3;
const int speaker_pin = D5;  

SerialDebugOutput debugOutput; //adding extra logging

const int layout_count = 2; 

Screen screen = init_screen(screen_cs, screen_dc, screen_rst);
SD sd; 
struct Layout layouts[layout_count] = {
  get_temperature_layout(&screen, temperature_sensor), 
  get_clock_layout(&screen),
};
LayoutState layout_state = init_layout_state(next_button, previous_button, layout_count, layouts);

void setup()
{
  Serial.begin(9600);
  Particle.publishVitals(5);

  setup_screen(&screen);
  setup_christmas_mode(lights_pin, speaker_pin);
  sd = init_sd_card(sd_cs); 
}


void loop()
{
  render(&layout_state);
  christmas_mode();
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