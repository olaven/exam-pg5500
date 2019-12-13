#include "Particle.h"

const int num_readings = 10;

int readings[num_readings]; 
int read_index = 0;         
int total = 0;  
int average = 0;

int fire_sensor_pin; 

/**
 * NOTE: This is an adapted 
 * version of the Arduino
 * analog->smoothing example 
*/

void setup_fire_sensor(int _fire_sensor_pin)
{
    fire_sensor_pin = _fire_sensor_pin;
    for (int this_reading = 0; this_reading < num_readings; this_reading++)
    {
        readings[this_reading] = 0;
    }
}

bool is_detecting_fire()
{
    total = total - readings[read_index];
    readings[read_index] = analogRead(fire_sensor_pin);
    total = total + readings[read_index];
    read_index = read_index + 1;

    if (read_index >= num_readings)
    {
        read_index = 0;
    }

    average = total / num_readings;

    return average > 35;
}

void check_fire_sensor() 
{
    if (is_detecting_fire())
    {
        Serial.println("Detected fire!");
        Particle.publish("fire_event", PRIVATE);
        delay(1000);
    }
}
