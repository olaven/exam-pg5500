#include "../layout.h"
#include "clock.h"

int element_count = 2; 

void updated_clock_elements(Element elements[MAX_ELEMENT_COUNT])
{
    String time = Time.format("%H:%M");
    String date = Time.format("%a:%b");

    elements[0] = {time, CENTER};
    elements[1] = {date, BOTTOM_RIGHT_CORNER}; 
}

Layout get_clock_layout(Screen * screen)
{

    return {
        .screen = screen,
        .element_count = element_count,
        .updated_elements = updated_clock_elements,
        .update_frequency = 60000, //i.e. every minute
    };
}