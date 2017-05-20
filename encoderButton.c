#include "alm.h"

volatile int encoderButton_count;
volatile uint8_t encoderButton_buttonPress; // for registering encoder button push event 1-if button is pushed 
volatile uint8_t encoderButton_dir=0; // 1-clockwise , 0-anti-clockwise

void encoderButton_init()
{
	ENCODER_DDR &= ~(1<<ENCODER_DIRB_BIT|1<<ENCODER_DIRA_BIT|1<<ENCODER_BUTTON_BIT);
	EICRA |= 0x05;    // Interrupt triggers for Encoder Direction Pin A and -INT0(on falling/rising edge)
	
	EICRA |= 0x30;  // Interrupts triggers for Falling edge of button pin

	EIMSK |= (0x07); // Enable Interrupts for 1-direction(DIR A) pin and button
        
        sei();
         encoderButton_count=0;
         encoderButton_buttonPress=0;
         encoderButton_dir=0;
}

void encoderButton_waitForButtonPress()
{
	while(!encoderButton_buttonPress)
	{}
	encoderButton_buttonPress=0;
	_delay_ms(5);    // crude method for debouncing button
	encoderButton_buttonPress=0;
}

ISR(INT2_vect)
{
  encoderButton_buttonPress=1;
      //switch(current_pointer)
      //{
      //  case BACK:
      //  display_loadScreen();
     // }
}
ISR(INT0_vect)
{
  static uint8_t old_AB = 3;  //lookup table index
  static int8_t encval = 0;   //encoder value  
  static const int8_t enc_states [] PROGMEM = {0,-1,1,0,1,0,0,-1,-1,0,0,1,0,1,-1,0};  //encoder lookup table
 
  old_AB <<=2;  //remember previous state
  old_AB |= ( ENCODER_PIN & 0x03 );
  encval += pgm_read_byte(&(enc_states[( old_AB & 0x0f )]));


  if( encval > 1 )         //two steps forward
  {  
   encoderButton_count+=1;
   encoderButton_dir=1;
    encval = 0;
  }
  else if( encval < -1 )   //two steps backwards
  {  
    encoderButton_count-=1;
    encoderButton_dir=0;
    encval = 0;
  }
  	
}

ISR(INT1_vect)
{
  static uint8_t old_AB1 = 3;  //lookup table index
  static int8_t encval1 = 0;   //encoder value  
  static const int8_t enc_states1 [] PROGMEM = {0,-1,1,0,1,0,0,-1,-1,0,0,1,0,1,-1,0};  //encoder lookup table
 
  old_AB1 <<=2;  //remember previous state
  old_AB1 |= ( ENCODER_PIN & 0x03 );
  encval1 += pgm_read_byte(&(enc_states1[( old_AB1 & 0x0f )]));


  if( encval1 > 1 )         //two steps forward
  {  
   encoderButton_count+=1;
   encoderButton_dir=1;
    encval1 = 0;
  }
  else if( encval1 < -1 )   //two steps backwards
  {  
    encoderButton_count-=1;
    encoderButton_dir=0;
    encval1 = 0;
  }
  	
}
/*
int main(void)
{
	//sdCard_init();
        lcd_init();
        uart_init(9600);
        encoderButton_init();
        char count[10];
        char cl[20];
        char dir[2];
        int i=0;
        memset(cl,0,20);
        memset(dir,0,2);
        memset(count,0,10);
        lcd_display("Encoder Count");
        lcd_gotoXY(2,0);
        lcd_display("Dir:");
        
        while(1)
        {
         itoa(encoderButton_count,count,10);
         itoa(encoderButton_dir,dir,2);
         
         lcd_gotoXY(1,0);
         lcd_display(count);
         lcd_gotoXY(2,5);
         lcd_display(dir);
         
         uart_write(count);
         uart_write("\n");
         
         _delay_ms(15);
         
         lcd_gotoXY(1,0);
         lcd_display("      ");
         lcd_gotoXY(2,5);
         lcd_display("  ");
        } 
              
}
*/
