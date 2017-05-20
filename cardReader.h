#ifndef cardReader_h
#define cardReader_h


uint8_t sdCard_detect_flag;
uint8_t sdCard_mounted_flag;

FATFS sdCard_filePointer;
uint8_t sdCard_opResult;


void sdCard_init();
char *sdCard_readFile(char* fileName , int numOfBytes, char* buffer);
char* sdCard_perror(uint8_t error_code);

#endif
