#include <SPI.h>
#include "SdFat.h"
#include "sd.h"

const int8_t DISABLE_CHIP_SELECT = -1;
#define SPI_SPEED SD_SCK_MHZ(4)

SD init_sd_card(int chip_select_pin) {


    if (DISABLE_CHIP_SELECT < 0) {
        Serial.println("You should disable chip select."); 
    }
    
    SD sd;
    if (!sd.begin(chip_select_pin, SPI_SPEED)) {
        Serial.println("SD initialization failed."); 
    }

    return sd;
}

