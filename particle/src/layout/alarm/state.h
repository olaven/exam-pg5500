#ifndef EMBEDDED_EXAM_MODE_ALARM_STATE
#define EMBEDDED_EXAM_MODE_ALARM_STATE

extern int alarm_hour;
extern int alarm_minute;
extern int extra_minutes;

extern String alarm_from_location;
extern String alarm_to_location;
extern int arrive_by_hour;
extern int arrive_by_minute;

extern boolean alarm_enabled;   
extern String alarm_enabled_readable;

void entur_api_handler(const char *event, const char *data); 
void update_entur_subscription();
void add_extra_time();
int change_alarm_from_location(String input);
int change_alarm_to_location(String input);
int change_extra_minutes(String input);
int change_arrive_by_minute(String input);
int change_arrive_by_hour(String input);
int toggle_alarm_enabled(String input);

#endif