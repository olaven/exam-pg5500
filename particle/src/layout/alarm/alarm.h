#ifndef EMBEDDED_EXAM_MODE_ALARM
#define EMBEDDED_EXAM_MODE_ALARM

Layout get_alarm_layout(Screen *screen);
void setup_alarm(int _speaker_pin);
void alarm_listener(); 

#endif