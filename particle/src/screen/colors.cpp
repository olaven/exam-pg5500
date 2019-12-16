#include "Adafruit_ST7735.h"
#include "colors.h"

String background_color_name = "black";
String text_color_name = "white";

/**
 * Returns a color for 
 * the ST7735 screen.
 * Defaults to black
 */
int get_color(String color_name)
{
    if (color_name == "red")
    {
        return ST7735_RED;
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

/**
 * Returns the selected color 
 * as int value 
 */
int get_selected_background_color()
{
    const int color_value = get_color(background_color_name);
    return color_value; 
}

/**
 * Returns the selected color 
 * as int value 
 */
int get_selected_text_color() 
{
    const int color_value = get_color(text_color_name);
    return color_value;
}

int change_background_color(String color_name)
{
    Serial.println("got backgrouond color: " + color_name);
    background_color_name = color_name;
    return 0; 
}

int change_text_color(String color_name)
{
    Serial.println("got text color: " + color_name);
    text_color_name = color_name;
    return 0;
}

void register_color_changers()
{
    Particle.function("change_background_color", change_background_color);
    Particle.function("change_text_color", change_text_color);
    Particle.variable("text_color", text_color_name);
    Particle.variable("background_color", background_color_name);
}
