#include <SPI.h>
#include "SdFat.h"
#include "sd.h"
#include "sdios.h"

const int8_t DISABLE_CHIP_SELECT = -1;
#define SPI_SPEED SD_SCK_MHZ(5)
ArduinoOutStream cout(Serial); //NOTE: add back cout

SD init_sd_card(int chip_select_pin) {
    
    SD sd;

    if (!sd.begin(chip_select_pin, SPI_SPEED)) 
    {
        cout << F("\nerrorCode: ") << hex << showbase;
        cout << int(sd.card()->errorCode());
        cout << F("\n\n");  
    } 
    else 
    {
        Serial.println("SD initialized :D"); 
    }

    return sd;
}

