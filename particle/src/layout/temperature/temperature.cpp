/*
- [ ] Skjerm 2 -> Temperatur
    - [X] Temperatursensor
    - [ ] Temeperatur fra vaermelding 
*/

#include "../layout.h"

int local_temperature_pin;
const int element_count = 2; 


void updated_temperature_elements(Element elements[MAX_ELEMENT_COUNT]) 
{
    const int analog_value = analogRead(local_temperature_pin);
    const int celcius = (int) (80 * analog_value / 1024.0);
    String local_temperature = "Inne " + String(celcius); 

    elements[0] = {"temp.", CENTER}; 
    elements[1] = {local_temperature, BOTTOM_LEFT_CORNER}; 
}

Layout get_temperature_layout(Screen * screen, int _local_temperature_pin) 
{
    local_temperature_pin = _local_temperature_pin; 

    return {
        .screen = screen,    
        .element_count = element_count, 
        .updated_elements = updated_temperature_elements,
        .update_frequency = 10000, //i.e. every 10 seconds
    };
}