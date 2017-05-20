#include "alm.h"

void lcd_clear()
{
        LCD_PORT &= ~(1<<LCD_RS_BIT);
	lcd_command(0x01);     // Clear screen DDRAM 
        _delay_ms(10);
        lcd_command(0x80);
        _delay_ms(5);
}

void lcd_pulseEnable()
{
       LCD_PORT &= ~(1<<LCD_EN_BIT);
       _delay_us(10);
       LCD_PORT |=  (1<<LCD_EN_BIT);
       _delay_us(10);
       LCD_PORT &= ~(1<<LCD_EN_BIT);
       _delay_us(200);
}
  

void lcd_command(char cmd)
{
        if(cmd & 0x10)
	  LCD_PORT 	|= 1<<LCD_LCD4_BIT;
        else
          LCD_PORT &= ~(1<<LCD_LCD4_BIT);
          
        if(cmd & 0x20)
	  LCD_PORT 	|= 1<<LCD_LCD5_BIT;
        else
          LCD_PORT &= ~(1<<LCD_LCD5_BIT);
          
        if(cmd & 0x40)
	  LCD67_PORT 	|= 1<<LCD_LCD6_BIT;
        else
        LCD67_PORT &= ~(1<<LCD_LCD6_BIT);
        
        if(cmd & 0x80)
	  LCD67_PORT 	|= 1<<LCD_LCD7_BIT;
        else
          LCD67_PORT &= ~(1<<LCD_LCD7_BIT);
          
        lcd_pulseEnable();
        
       if(cmd & 0x01)
	  LCD_PORT 	|= 1<<LCD_LCD4_BIT;
        else
          LCD_PORT &= ~(1<<LCD_LCD4_BIT);
          
        if(cmd & 0x02)
	  LCD_PORT 	|= 1<<LCD_LCD5_BIT;
        else
          LCD_PORT &= ~(1<<LCD_LCD5_BIT);
          
        if(cmd & 0x04)
	  LCD67_PORT 	|= 1<<LCD_LCD6_BIT;
        else
        LCD67_PORT &= ~(1<<LCD_LCD6_BIT);
        
        if(cmd & 0x08)
	  LCD67_PORT 	|= 1<<LCD_LCD7_BIT;
        else
          LCD67_PORT &= ~(1<<LCD_LCD7_BIT);

        lcd_pulseEnable();
        _delay_us(500);
}

/* Initialize LCD pins and set LCD to 4-bit mode and set display parameters */
void lcd_init()
{
	LCD_DDR 	|= (1<<LCD_LCD4_BIT) | (1<<LCD_LCD5_BIT) | (1<<LCD_RS_BIT) | (1<<LCD_EN_BIT);
	LCD67_DDR 	|= (1<<LCD_LCD6_BIT) | (1<<LCD_LCD7_BIT);
        
        _delay_ms(60);
        LCD_PORT &= (1<<LCD_EN_BIT | 1<<LCD_RS_BIT);
        
	// LCD Initialization sequence for setting it to 4-bit mode

	_delay_ms(20);
	LCD_PORT 		|=  ((1<<LCD_LCD4_BIT)|(1<<LCD_LCD5_BIT));
	LCD67_PORT 		&= ~((1<<LCD_LCD6_BIT)|(1<<LCD_LCD7_BIT));
        lcd_pulseEnable();
	_delay_ms(20);
	LCD_PORT 		|=  ((1<<LCD_LCD4_BIT)|(1<<LCD_LCD5_BIT));
	LCD67_PORT 		&= ~((1<<LCD_LCD6_BIT)|(1<<LCD_LCD7_BIT));
	lcd_pulseEnable();
        _delay_ms(20);
	LCD_PORT 		|=  ((1<<LCD_LCD4_BIT)|(1<<LCD_LCD5_BIT));
	LCD67_PORT 		&= ~((1<<LCD_LCD6_BIT)|(1<<LCD_LCD7_BIT));
	lcd_pulseEnable();
        _delay_ms(20);
	LCD_PORT 		&=  ~(1<<LCD_LCD4_BIT);
        LCD_PORT 		|=   (1<<LCD_LCD5_BIT);
	LCD67_PORT 		&= ~((1<<LCD_LCD6_BIT)|(1<<LCD_LCD7_BIT));
	lcd_pulseEnable();
        _delay_ms(10);
   
        LCD_PORT &= (1<<LCD_RS_BIT);

        lcd_command(0x01);  // Clear Display and DDRAM
	lcd_command(0x20);  // Set to 2-Line display
        lcd_command(0x01);  
        
	lcd_command(0x06);  // Entry Mode-Automatic Increment
        lcd_command(0x0C);  // Switch on display - no cursor 
}

void lcd_display(char *data)
{    
 	while(*data)
 	{
        LCD_PORT |= (1<<LCD_RS_BIT);
        lcd_command(*data++);
 	}
}

void lcd_displaySymbol(char symbol)
{
  LCD_PORT |= 1<<LCD_RS_BIT;
  lcd_command(symbol);
}


void lcd_gotoXY(char x, char y)
{
  char address;
  switch(x)
  {
     case 0: address = 0x00; break; //Starting address of 1st line
     case 1: address = 0x40; break; //Starting address of 2nd line
     case 2: address = 0x14; break; //Starting address of 3rd line
     case 3: address = 0x54; break; //Starting address of 4th line
     default: ; 
  }
  
  address +=y;
  
  lcd_gotoAddr(address);
}


void lcd_gotoAddr(char addr)
{
    char cmd = 0x80 | addr;
    LCD_PORT &= ~(1<<LCD_RS_BIT); 
    lcd_command(cmd);
}

void lcd_createChar(uint8_t location,uint8_t charmap[])
{
  location &= 0x7; // we only have 8 locations 0-7
  
  LCD_PORT &= ~(1<<LCD_RS_BIT);
  lcd_command(0x40 | (location << 3));
  uint8_t i=0;
  for (i=0; i<8; i++)
  {
    LCD_PORT |= (1<<LCD_RS_BIT);
    lcd_command(charmap[i]);
  }

}



