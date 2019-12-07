#ifndef EMBEDDED_EXAM_LAYOUT
#define EMBEDDED_EXAM_LAYOUT

#include "../screen/screen.h"

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
    Element elements[4];
};

struct LayoutState
{
    int current_layout_index;
    int total_layout_count;
    Layout *layouts;
};

void render_layout(int element_count, Layout layout);

#endif
