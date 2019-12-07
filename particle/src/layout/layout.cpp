#include "./layout.h"

int next_button_pin = -1;
int previous_button_pin = -1;

void listen_for_layout_change(LayoutState layout_state) 
{
    //TODO: listen to buttons 
    //TODO: avoid multiple triggers (delay?)
}


LayoutState setup_modes(
    int _next_button_pin, 
    int _previous_button_pin, 
    int total_layout_count, 
    Layout * layouts)  
{

    next_button_pin = _next_button_pin; 
    previous_button_pin = _next_button_pin;

    struct LayoutState initial_state = {
        .current_layout_index = 0,
        .total_layout_count = total_layout_count,
        .layouts = layouts,
    };
    
    return initial_state;
}
