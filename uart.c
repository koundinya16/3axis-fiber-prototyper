#include "alm.h"
#define FOSC 16000000// Clock Speed

/* Only  baudrates available - 9600,19200,38400,56700 */
void uart_init(unsigned int baudrate) 
{
	 UCSR0A= 0x00;                 // Clear the UASRT status register

	//Enable The receiver and transmitter
    UCSR0B = (1 << RXEN0) | (1 << TXEN0);

    // Set Properties: asynchronous, no parity, 1 stop bit, char size 8
    UCSR0C = (1 << UCSZ01) | (1 << UCSZ00);
    
    //Set Baud rate
    UBRR0H = (uint8_t) (FOSC/(16UL*baudrate)-1 >> 8);  
    UBRR0L = (uint8_t) (FOSC/(16UL*baudrate)-1 & 255);
}

char uart_readChar()
 { 
    while(!(UCSR0A & (1<<RXC0))) 
    {
    }
    return UDR0;
}

void uart_writeChar(char data)
 { 
    while(!(UCSR0A & (1<<UDRE0)))
    {
    }
    UDR0=data;
}


void uart_write(const char *data)
{
	while (*data)
	{ 
		uart_writeChar( *data++ );
	}
}


