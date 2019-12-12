#include "christmas.h"
#include "Arduino.h"

/*
    NOTE: This code is a modified version of: 
    https://github.com/AbhishekGhosh/Arduino-Buzzer-Tone-Codes/blob/master/Jingle-bells.ino
*/

const int C = 2100 / 3; 
const int D = 1870 / 3; 
const int E = 1670 / 3; 
const int f = 1580 / 3; 
const int G = 1400 / 3; 
const int R = 0; 

int lights_pin = -1; 
int speaker_pin = -1;

 // Set overall tempo
long tempo = 1000;

int melody[58] = {
    E, E, E, R,
    E, E, E, R,
    E, G, C, D, E, R,
    f, f, f,f, f, E, E,E, E, D ,D,E, D, R, G ,R,
    E, E, E, R,
    E, E, E, R,
    E, G, C, D, E, R,
    f, f, f,f, f, E, E, E,  G,G, f, D, C,R 
};
int rest_count = 10;
int tone_ = 0;
int beat = 0;
long duration = 0;
int MAX_COUNT = 58;//sizeof(melody) / 2;

static bool christmas_mode_on = false; 
int toggle_christmas_mode(String _) 
{
    christmas_mode_on = !christmas_mode_on;
    return 1; 
}

void play_tone(bool is_last_tone)
{
    long elapsed_time = 0;
    if (tone_ > 0) { // if this isn't a Rest beat, while the tone has
        //  played less long than 'duration', pulse speaker HIGH and LOW
        while (elapsed_time < duration && !is_last_tone) 
        {
            digitalWrite(speaker_pin,HIGH);
            delayMicroseconds(tone_ * 2); 
            digitalWrite(speaker_pin, LOW);
            delayMicroseconds(tone_ * 2); 
            elapsed_time += (tone_);   
        }
    }
}

void play_melody()
{
    for (int i=0; i<MAX_COUNT; i++) {
        tone_ = melody[i];
        beat = 50;

        duration = beat * tempo; // Set up timing
        delayMicroseconds(duration); 
        play_tone((i + 1 == MAX_COUNT));
    }
    toggle_christmas_mode(""); //Turn off when done
}

void setup_christmas_mode(int _lights_pin, int _speaker_pin)
{
    lights_pin = _lights_pin; 
    speaker_pin = _speaker_pin; 

    pinMode(lights_pin, OUTPUT); 
    pinMode(speaker_pin, OUTPUT); 

    Particle.function("toggle_christmas_mode", toggle_christmas_mode);
}


void christmas_mode()
{
    if (christmas_mode_on) 
    {
        digitalWrite(lights_pin, HIGH); 
        play_melody(); 
    } 
    else 
    {
        digitalWrite(lights_pin, LOW); 
    }
}
