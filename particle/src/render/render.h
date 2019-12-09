#ifndef EMBEDDED_EXAM_LAYOUT_RENDER
#define EMBEDDED_EXAM_LAYOUT_RENDER

#include "../layout/layout.h"

/**
 * Will listen for changes to layout 
 * and render the current layout 
 * when changed //TODO: I may need other trigger methods for rerender
 */
void render(LayoutState * layout_state_pointer);

#endif