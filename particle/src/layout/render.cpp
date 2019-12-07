#include "./layout.h"

void layout_write(Screen screen, String text, LayoutPosition position)
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

void render_layout(int element_count, Layout layout)
{
    Screen screen = layout.screen;
    for (int i = 0; i < element_count; i++)
    {
        Element element = layout.elements[i];
        layout_write(screen, element.text, element.position);
    }
}