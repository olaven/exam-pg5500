#include "../layout/layout.h"

void render_element(Screen * screen_pointer, String text, LayoutPosition position)
{
    switch (position)
    {
    case CENTER:
        write_text(screen_pointer, text, 40, 55, 2);
        break;
    case BOTTOM_LEFT_CORNER:
        write_text(screen_pointer, text, 70, 80, 1);
        break;
    case BOTTOM_RIGHT_CORNER:
        write_text(screen_pointer, text, 5, 85, 1);
        break;
    case TOP_LEFT_CORNER:
        write_text(screen_pointer, text, 5, 30, 1);
        break;
    case TOP_RIGHT_CORNER:
        write_text(screen_pointer, text, 85, 30, 1);
    default:
        break;
    }
}

void render_current_layout(LayoutState * layout_state_pointer)
{
    Layout layout = layout_state_pointer->layouts[layout_state_pointer->current_layout_index];
    Screen * screen_pointer = layout.screen;
    clear_screen(screen_pointer);

    Element elements[layout.element_count]; 
    layout.updated_elements(elements);  
    for (int i = 0; i < layout.element_count; i++)
    {
        Element element = elements[i];         
        render_element(screen_pointer, element.text, element.position);
    }
}

int layout_has_changed(LayoutState * layout_state_pointer) 
{
    int current = layout_state_pointer->current_layout_index; 
    int previous = layout_state_pointer->previous_layout_index; 
    return current != previous; 
}

int timeout_has_passed(LayoutState * layout_state_pointer) 
{
    Layout layout = layout_state_pointer->layouts[layout_state_pointer->current_layout_index];
    int now = millis(); 
    int frequency = layout.update_frequency; 

    return now % frequency < 100; //NOTE: ideally 0, but loops take time. 100ms is less accurate, but practical. 
}

int should_rerender(LayoutState * layout_state_pointer) 
{
    static int render_count = 0; 
    render_count++; 

    return render_count == 1 || layout_has_changed(layout_state_pointer) || timeout_has_passed(layout_state_pointer); 
}

void render(LayoutState * layout_state_pointer) 
{
    listen_for_layout_change(layout_state_pointer);
    
    if (should_rerender(layout_state_pointer))
    {
        render_current_layout(layout_state_pointer); 
    }
}