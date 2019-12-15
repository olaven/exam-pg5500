#include "Particle.h"
#include "../layout.h"
#include "ctype.h"

int alarm_hour = -1; 
int alarm_minute = -1;
int extra_minutes = 25; 
String alarm_from_location = "13825"; 
String alarm_to_location = "6488";
int arrive_by_hour = 9; 
int arrive_by_minute = 15; 

boolean alarm_enabled = false;
String alarm_enabled_readable = "no"; //NOTE: more readable for end user.

int alarm_pin = -1;


//
// IO for alarm
//

int is_valid_input(String input, const int max_value = 999999)
{
    for (int i = 0; i < input.length(); i++)
    {
        char character = input.charAt(i);
        if (!isdigit(character))
        {
            return false;
        }
    }

    const int as_int = input.toInt(); 
    return as_int <= max_value; 
}

void update_entur_subscription()
{
    String arrive_by_iso = String::format("%d-%d-%dT%d:%d:43+0100", Time.year(), Time.month(), Time.day(), arrive_by_hour, arrive_by_minute);
    String data = String::format(
        "{ \"from_id\": \"%s\", \"to_id\": \"%s\", \"arrive_by\": \"%s\" }", 
        alarm_from_location.c_str(), 
        alarm_to_location.c_str(),
        arrive_by_iso.c_str()
    );
    Particle.publish("transport_event", data, PRIVATE);
}

int change_alarm_from_location(String _alarm_from)
{
    if (!is_valid_input(_alarm_from))
        return -1;
    alarm_from_location = _alarm_from;
    update_entur_subscription();
    return 1;
}

int change_alarm_to_location(String _alarm_to)
{
    if (!is_valid_input(_alarm_to))
        return -1;
    alarm_to_location = _alarm_to;
    update_entur_subscription();
    return 1; 
}

int change_extra_minutes(String _extra_minutes)
{
    if (!is_valid_input(_extra_minutes, 59))
        return -1; 
    extra_minutes = _extra_minutes.toInt(); 
    update_entur_subscription();
    return 1; 
}

int change_arrive_by_hour(String _arrive_by_hour)
{
    if (!is_valid_input(_arrive_by_hour, 23))
        return -1; 
    arrive_by_hour = _arrive_by_hour.toInt(); 
    update_entur_subscription(); 
    return 1; 
}

int change_arrive_by_minute(String _arrive_by_minute)
{
    if (!is_valid_input(_arrive_by_minute, 59))
        return -1; 
    arrive_by_minute = _arrive_by_minute.toInt();
    update_entur_subscription(); 
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

int add_extra_time() 
{
    alarm_minute = (alarm_minute + extra_minutes) % 60; 
    if (alarm_minute < extra_minutes)
        alarm_hour += 1;
}

void entur_api_handler(const char *event, const char *data)
{
    int y, M, d; 
    float s;
    sscanf(data, "%d-%d-%dT%d:%d:%fZ", &y, &M, &d, &alarm_hour, &alarm_minute, &s);
    add_extra_time(); 
    
    Serial.println("updated alarm to: " + String(alarm_hour) + ":" + String(alarm_minute));
}

void setup_alarm_io(int _alarm_pin)
{
    alarm_pin = _alarm_pin;

    Particle.subscribe("transport_response", entur_api_handler, MY_DEVICES);

    Particle.variable("alarm_hour", alarm_hour);
    Particle.variable("alarm_minute", alarm_minute);
    Particle.variable("extra_minutes", extra_minutes); 
    Particle.variable("alarm_from_location", alarm_from_location);
    Particle.variable("alarm_to_location", alarm_to_location);

    Particle.function("change_alarm_from_location", change_alarm_from_location);
    Particle.function("change_alarm_to_location", change_alarm_to_location);
    Particle.function("change_extra_minutes", change_extra_minutes);
    Particle.function("change_arrive_by_minute", change_arrive_by_minute);
    Particle.function("change_arrive_by_hour", change_arrive_by_hour);
    Particle.function("toggle_alarm_enabled", toggle_alarm_enabled);
}


void alarm_listener()
{
    /**
     * Updating in case of delays/other changes to 
     * entur data.
     */
    if (millis() % 900000 == 0)
    {
        Serial.println("Extra update of entur");
        update_entur_subscription(); 
    }

    const int current_hour = Time.hour(); 
    const int current_minute = Time.minute(); 
    const bool is_triggered = current_hour == alarm_hour && current_minute == alarm_minute; 

    if (alarm_enabled && is_triggered)
    {
        tone(alarm_pin, 440, 200);
    }
}

//
// Layout for alarm
//

//TODO: update alarm in case of delays
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