#include "christmas.h"
#include "Arduino.h"

/*
    NOTE: This code is a modified version of: 
    https://github.com/AbhishekGhosh/Arduino-Buzzer-Tone-Codes/blob/master/Jingle-bells.ino
*/

const int C = 2100; 
const int D = 1870; 
const int E = 1670; 
const int f = 1580; 
const int G = 1400; 
const int R = 0; 

int button_pin = -1; 
int lights_pin = -1; 
int speaker_pin = -1; 

int melody[] = {
    E, E, E, R,
    E, E, E, R,
    E, G, C, D, E, R,
    f, f, f,f, f, E, E,E, E, D ,D,E, D, R, G ,R,
    E, E, E, R,
    E, E, E, R,
    E, G, C, D, E, R,
    f, f, f,f, f, E, E, E,  G,G, f, D, C,R 
};
int rest_count = 100;
int tone_ = 0;
int beat = 0;
long duration = 0;

void play_melody() 
{
    long elapsed_time = 0;
    if (tone_ > 0) { // if this isn't a Rest beat, while the tone has
        //  played less long than 'duration', pulse speaker HIGH and LOW
        while (elapsed_time < duration) {
            digitalWrite(speaker_pin,HIGH);
            delayMicroseconds(tone_ / 2);
            // DOWN
            digitalWrite(speaker_pin, LOW);
            delayMicroseconds(tone_ / 2);
            // Keep track of how long we pulsed
            elapsed_time += (tone_);
        }
    }
    else { // Rest beat; loop times delay
        for (int j = 0; j < rest_count; j++) { // See NOTE on rest_count
            delayMicroseconds(duration); 
        } 
    }                                
}

void setup_christmas_mode(int _button_pin, int _lights_pin, int _speaker_pin)
{
    button_pin = _button_pin; 
    lights_pin = _lights_pin; 
    speaker_pin = _speaker_pin; 

    pinMode(button_pin, INPUT); 
    pinMode(lights_pin, OUTPUT); 
    pinMode(speaker_pin, OUTPUT); 
}

void christmas_mode()
{
    if (digitalRead(button_pin)) 
    {
        digitalWrite(lights_pin, HIGH); 
        play_melody(); 
    } 
    else 
    {
        digitalWrite(lights_pin, LOW); 
    }
}
