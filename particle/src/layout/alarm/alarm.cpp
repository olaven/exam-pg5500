#include "Particle.h"
#include "../layout.h"
#include "ctype.h"

int alarm_hour = 7; 
int alarm_minute = 0;
boolean alarm_enabled = false; 
String alarm_enabled_readable = "no"; //NOTE: more readable for end user.

int alarm_pin = -1;


//
// IO for alarm
//

int is_valid_input(String input, int max_value)
{
    for (int i = 0; i < input.length(); i++)
    {
        char character = input.charAt(i);
        if (!isdigit(character))
        {
            return false;
        }
    }

    int int_value = input.toInt();
    return int_value <= max_value;
}

int change_alarm_hour(String hour_string)
{
    if (!is_valid_input(hour_string, 23))
        return -1;
    alarm_hour = hour_string.toInt();
    return 1;
}

int change_alarm_minute(String minute_string)
{
    if (!is_valid_input(minute_string, 59))
        return -1;
    alarm_minute = minute_string.toInt();
    return 1;
}

int toggle_alarm_enabled(String _)
{
    alarm_enabled = !alarm_enabled;
    if (alarm_enabled)
    {
        alarm_enabled_readable = "yes";
    }
    else
    {
        alarm_enabled_readable = "no";
    }

    return 0;
}

void setup_alarm_io(int _alarm_pin)
{
    alarm_pin = _alarm_pin;

    Particle.variable("alarm_hour", alarm_hour);
    Particle.variable("alarm_minute", alarm_minute);
    Particle.variable("alarm_enabled", alarm_enabled_readable);

    Particle.function("change_alarm_hour", change_alarm_hour);
    Particle.function("change_alarm_minute", change_alarm_minute);
    Particle.function("toggle_alarm_enabled", toggle_alarm_enabled);
}

void alarm_listener()
{

    const int current_hour = Time.hour(); 
    const int current_minute = Time.minute(); 
    const bool is_triggered = current_hour == alarm_hour && current_minute == alarm_minute; 

    if (toggle_alarm_enabled && is_triggered)
    {
        tone(alarm_pin, 440, 200);
    }
}

//
// Layout for alarm
//

void updated_alarm_elements(Element elements[MAX_ELEMENT_COUNT])
{
    String alarm_setting = "time:" + String(alarm_hour) + ":" + String(alarm_minute); 

    elements[0] = {"alarm", TOP_LEFT_CORNER};
    elements[1] = {alarm_setting, CENTER};
}

Layout get_alarm_layout(Screen *screen)
{
    return {
        .screen = screen,
        .element_count = 2,
        .updated_elements = updated_alarm_elements,
        .update_frequency = 60000, //i.e. every minute
    };
}