#include "alm.h"


uint8_t temp_symbol_map[8]={
	0b00100,
	0b01010,
	0b01010,
	0b01010,
	0b01010,
	0b10101,
	0b10001,
	0b01110

};
uint8_t alm_symbol_map[8]={	
       0b00100,
	0b01010,
	0b01110,
	0b01010,
	0b10101,
	0b10111,
	0b10101,
	0b11101  
};

uint8_t sdcard_symbol_map[8]={0b00000,
	0b11110,
	0b11010,
	0b11111,
	0b11111,
	0b11111,
	0b11111,
	0b00000};

uint8_t headCompression_symbol_map[8]= {
	0b01110,
	0b01110,
	0b01110,
	0b10001,
	0b01110,
	0b10001,
	0b01010,
	0b00100
};

uint8_t feedRate_symbol_map[8]=  {
	0b11111,
	0b10000,
	0b11111,
	0b10000,
	0b10111,
	0b10101,
	0b00110,
	0b00101
};

uint8_t time_symbol_map[8]= {
	0b11111,
	0b11111,
	0b10001,
	0b11011,
	0b11011,
	0b11011,
	0b11111,
	0b11111
};

uint8_t jobDone_symbol_map[8]= {
	0b11111,
	0b11111,
	0b00000,
	0b11011,
	0b11011,
	0b01011,
	0b00011,
	0b11111
};

uint8_t current_pointer=0;

void display_init()
{
  lcd_init();
  encoderButton_init();
  
  lcd_createChar(TEMP_SYMBOL,temp_symbol_map);
  lcd_createChar(ALM_SYMBOL,alm_symbol_map);
  lcd_createChar(SDCARD_SYMBOL,sdcard_symbol_map);
  lcd_createChar(HEADCOMPRESSION_SYMBOL,headCompression_symbol_map);
  lcd_createChar(FEEDRATE_SYMBOL,feedRate_symbol_map);
  lcd_createChar(TIME_SYMBOL,time_symbol_map);
  lcd_createChar(JOBDONE_SYMBOL,jobDone_symbol_map);
  
  lcd_gotoXY(0,0);
}


void display_home()
{
  lcd_gotoXY(0,0);
  lcd_display("FABHEADS ");
  lcd_displaySymbol(ALM_SYMBOL);
  lcd_display(" v1");
  
  lcd_gotoXY(1,0);
  lcd_display("X:");
  lcd_gotoXY(1,7);
  lcd_display("Y:");
  lcd_gotoXY(1,13);
  lcd_display("Z:");
  
  lcd_gotoXY(2,1);
  lcd_displaySymbol(TIME_SYMBOL);
  lcd_gotoXY(2,4);
  lcd_displaySymbol(":");
  
  lcd_gotoXY(2,8);
  lcd_displaySymbol(JOBDONE_SYMBOL);
  lcd_gotoXY(2,12);
  lcd_display("% done");
  
  lcd_gotoXY(3,0);
  lcd_displaySymbol(TEMP_SYMBOL);
  lcd_gotoXY(3,3);
  lcd_displaySymbol((char)DEGREE_SYMBOL);
  
  lcd_gotoXY(3,6);
  lcd_displaySymbol(HEADCOMPRESSION_SYMBOL);
  lcd_gotoXY(3,10);
  lcd_display("%");
  
  lcd_gotoXY(3,12);
  lcd_displaySymbol(FEEDRATE_SYMBOL);
  lcd_gotoXY(3,16);
  lcd_display("%");

  char x_pos[8];
  char y_pos[8];
  char z_pos[8];
  char time_elapsed_hrs[2];
  char time_elapsed_min[2];
  char feed_rate[3];
  char compression_factor[3];
  char temp[3];
  char job_percentage[3];

  memset(x_pos,0,8);
  memset(y_pos,0,8);
  memset(z_pos,0,8);
  
  while(!encoderButton_buttonPress)
  {
  	ftoa((X_steps*STEP_DIST_RESOLUTION),x_pos,2);
  	ftoa((Y_steps*STEP_DIST_RESOLUTION),y_pos,2);
  	ftoa((Z_steps*STEP_DIST_RESOLUTION),z_pos,2);
  	itoa(compressionFactor,compression_factor,10);
  	itoa(feedRate,feed_rate,10);
  	itoa(temperature,temp,10);
  	itoa(timeElapsed_hours,time_elapsed_hrs,10);
  	itoa(timeElapsed_minutes,time_elapsed_min,10);
  	itoa(jobPercentage,job_percentage,10);

  	lcd_gotoXY(1,2);
  	lcd_display(x_pos);
  	lcd_gotoXY(1,9);
  	lcd_display(y_pos);
  	lcd_gotoXY(1,15);
  	lcd_display(z_pos);

  	lcd_gotoXY(2,2);
  	lcd_display(time_elapsed_hrs);
  	lcd_gotoXY(2,5);
  	lcd_display(time_elapsed_min);

  	lcd_gotoXY(2,9);
  	lcd_display(job_percentage);

  	lcd_gotoXY(3,1);
  	lcd_display(temp);

  	lcd_gotoXY(3,7);
  	lcd_display(compression_factor);

  	lcd_gotoXY(3,13);
  	lcd_display(feed_rate);

  	if(!pf_mount(&sdCard_Pointer))
  	{
  		lcd_gotoXY(3,19);
  		lcd_displaySymbol(SDCARD_SYMBOL);
  	}
  	_delay_ms(20);
  }
  
}



void ftoa(float f, char *str, uint8_t precision) 
{
  uint8_t i, j, divisor = 1;
  int8_t log_f;
  int32_t int_digits = (int)f;             //store the integer digits
  float decimals;
  char s1[12];

  memset(str, 0, sizeof(str));  
  memset(s1, 0, 10);

  if (f < 0) {                             //if a negative number 
    str[0] = '-';                          //start the char array with '-'
    f = abs(f);                            //store its positive absolute value
  }
  log_f = ceil(log10(f));                  //get number of digits before the decimal
  if (log_f > 0) {                         //log value > 0 indicates a number > 1
    if (log_f == precision) {              //if number of digits = significant figures
      f += 0.5;                            //add 0.5 to round up decimals >= 0.5
      itoa(f, s1, 10);                     //itoa converts the number to a char array
      strcat(str, s1);                     //add to the number string
    }
    else if ((log_f - precision) > 0) {    //if more integer digits than significant digits
      i = log_f - precision;               //count digits to discard
      divisor = 10;
      for (j = 0; j < i; j++) divisor *= 10;    //divisor isolates our desired integer digits 
      f /= divisor;                             //divide
      f += 0.5;                            //round when converting to int
      int_digits = (int)f;
      int_digits *= divisor;               //and multiply back to the adjusted value
      itoa(int_digits, s1, 10);
      strcat(str, s1);
    }
    else {                                 //if more precision specified than integer digits,
      itoa(int_digits, s1, 10);            //convert
      strcat(str, s1);                     //and append
    }
  }

  else {                                   //decimal fractions between 0 and 1: leading 0
    s1[0] = '0';
    strcat(str, s1);
  }

  if (log_f < precision) {                 //if precision exceeds number of integer digits,
    decimals = f - (int)f;                 //get decimal value as float
    strcat(str, ".");                      //append decimal point to char array

    i = precision - log_f;                 //number of decimals to read
    for (j = 0; j < i; j++) {              //for each,
      decimals *= 10;                      //multiply decimals by 10
      if (j == (i-1)) decimals += 0.5;     //and if it's the last, add 0.5 to round it
      itoa((int)decimals, s1, 10);         //convert as integer to character array
      strcat(str, s1);                     //append to string
      decimals -= (int)decimals;           //and remove, moving to the next
    }
  }
}


int main(void)
{
   
  display_init();
  display_home();
  lcd_clear();
}



