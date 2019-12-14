/* #ifndef EMBEDDED_EXAM_SD
#define EMBEDDED_EXAM_SD

#include "SdFat.h"
typedef SdFat SD; 
SD init_sd_card(int chip_select_pin);
void get_filenames_ending_with(String suffix, int sd_cs_pin, String *filenames, int filenames_count);

#endif */