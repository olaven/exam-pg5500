#include "Particle.h"
#include "../layout.h"
#include "state.h"
#include "alarm.h"

/**
 * General note: 
 * The locations are based on Nasjonalt Stoppestedsregister 
 * (NSR, https://www.entur.org/wp-content/uploads/2018/03/Nasjonalt-stoppestedsregister.pdf)
 *  
 * A stop is identified with an ID. 
 * To find an ID manually, one may go to https://stoppested.entur.org and use their interative map. 
 */

int alarm_pin = -1;

void setup_alarm(int _alarm_pin)
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
    Particle.function("change_arrive_by", change_arrive_by); 
    Particle.function("toggle_alarm_enabled", toggle_alarm_enabled);
}

/*
    The alarm should be updated temporarily, 
    to account for traffic delays, changes etc.
    The update should run every 15 minutes, and 
    on startup. 

    However, these two conditions must not be met 
    at the same time, as that could cause a 
    "race condition", waiting for the response 
    from entur. 

    In other words, the two conditions must be 
    mutually exclusive. 
*/
bool should_run_update() 
{
    static int first_call = -1; 
    if (first_call < 0)
    {
        first_call = millis(); 
        return true; 
    }
    
    const int five_minutes = 300000; 
    const int fifteen_minutes = 900000;

    //NOTE: assuming that race condition is avoided if Entur has not responded within 5 minutes.
    const int time_since_first_call = millis() - first_call;
    if (time_since_first_call < five_minutes)
    {
        return false; 
    }

    //NOTE: some margin, as running loops take some time 
    return (millis() % fifteen_minutes < 50);
}

bool alarm_should_run() 
{
    if (!alarm_enabled) return false; 

    const int current_hour = Time.hour();
    const int current_minute = Time.minute();
    return (current_hour == alarm_hour && current_minute == alarm_minute);
}

void alarm_listener()
{
    if (should_run_update())
    {
        Serial.println("Extra update of entur");
        update_entur_subscription(); 
    }

    if (alarm_should_run())
    {
        tone(alarm_pin, 440, 200);
    }
}


void update_alarm_elements(Element elements[MAX_ELEMENT_COUNT])
{
    String next_alarm = String(alarm_hour) + ":" + String(alarm_minute); 

    elements[0] = {"next alarm", TOP_LEFT_CORNER};
    elements[1] = {next_alarm, CENTER};
}

Layout get_alarm_layout(Screen *screen)
{
    return {
        .screen = screen,
        .element_count = 2,
        .update_elements = update_alarm_elements,
        .update_frequency = 60000, //i.e. every minute
    };
}