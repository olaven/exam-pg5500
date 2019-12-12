/*
NOTE: This file is just used to 
test if SD connection is actually working 
*/
/*
#include <SPI.h>
#include "SdFat.h"
#include "sdios.h"
//
// Set DISABLE_CHIP_SELECT to disable a second SPI device.
// For example, with the Ethernet shield, set DISABLE_CHIP_SELECT
// to 10 to disable the Ethernet controller.
const int8_t DISABLE_CHIP_SELECT = -1;
#define SPI_SPEED SD_SCK_MHZ(4)
//------------------------------------------------------------------------------
// File system object.
SdFat sd;
ArduinoOutStream cout(Serial);
char cinBuf[40];
ArduinoInStream cin(Serial, cinBuf, sizeof(cinBuf));
// SD card chip select
int chipSelect;
void setup()
{
    Serial.begin(9600);
    if (DISABLE_CHIP_SELECT < 0)
    {
        cout << F(
            "\nBe sure to edit DISABLE_CHIP_SELECT if you have\n"
            "a second SPI device.  For example, with the Ethernet\n"
            "shield, DISABLE_CHIP_SELECT should be set to 10\n"
            "to disable the Ethernet controller.\n");
    }
    cout << F(
        "\nSD chip select is the key hardware option.\n"
        "Common values are:\n"
        "Arduino Ethernet shield, pin 4\n"
        "Sparkfun SD shield, pin 8\n"
        "Adafruit SD shields and modules, pin 10\n");
}
bool firstTry = true;
void loop()
{
    delay(200);
    if (!firstTry)
    {
        cout << F("\nRestarting\n");
    }
    firstTry = false;

    chipSelect = D4;
    
    if (!sd.begin(chipSelect, SPI_SPEED))
    {
        if (sd.card()->errorCode())
        {
            cout << F(
                "\nSD initialization failed.\n"
                "Do not reformat the card!\n"
                "Is the card correctly inserted?\n"
                "Is chipSelect set to the correct value?\n"
                "Does another SPI device need to be disabled?\n"
                "Is there a wiring/soldering problem?\n");
            cout << F("\nerrorCode: ") << hex << showbase;
            cout << int(sd.card()->errorCode());
            cout << F(", errorData: ") << int(sd.card()->errorData());
            cout << dec << noshowbase << endl;
            return;
        }

        cout << F("begin failed, can't determine error type\n");
        return;
    }
    cout << F("\nCard successfully initialized.\n");
}
*/