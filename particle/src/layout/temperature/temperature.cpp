#include "Particle.h"
#include "../layout.h"

int inside_temperature_pin;
int outside_temperature = -1; //updated via webhook integration
String temperature_city = "Oslo"; //can be updated through functions

void temperature_response_handler(const char *event, const char *data)
{
    /*
     * Expects the respons template to be: 
     * {{main.temp}}
    */
    outside_temperature = String(data).toInt();
}

int change_temperature_city(String _temperature_city) 
{
    if (_temperature_city.length() <= 0) return -1; 
    temperature_city = _temperature_city; 
    return 1; 
}

void setup_temperature()
{
    Particle.subscribe("temperature_response", temperature_response_handler, MY_DEVICES); 
    Particle.variable("temperature_city", temperature_city); 
    Particle.function("change_temperature_city", change_temperature_city); 
}

int read_local_temperature() 
{
    const int analog_value = analogRead(inside_temperature_pin);
    const int celcius = (int)(80 * analog_value / 1024.0);
    return celcius;
}

void updated_temperature_elements(Element elements[MAX_ELEMENT_COUNT]) 
{
    Particle.publish("temperature", String::format("{ \"city\": \"%s\" }", temperature_city.c_str()));

    elements[0] = {"local.", TOP_LEFT_CORNER}; 
    elements[1] = {String(read_local_temperature()), TOP_RIGHT_CORNER};
    elements[2] = {temperature_city, BOTTOM_LEFT_CORNER};
    elements[3] = {String(outside_temperature), BOTTOM_RIGHT_CORNER};
}

Layout get_temperature_layout(Screen * screen, int _inside_temperature_pin) 
{
    inside_temperature_pin = _inside_temperature_pin; 

    return {
        .screen = screen,    
        .element_count = 4, 
        .updated_elements = updated_temperature_elements,
        .update_frequency = 10000, //i.e. every 10 seconds
    };
}