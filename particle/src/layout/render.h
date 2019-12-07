#ifndef EMBEDDED_EXAM_LAYOUT_RENDER
#define EMBEDDED_EXAM_LAYOUT_RENDER

#include "./layout.h"

LayoutState setup_render(
    int _next_button_pin,
    int _previous_button_pin,
    int total_layout_count,
    Layout *layouts);

/**
 * Will listen for changes to layout 
 * and render the current layout 
 * when changed //TODO: I may need other trigger methods for rerender
 */
void render(LayoutState * layout_state_pointer);

#endif
