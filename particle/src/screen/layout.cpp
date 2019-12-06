#include "Particle.h"
#include "screen.h"
#include "layout.h"

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