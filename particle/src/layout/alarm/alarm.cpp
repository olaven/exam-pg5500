#include "Particle.h"
#include "../layout.h"
#include "state.h"
#include "alarm.h"

int alarm_pin = -1;

void setup_alarm_io(int _alarm_pin)
{
    alarm_pin = _alarm_pin;

    Particle.subscribe("transport_response", entur_api_handler, MY_DEVICES);

    Particle.variable("alarm_hour", alarm_hour);
    Particle.variable("alarm_minute", alarm_minute);
    Particle.variable("extra_minutes", extra_minutes); 
    Particle.variable("alarm_from_location", alarm_from_location);
    Particle.variable("alarm_to_location", alarm_to_location);
    Particle.variable("arrive_by_hour", arrive_by_hour);
    Particle.variable("arrive_by_minute", arrive_by_minute);
    Particle.variable("alarm_enabled_readable", alarm_enabled_readable);

    Particle.function("change_alarm_from_location", change_alarm_from_location);
    Particle.function("change_alarm_to_location", change_alarm_to_location);
    Particle.function("change_extra_minutes", change_extra_minutes);
    Particle.function("change_arrive_by_minute", change_arrive_by_minute);
    Particle.function("change_arrive_by_hour", change_arrive_by_hour);
    Particle.function("change_arrive_by", change_arrive_by); //TODO: accept iso date
    Particle.function("toggle_alarm_enabled", toggle_alarm_enabled);
}

void alarm_listener()
{
    /**
     * Updating in case of delays/other changes to 
     * entur data.
     */
    static int firstCall = true; 
    if (millis() % 900000 == 0 || firstCall)
    {
        Serial.println("Extra update of entur");
        firstCall = false; 
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


void updated_alarm_elements(Element elements[MAX_ELEMENT_COUNT])
{
    String next_alarm = "time:" + String(alarm_hour) + ":" + String(alarm_minute); 

    elements[0] = {"alarm", TOP_LEFT_CORNER};
    elements[1] = {next_alarm, CENTER};
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