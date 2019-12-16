#include "Particle.h"
#include "ctype.h"
#include "state.h"

int alarm_hour = -1;
int alarm_minute = -1;
int extra_minutes = 25;

String alarm_from_location = "13825";
String alarm_to_location = "6488";
int arrive_by_hour = 9;
int arrive_by_minute = 15;

boolean alarm_enabled = false;
String alarm_enabled_readable = "no"; //NOTE: more readable for end user.

void extract_from_iso(String iso_string)
{
    int y, M, d;
    float s;
    sscanf(iso_string, "%d-%d-%dT%d:%d:%fZ", &y, &M, &d, &alarm_hour, &alarm_minute, &s);
    Serial.println("alarm hour: " + String(alarm_hour) + " alarm minute " + String(alarm_minute) + " from " + iso_string);
}

void entur_api_handler(const char *event, const char *data)
{
    extract_from_iso(String(data));
    add_extra_time();

    Serial.println("updated alarm to: " + String(alarm_hour) + ":" + String(alarm_minute));
}

void update_entur_subscription()
{
    String arrive_by_iso = String::format("%d-%d-%dT%d:%d:43+0100", Time.year(), Time.month(), Time.day(), arrive_by_hour, arrive_by_minute);
    String data = String::format(
        "{ \"from_id\": \"%s\", \"to_id\": \"%s\", \"arrive_by\": \"%s\" }",
        alarm_from_location.c_str(),
        alarm_to_location.c_str(),
        arrive_by_iso.c_str());

    Particle.publish("transport_event", data, PRIVATE);
}

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


int change_alarm_from_location(String _alarm_from)
{
    if (!is_valid_input(_alarm_from))
        return -1;
    alarm_from_location = _alarm_from;
    update_entur_subscription();
    return 0;
}

int change_alarm_to_location(String _alarm_to)
{
    if (!is_valid_input(_alarm_to))
        return -1;
    alarm_to_location = _alarm_to;
    update_entur_subscription();
    return 0;
}

int change_extra_minutes(String _extra_minutes)
{
    if (!is_valid_input(_extra_minutes, 59))
        return -1;
    extra_minutes = _extra_minutes.toInt();
    update_entur_subscription();
    return 0;
}

/**
 * This function accepts an ISO8806 date string, 
 * and updates the wanted arrival time. 
 * NOTE: this is not practical with the Particle App. 
 * Therefore, alternatives with hour/minute are also available (see other functions)
 */
int change_arrive_by(String _arrive_by)
{
    //TODO: some input validation
    extract_from_iso(_arrive_by);
    return 0;
}

int change_arrive_by_hour(String _arrive_by_hour)
{
    if (!is_valid_input(_arrive_by_hour, 23))
        return -1;
    arrive_by_hour = _arrive_by_hour.toInt();
    update_entur_subscription();
    return 0;
}

int change_arrive_by_minute(String _arrive_by_minute)
{
    if (!is_valid_input(_arrive_by_minute, 59))
        return -1;
    arrive_by_minute = _arrive_by_minute.toInt();
    update_entur_subscription();
    return 0;
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

void add_extra_time()
{
    alarm_minute = (alarm_minute + extra_minutes) % 60;
    if (alarm_minute < extra_minutes)
        alarm_hour += 1;
}


