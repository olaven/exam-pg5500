#include "./mode.h"
#include "../screen/layout.h"

const int MAX_LAYOUT_COUNT = 8; 
int next_button_pin = -1;
int previous_button_pin = -1;

void listen_for_layout_change(LayoutState layout_state) 
{
    //TODO: listen to buttons 
    //TODO: avoid multiple triggers (delay?)
}

int adjusted_layout_count(int layout_count)
{
    if (layout_count > MAX_LAYOUT_COUNT)
    {
        Serial.print("Last layouts are ommited because they exceed max count: ");
        Serial.println(MAX_LAYOUT_COUNT);
        layout_count = MAX_LAYOUT_COUNT;
    }

    return layout_count;
}

LayoutState setup_modes(
    int _next_button_pin, 
    int _previous_button_pin, 
    int total_layout_count, 
    Layout layouts[MAX_LAYOUT_COUNT])  
{
    //NOTE: avoiding overflows later on 
    total_layout_count = adjusted_layout_count(total_layout_count); 

    next_button_pin = _next_button_pin; 
    previous_button_pin = _next_button_pin; 

    return {
        .current_layout_index = 0, 
        .total_layout_count = total_layout_count, 
        .layouts = layouts,
    }; 
}
