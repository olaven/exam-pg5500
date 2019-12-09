/*
- [ ] Skjerm 2 -> Temperatur
    - [ ] Temperatursensor
    - [ ] Temeperatur fra vaermelding 
*/

#include "../layout.h"

static int pin;
static String local_temperature = "..";


Element * update_elements() 
{
    const int analog_value = analogRead(pin);
    float celcius = (0.8 * analog_value / 1024.0);
    
    local_temperature = String("Inne: ", celcius);
    Element elements[2] = {
        {
            .text = "temp.", 
            .position = CENTER, 
        }, 
        {
            .text = local_temperature, 
            .position = BOTTOM_LEFT_CORNER, 
        }, 
    };

    return elements;
}


Layout get_temperature_layout(Screen screen, int pin) 
{
    Element elements[2] = {
        {
            .text = "temp.", 
            .position = CENTER, 
        }, 
        {
            .text = "Some tesxt hello should be local", 
            .position = BOTTOM_LEFT_CORNER, 
        }, 
    };

    return {
        .screen = screen,    
        .elements = elements,
        .updated_elements = update_elements,
    };
}