/******************************************************/
//       THIS IS A GENERATED FILE - DO NOT EDIT       //
/******************************************************/

#include "application.h"
#line 1 "/Users/olav/Documents/skole/kristiania/5_semester/embedded_systems/eksamen/particle/src/particle.ino"
#include <Adafruit_ST7735.h>

void setup();
int gong(String command);
void loop();
#line 3 "/Users/olav/Documents/skole/kristiania/5_semester/embedded_systems/eksamen/particle/src/particle.ino"
Servo myservo; // create servo object to control a servo
               // a maximum of eight servo objects can be created

int pos = 0; // variable to store the servo position

#define cs A2
#define dc D0
#define rst A0

Adafruit_ST7735 tft = Adafruit_ST7735(cs, dc, rst); // hardware spi

int photosensor = A1;
int sensor_value;

void setup()
{

  tft.initG();

  tft.fillScreen(ST7735_BLACK);

  tft.setCursor(0, 0);
  tft.setTextColor(ST7735_WHITE);
  tft.setTextWrap(true);
  tft.print("Lorem ipsum dolor sit amet, consectetur adipiscing elit. Curabitur adipiscing ante sed nibh tincidunt feugiat. Maecenas enim massa, fringilla");

  tft.drawLine(0, 0, tft.width() - 1, tft.height() - 1, ST7735_YELLOW);
  tft.drawLine(tft.width() - 1, 0, 0, tft.height() - 1, ST7735_YELLOW);

  tft.drawPixel(0, tft.height() / 2, ST7735_GREEN);

  Serial.begin(9600);
  Particle.function("gong", gong);
  myservo.attach(D1);
  myservo.write(25);
  pinMode(D7, OUTPUT);

  pinMode(D5, OUTPUT);
  digitalWrite(D5, HIGH);
}

int gong(String command) // when "gong" is called from the cloud, it will
{                        // be accompanied by a string.
  if (command == "now")  // if the string is "now", ring the gong once.
  {
    myservo.write(0);       // move servo to 0° - ding!
    digitalWrite(D7, HIGH); // flash the LED (as an indicator)
    delay(100);             // wait 100 ms
    myservo.write(25);      // move servo to 25°
    digitalWrite(D7, LOW);  // turn off LED
    return 1;               // return a status of "1"
  }
  else if (command == "alarm") // if the string is "alarm",
  {
    for (int i = 0; i < 3; i++) // ring the gong 3 times.
    {
      myservo.write(0);       // move servo to 0° - ding!
      digitalWrite(D7, HIGH); // flash the LED
      delay(100);             // wait 100 ms
      myservo.write(25);      // move servo to 25°
      digitalWrite(D7, LOW);  // turn off LED
      delay(1000);            // wait 1 second between gongs
    }
    return 2; // return a status of "2"
  }

  return 0;
}

void loop()

{

  int sensorValue = analogRead(photosensor);

  if (sensorValue < 100)
  {
    myservo.write(0);
  }
  else
  {
    int pos = map(sensorValue, 100, 1600, 0, 127);
    Serial.print("pos");
    Serial.println(pos);
    myservo.write(pos);
  }
  delay(50);
  Serial.print("Sensor value: ");
  Serial.println(sensorValue);
}