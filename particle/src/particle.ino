  #include "Adafruit_ST7735.h"

const int cs = A2; 
const int dc = D0; 
const int rst = A0; 

Adafruit_ST7735 screen = Adafruit_ST7735(cs, dc, rst);


/*

TODO: 
- [ ] Skjerm  
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

void setup_screen()
{
  screen.initG();
  screen.setRotation(3);
  screen.fillScreen(ST7735_BLACK);
}

void setup()
{
  Serial.begin(9600);
  Serial.println("i setup");

  setup_screen(); 
}

void write_text(String text) {


  screen.setTextSize(2);
  screen.setCursor(40, 55);
  screen.setTextColor(ST7735_WHITE);
  screen.setTextWrap(true);
  screen.print(text); 
}

void loop()
{
  Serial.println("i loop");

  write_text("Olav");
}