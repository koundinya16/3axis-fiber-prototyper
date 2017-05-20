#include "alm.h"

uint8_t sdCard_detect_flag;
uint8_t sdCard_mounted_flag;

FATFS sdCard_Pointer;
uint8_t sdCard_opResult;

void sdCard_init()
{
  SD_DETECT_DDR &= ~(1<<SD_DETECT_BIT);		// Set SD card Detect pin as input
  //EICRB |= 0x01; 							// Interrupt triggers for any change in SD-Detect pin
  //EIMSK  |= 1<<4; 							// Enable Interrupt on INT4 pin-SDDETECT Pin
 // sei();
}


//uint8_t sdCard_mount()
//{
//	 return pf_mount(&sdcard_Pointer);
//}


char *sdCard_readFile(char* fileName , int numOfBytes, char* buffer)
{
  pf_open(fileName);
}

/*
ISR(INT4_vect)
{
	sdCard_detect_flag=1;

}
*/


char* sdCard_perror(uint8_t error_code)
{
  char* error_msg;
  switch(error_code)
        {
          case 0:
          return "Operation Successfull"; 
          break;
          
          case 1:
          return "Error in Disk Read function";
          break;
          
          case 2:
          return "Storage device could not be initialized due to hardware  error or no medium";
          break;
          
          case 3:
          return "No File";
          break;
          
          case 4:
          return "Not Open";
          break;
          
          case 5:
          return "Not Enabled";
          break;
          
          case 6:
          return "No valid FAT partition";
          break;
   
          
        }
  
}

