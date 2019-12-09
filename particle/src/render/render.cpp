#include "../layout/layout.h"

void render_element(Screen screen, String text, LayoutPosition position)
{

    Serial.print("Rendering: "); 
    Serial.println(text);

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

void render_current_layout(LayoutState * layout_state_pointer)
{
    Layout layout = layout_state_pointer->layouts[layout_state_pointer->current_layout_index];
    Screen screen = layout.screen;
    clear_screen(screen);
    
    Element elements[layout.element_count]; 
    layout.updated_elements(elements);  
    for (int i = 0; i < layout.element_count; i++)
    {
        Element element = elements[i];         

        render_element(screen, element.text, element.position);
    }
}

int layout_has_changed(LayoutState * layout_state_pointer) 
{
    int current = layout_state_pointer->current_layout_index; 
    int previous = layout_state_pointer->previous_layout_index; 
    return current != previous; 
}


void render(LayoutState * layout_state_pointer) 
{
    static int render_count = 0; 
    listen_for_layout_change(layout_state_pointer);
    
    //if (layout_has_changed(layout_state_pointer) || render_count == 0) //TODO: add back 
    if(true)
    {
        render_count++; 
        render_current_layout(layout_state_pointer); 
    }
}