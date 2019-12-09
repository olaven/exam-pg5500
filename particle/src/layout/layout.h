#ifndef EMBEDDED_EXAM_LAYOUT
#define EMBEDDED_EXAM_LAYOUT

#include "../screen/screen.h"

#define MAX_ELEMENT_COUNT 8 

enum LayoutPosition
{
    CENTER,
    BOTTOM_LEFT_CORNER,
    BOTTOM_RIGHT_CORNER,
    TOP_LEFT_CORNER,
    TOP_RIGHT_CORNER
};

struct Element
{
    String text;
    LayoutPosition position;
};

struct Layout
{
    Screen screen;
    int element_count; 
    void (*updated_elements)(Element elements[MAX_ELEMENT_COUNT]);
    int update_frequency; 
};

struct LayoutState
{
    int current_layout_index;
    int previous_layout_index;
    int total_layout_count;
    Layout *layouts;
};

LayoutState setup_layout_state(
    int _next_button_pin,
    int _previous_button_pin,
    int total_layout_count,
    Layout *layouts);

void listen_for_layout_change(LayoutState * layout_state_pointer); 

#endif