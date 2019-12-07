#include "./layout.h"

void render_layout(Screen screen, String text, LayoutPosition position)
{
    switch (position)
    {
    case CENTER:
        write_text(screen, text, 40, 55, 2);
        break;
    case BOTTOM_LEFT_CORNER:
        write_text(screen, text, 70, 80, 1);
        break;
    case BOTTOM_RIGHT_CORNER:
        write_text(screen, text, 5, 85, 1);
        break;
    case TOP_LEFT_CORNER:
        write_text(screen, text, 5, 30, 1);
        break;
    case TOP_RIGHT_CORNER:
        write_text(screen, text, 85, 30, 1);
    default:
        break;
    }
}

int layout_has_changed(LayoutState * layout_state_pointer) 
{
    int current = layout_state_pointer->current_layout_index; 
    int previous = layout_state_pointer->previous_layout_index; 
    return current != previous; 
}

//TODO: split this function
void render(LayoutState * layout_state_pointer) 
{
    Serial.print("Previous layout: ");
    Serial.print(layout_state_pointer->previous_layout_index);
    Serial.print(" Current layout: ");
    Serial.println(layout_state_pointer->current_layout_index);


    listen_for_layout_change(layout_state_pointer);
    if (layout_has_changed(layout_state_pointer)) 
    {
        Layout layout = layout_state_pointer->layouts[layout_state_pointer->current_layout_index];
        Screen screen = layout.screen;
        clear_screen(screen);
        
        for (int i = 0; i < layout_state_pointer->total_layout_count; i++)
        {
            Element element = layout.elements[i];
            render_layout(screen, element.text, element.position);
        }
    }
}

//TODO: this should be removed, in favour of just using layout 
//NOTE: This is just a wrapper to avoid multiple includes in `.ino`-file.
LayoutState setup_render(
    int _next_button_pin,
    int _previous_button_pin,
    int total_layout_count,
    Layout *layouts) 
{
    return setup_layout(
        _next_button_pin, 
        _previous_button_pin, 
        total_layout_count, 
        layouts); 
}