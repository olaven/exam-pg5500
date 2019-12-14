/**
 * NOTE: commented out, as I have more or less decided to quit SD for this project
 */

/* #include <SPI.h>
#include "SdFat.h"
#include "sd.h"
#include "sdios.h"

const int8_t DISABLE_CHIP_SELECT = -1;
//#define SPI_SPEED SD_SCK_MHZ(4)
#define SPI_SPEED SD_SCK_MHZ(4)
ArduinoOutStream cout(Serial); //NOTE: add back cout

SD init_sd_card(int chip_select_pin) {
    
    SD sd; 
    //SD * sd_pointer = new SdFat(); //TODO: test this (is pointer)
    if(!sd.begin(chip_select_pin, SPI_SPEED))
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

void get_filenames_ending_with(String suffix, int sd_cs_pin, String * filenames, int filenames_count)
{
    SD sd = init_sd_card(sd_cs_pin);
    SdFile root; 
    SdFile file;
    
    if (!root.open("/"))
    {
        sd.errorHalt("open root failed");
    }
    
    int counter = 0; 
    while (file.openNext(&root, O_RDONLY) && counter < filenames_count)
    {
        char name[50];
        file.getName(name, 50);
        String name_as_string = String(name);

        if (name_as_string.toLowerCase().endsWith(suffix))
        {
            filenames[counter] = name_as_string; 
            Serial.print("adding: ");
            Serial.println(name_as_string);
        }
        
        counter++;
        file.close();
    }
}
 */