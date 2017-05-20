#include "alm.h"

#define CS (1<<PB2)
#define MOSI (1<<PB3)
#define MISO (1<<PB4)
#define SCK (1<<PB5)
#define CS_DDR DDRB
#define CS_ENABLE() (PORTB &= ~CS)
#define CS_DISABLE() (PORTB |= CS)

void sdSPI_init()
 {
 	// SD card circuit select as output
    SD_DDR |= 1<<SD_CS_BIT | 1<<SD_MOSI_BIT | 1<<SD_CLK_BIT; 
    
    // Enable pullup resistor for MISO line, might not be needed
    SD_PORT |= 1<<SD_MISO_BIT; 
        
    // Enable SPI, master, set clock rate fck/128
    SPCR = (1<<SPE) | (1<<MSTR) | (1<<SPR0) | (1<<SPR1);
}

unsigned char sdSPI_write(BYTE ch) 
{
    SPDR = ch;
    while(!(SPSR & (1<<SPIF))) {}       
    return SPDR;
}

void sdSPI_enable()
{
	SD_PORT &= ~(1<<SD_CS_BIT);
}

void sdSPI_disable()
{
	SD_PORT |= (1<<SD_CS_BIT);
}

void sdSPI_command(unsigned char cmd, unsigned long arg,unsigned char crc, unsigned char read)
{
    unsigned char i, buffer[8];
        
    sdSPI_enable();
    sdSPI_write(cmd);
    sdSPI_write(arg>>24);
    sdSPI_write(arg>>16);
    sdSPI_write(arg>>8);
    sdSPI_write(arg);
    sdSPI_write(crc);
                
    for(i=0; i<read; i++)
        buffer[i] = sdSPI_write(0xFF);
                
    sdSPI_disable();               
                
    // print out read bytes
}
