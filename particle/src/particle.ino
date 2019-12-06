#include "Adafruit_ST7735.h"
#include "./screen/screen.h"

Adafruit_ST7735 screen = init_screen(A2, D0, A0);

/*

TODO: 
- [X] Skjerm  
- [X] Splitt opp kode 
- [ ] Bytte mellom skjermer med knapp 
- [ ] Skjerm 1: 
  - [ ] Viser klokkeslett
  - [ ] Vise neste kollektivtransportmulighet 
  - [ ] Sette stasjon via web-grensesnitt 
- [ ] Skjerm 2
  - [ ] Temperatursensor
  - [ ] Temeperatur fra vaermelding 
- [ ] Skjerm 3 -> Soevnlogger
  - [ ] Knapp for aa registrere sove/vaakne 
  - [ ] Lagre dem paa SD-kort 

*/

void setup()
{
  Serial.begin(9600);
  setup_screen(screen); 
}

void loop()
{
  if(digitalRead(D1)) {
    Serial.println("Button 1 is pressed");
  }

  if(digitalRead(D2)) {
    Serial.println("Button 2 is pressed");
  }

  write_text(screen, "Olav");
}