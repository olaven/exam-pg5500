#include "Particle.h"


int fire_sensor_pin;
bool send_fire_email; //https://www.youtube.com/watch?v=1EBfxjSFAxQ&feature=youtu.be
int last_fire_event_publish = -1; 


void setup_fire_sensor(int _fire_sensor_pin, bool _send_email)
{
    pinMode(_fire_sensor_pin, INPUT);
    fire_sensor_pin = _fire_sensor_pin;
    send_fire_email = _send_email; 
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
    return (average > 1000);
} 

void check_fire_sensor() 
{
    if (is_detecting_fire() && send_fire_email)
    {
        Serial.println("Detected fire!");
        if ((millis() - last_fire_event_publish) > 3000000) //i.e. do not sent more than once/5 min
        {
            Particle.publish("fire_event", PRIVATE);
        }
    }
}
