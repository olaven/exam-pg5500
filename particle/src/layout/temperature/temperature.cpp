/*
- [ ] Skjerm 2 -> Temperatur
    - [ ] Temperatursensor
    - [ ] Temeperatur fra vaermelding 
*/

#include "../layout.h"

static int pin;
static String local_temperature = "..";
const int element_count = 2; 


void updated_temperature_elements(Element * elements) 
{
    /* const int analog_value = analogRead(pin);
    float celcius = (0.8 * analog_value / 1024.0);
    
    local_temperature = String("Inne: ", celcius); */


    elements[0] = {
        .text = "temp.", 
        .position = CENTER, 
    }; 

    elements[1] = {
        .text = "SOMETHING", 
        .position = BOTTOM_LEFT_CORNER, 
    };

    Serial.print("Returning from temp: "); 
    Serial.println(elements[0].text); 
}

Layout get_temperature_layout(Screen screen, int pin) 
{

    return {
        .screen = screen,    
        .element_count = element_count, 
        .updated_elements = updated_temperature_elements,
    };
}