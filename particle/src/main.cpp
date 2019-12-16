#include "./render/render.h"
#include "./layout/layout.h"
#include "./layout/temperature/temperature.h"
#include "./layout/clock/clock.h"
#include "./layout/alarm/alarm.h"
#include "./layout/message/message.h"
#include "./christmas/christmas.h"
#include "./fire/fire.h"
#include "./water/water.h"

//PINS
// -- screen
const int screen_cs = A2;
const int screen_dc = D0;
const int screen_rst = A0;
// -- buttons 
const int next_button = D2; 
const int previous_button = D1; 
// - sensors
const int temperature_sensor = A1;
const int fire_sensor_pin = A6;
const int water_sensor_pin = A7; 
// - christmas mode 
const int lights_pin = D3;
const int speaker_pin = RX;  

SerialDebugOutput debugOutput; //adding extra logging
Screen screen = init_screen(screen_cs, screen_dc, screen_rst);

const int layout_count = 4;
struct Layout layouts[layout_count] = { //TODO: move this to separate file 
  get_temperature_layout(&screen, temperature_sensor), 
  get_clock_layout(&screen),
  get_message_layout(&screen),
  get_alarm_layout(&screen),
};
LayoutState layout_state = init_layout_state(next_button, previous_button, speaker_pin, layout_count, layouts);



void setup()
{
  Serial.begin(9600);
  Particle.publishVitals(5);
  Time.zone(1);

  setup_temperature(); 
  setup_message_updater();
  setup_fire_sensor(fire_sensor_pin, false);
  setup_water_sensor(water_sensor_pin, true);
  setup_alarm_io(speaker_pin);
  setup_screen(&screen);
  setup_christmas_mode(lights_pin, speaker_pin);
}


void loop()
{
  check_fire_sensor();
  check_water_sensor();
  alarm_listener();
  christmas_mode();
  render(&layout_state);
}
