#include "Adafruit_ST7735.h"
#include "colors.h"

int selected_background_color = ST7735_BLACK;
int selected_text_color = ST7735_WHITE;

int get_selected_background_color()
{
    return selected_background_color; 
}

int get_selected_text_color() 
{
    return selected_text_color;
}

/**
 * Returns a color for 
 * the ST7735 screen.
 * Defaults to black
 */
    int
    get_color(String color_name)
{
    if (color_name == "red")
    {
        return ST7735_BLACK;
    }
    else if (color_name == "yellow")
    {
        return ST7735_YELLOW;
    }
    else if (color_name == "white")
    {
        return ST7735_WHITE;
    }
    else if (color_name == "blue")
    {
        return ST7735_BLUE;
    }
    else if (color_name == "cyan")
    {
        return ST7735_CYAN;
    }
    else if (color_name == "magenta")
    {
        return ST7735_MAGENTA;
    }
    else if (color_name == "blue")
    {
        return ST7735_BLUE;
    }
    else if (color_name == "green")
    {
        return ST7735_GREEN;
    }

    return ST7735_BLACK;
}

int change_background_color(String color_name)
{
    int color = get_color(color_name);
    selected_background_color = color;
}

int change_text_color(String color_name)
{
    int color = get_color(color_name);
    selected_text_color = color;
}

void register_color_changers()
{
    Particle.function("change_background_color", change_background_color);
    Particle.function("change_text_color", change_text_color);
}
