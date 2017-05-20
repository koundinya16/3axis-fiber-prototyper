#ifndef display_h
#define display_h

#define HOME_1_STRING 
#define HOME_2_1_STRING "X:"
#define HOME_2_2_STRING "Y:"
#define HOME_2_3_STRING "Z:"
#define HOME_3_1_STRING "SD-card"
#define HOME_3_STRING ""

#define TEMP_SYMBOL 0
#define ALM_SYMBOL 1
#define SDCARD_SYMBOL 2
#define HEADCOMPRESSION_SYMBOL 3
#define FEEDRATE_SYMBOL 4
#define TIME_SYMBOL 5
#define JOBDONE_SYMBOL 6
#define DEGREE_SYMBOL 223

#define HOME_SCREEN




void display_init();
void display_home();
void ftoa(float f, char *str, uint8_t precision);

#endif
