#include "Particle.h"

int water_sensor_pin;
bool send_water_email;
int last_water_event_publish = -1; 

void setup_water_sensor(int _water_sensor_pin, bool _send_email)
{
    pinMode(_water_sensor_pin, INPUT);
    water_sensor_pin = _water_sensor_pin;
    send_water_email = _send_email;


    Serial.println(String(_water_sensor_pin) + " is the water sensor pin");
    Serial.println(String(water_sensor_pin) + " is updated value");
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
        Serial.println("Detected water");
        //TODO: setup event webhook
        if ((millis() - last_water_event_publish) > 9000000) //i.e. do not sent more than once/15 min
        {
            Particle.publish("water_event", PRIVATE);
            last_water_event_publish = millis(); 
        }
    }
}
