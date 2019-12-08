#include "./layout.h"

int next_button_pin = -1;
int previous_button_pin = -1;

/**
 * TODO: This file should be exposed with setup to main ino file 
 */

int buttons_are_valid()
{

    if (next_button_pin < 0 || previous_button_pin < 0)
    {
        Serial.println("Button PIN does not seem valid.");
        return -1;
    }
    return 1;
}

void to_next_layout(LayoutState * layout_state_pointer)
{
    int current = layout_state_pointer->current_layout_index;
    int next = (current + 1) % layout_state_pointer->total_layout_count;
    layout_state_pointer->current_layout_index = next;
    layout_state_pointer->previous_layout_index = current; 
}

void to_previous_layout(LayoutState * layout_state_pointer)
{
    int current = layout_state_pointer->current_layout_index;
    int previous = (current - 1);
    if (previous < 0)
    {
        previous = layout_state_pointer->total_layout_count - 1;
    }

    layout_state_pointer->current_layout_index = previous;
    layout_state_pointer->previous_layout_index = current; 
}

void stay_on_same_layout(LayoutState * layout_state_pointer) 
{
    int current = layout_state_pointer->current_layout_index;
    layout_state_pointer->previous_layout_index = current; 
}

void listen_for_layout_change(LayoutState * layout_state_pointer) 
{
    //TODO: avoid multiple triggers (delay?)
    if (buttons_are_valid()) 
    {
        if (digitalRead(next_button_pin))
        {
            to_next_layout(layout_state_pointer);
        }
        else if (digitalRead(previous_button_pin))
        {
            to_previous_layout(layout_state_pointer); 
        } 
        else 
        {
            stay_on_same_layout(layout_state_pointer); 
        }
    }

    delay(100); //avoiding going back at once TODO: replace with millis to avoid actually stopping?
}

LayoutState setup_layout_state(
    int _next_button_pin,
    int _previous_button_pin,
    int total_layout_count,
    Layout *layouts)
{

    next_button_pin = _next_button_pin;
    previous_button_pin = _previous_button_pin;

    struct LayoutState initial_state = {
        .current_layout_index = 0,
        .previous_layout_index = 0, //NOTE: OK as long as 0 is default index 
        .total_layout_count = total_layout_count,
        .layouts = layouts};

    return initial_state;
}
