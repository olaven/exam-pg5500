#include "Particle.h"

int water_sensor_pin;
bool send_water_email;
String water_email = "lagasild@protonmail.com"; //NOTE: anonymous email made for exam purposes

int change_water_email(String _water_email) 
{
    water_email = _water_email;
    return 0; 
}

void setup_water_sensor(int _water_sensor_pin, bool _send_email)
{
    pinMode(_water_sensor_pin, INPUT);
    water_sensor_pin = _water_sensor_pin;
    send_water_email = _send_email;
    
    Particle.variable("water_email", water_email); 
    Particle.function("change_water_email", change_water_email); 
}

bool is_detecting_water()
{
    const int water_value = analogRead(water_sensor_pin);
    return water_value > 1000; 
}

void check_water_sensor()
{
    if (send_water_email && is_detecting_water())
    {
        static int last_water_event_publish = -1;
        if (last_water_event_publish == -1 || ((millis() - last_water_event_publish) > 900000)) //i.e. do not sent more than once/15 min
        {
            Particle.publish("water_event", String::format("{ \"email\": \"%s\" }", water_email.c_str()));
            last_water_event_publish = millis(); 
        }
    }
}
