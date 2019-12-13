#ifndef EMBEDDED_EXAM_MODE_ALARM
#define EMBEDDED_EXAM_MODE_ALARM

Layout get_alarm_layout(Screen *screen);
void setup_alarm_io(int _speaker_pin);
void alarm_listener(); 

#endif