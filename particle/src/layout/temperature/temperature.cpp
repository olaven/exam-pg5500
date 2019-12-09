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
    const float celcius = (0.08 * analog_value / 1024.0);
    
    String local_temperature = "Inne " + String(round(celcius)); 
    //Element elements[2]; 

    elements[0] = {"temp.", CENTER}; 
    elements[1] = {local_temperature, BOTTOM_LEFT_CORNER}; 

    Serial.print("Element in temperature: "); 
    Serial.println(elements[0].text); 
    //return elements;
}

Layout get_temperature_layout(Screen screen, int _local_temperature_pin) 
{
    local_temperature_pin = _local_temperature_pin; 

    return {
        .screen = screen,    
        .element_count = element_count, 
        .updated_elements = updated_temperature_elements,
    };
}