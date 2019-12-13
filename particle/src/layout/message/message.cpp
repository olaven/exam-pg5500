#include "Particle.h"
#include "../layout.h"
#include "message.h"

const int element_count = 1; 
String message = ":-)";

int update_message(String new_message) 
{
    if (new_message.length() < 1 || new_message.length() > 15)
    {
        return -1; 
    }
    
    message = new_message;
}

void setup_message_updater()
{
    Particle.function("update_message", update_message);
    Particle.variable("message", message);
}

void updated_message_elements(Element elements[MAX_ELEMENT_COUNT])
{
    elements[0] = {message, CENTER};
}

Layout get_message_layout(Screen *screen)
{
    return {
        .screen = screen,
        .element_count = element_count,
        .updated_elements = updated_message_elements,
        .update_frequency = 18000, //i.e. every 5 minutes
    };
}