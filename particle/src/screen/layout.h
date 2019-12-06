#ifndef EMBEDDED_EXAM_LAYOUT
#define EMBEDDED_EXAM_LAYOUT

#include "Particle.h"
#include "screen.h"

enum LayoutPosition
{
    CENTER,
    BOTTOM_LEFT_CORNER,
    BOTTOM_RIGHT_CORNER,
    TOP_LEFT_CORNER,
    TOP_RIGHT_CORNER
};
void layout_write(Screen screen, String text, LayoutPosition position);

#endif
