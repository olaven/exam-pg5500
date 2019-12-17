#include "Particle.h"


int fire_sensor_pin;
bool send_fire_email; //https://www.youtube.com/watch?v=1EBfxjSFAxQ&feature=youtu.be
String fire_email = "lagasild@protonmail.com"; //NOTE: anonymous email made for exam purposes 


int change_fire_email(String _fire_email) 
{
    fire_email = _fire_email; 
    return 0; 
}

void setup_fire_sensor(int _fire_sensor_pin, bool _send_email)
{
    pinMode(_fire_sensor_pin, INPUT);
    fire_sensor_pin = _fire_sensor_pin;
    send_fire_email = _send_email; 
    
    Particle.variable("fire_email", fire_email);
    Particle.function("change_fire_email", change_fire_email);
}

bool is_detecting_fire()
{
    const int total_read_count = 20; 
    int total = 0; 

    for(int i = 0; i < total_read_count; i++)
    {
        total += analogRead(fire_sensor_pin);
    }

    int average = total / total_read_count; 
    return (average > 1500);
} 

void check_fire_sensor() 
{
    if (is_detecting_fire() && send_fire_email)
    {
        static int last_fire_event_publish = -1; //NOTE: only send emails every 5 minutes (300000 ms)                    
        if (last_fire_event_publish == -1 || ((millis() - last_fire_event_publish) > 300000)) 
        {
            Particle.publish("fire_event", String::format("{ \"email\": \"%s\" }", fire_email.c_str()), PRIVATE);
            last_fire_event_publish = millis(); 
        }
    }
}
