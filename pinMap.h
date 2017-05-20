#ifndef pinMap_h
#define pinMap_h


#include "alm.h"

#define SERIAL_RX USART0_RX_vect
#define SERIAL_UDRE USART0_UDRE_vect

/*-------- X,Y,Z Motion Stepper Motors, Spool winding Stepper motors(P-paper,F-filament),Servo motor or cutter(C) -----------*/

 // Define step pulse output pins. NOTE: All step bit pins must be on the same port.
#define MOTOR_AXIS_X_DDR       DDRC
#define MOTOR_AXIS_X_PORT     PORTC
#define MOTOR_AXIS_X_PIN      PINC


#define MOTOR_AXIS_X_PULSE_BIT  5      // Pin 32 on arduino mega
#define MOTOR_AXIS_X_DIR_BIT    4      // Pin 33 on arduino mega
#define MOTOR_AXIS_X_EN_BIT		3      // Pin 34 on arduino mega


#define MOTOR_AXIS_Y_DDR       DDRA
#define MOTOR_AXIS_Y_PORT     PORTA
#define MOTOR_AXIS_Y_PIN      PINA


#define MOTOR_AXIS_Y_PULSE_BIT	2      // Pin 24 on arduino mega
#define MOTOR_AXIS_Y_DIR_BIT	1      // Pin 23 on arduino mega
#define MOTOR_AXIS_Y_EN_BIT		0	   // Pin 22 on arduino mega

#define MOTOR_AXIS_Z_DDR       DDRA
#define MOTOR_AXIS_Z_PORT     PORTA
#define MOTOR_AXIS_Z_PIN      PINA


#define MOTOR_AXIS_Z_PULSE_BIT  5 	  // Pin 27 on arduino mega
#define MOTOR_AXIS_Z_DIR_BIT	4     // Pin 26 on arduino mega
#define MOTOR_AXIS_Z_EN_BIT		3     // Pin 25 on arduino mega


// STEP -on the circuit board
#define MOTOR_AXIS_P_DDR      DDRH
#define MOTOR_AXIS_P_PORT      DDRH
#define MOTOR_AXIS_P_PIN      DDRH

#define MOTOR_AXIS_P_PULSE_BIT  3 	    // Pin 6(PWM) on arduino mega 
#define MOTOR_AXIS_P_DIR_BIT	1       // Pin 16(TX2) on arduino mega
#define MOTOR_AXIS_P_EN_BIT		4       // Pin 7 (PWM) on arduino mega


// STEP1 - on the circuit board 
#define MOTOR_AXIS_F_DDR      DDRA
#define MOTOR_AXIS_F_PORT     PORTA
#define MOTOR_AXIS_F_PIN      PINA

#define MOTOR_AXIS_F_PULSE_BIT  7 	      // Pin 29 on arduino mega
#define MOTOR_AXIS_F_DIR_BIT	6         // Pin 28 on arduino mega

/* the enable line is connected on a different port */
#define MOTOR_AXIS_F_EN_DDR      DDRC
#define MOTOR_AXIS_F_EN_PORT     PORTC
#define MOTOR_AXIS_F_EN_BIT		6        // Pin 31 on arduino mega



// SERVO-on the circuit board   
#define MOTOR_AXIS_C_DDR DDRH
#define MOTOR_AXIS_C_PORT DDRH
#define MOTOR_AXIS_C_BIT 5         // Pin 8(PWM)-Timer 4 on arduino mega

/*--------------------------------Endstop Switches-----------------------*/

  // Define homing/hard limit switch input pins and limit interrupt vectors. 
  // NOTE: All limit bit pins must be on the same port
  

  #define ENDSTOP_DDR       DDRL
  #define ENDSTOP_PORT      PORTL
  #define ENDSTOP_PIN       PINL
  #define ENDSTOP_X_BIT     3         // Pin 46(PWM) on arduino mega
  #define ENDSTOP_Y_BIT     4         // Pin 45(PWM) on arduino mega
  #define ENDSTOP_Z_BIT     5         // Pin 44(PWM) on arduino mega
  
  #define ENDSTOP_MASK ((1<<ENDSTOP_X_BIT)|(1<<ENDSTOP_Y_BIT)|(1<<ENDSTOP_Z_BIT)) 
 
// Endstops should have been ideally connected to interrupt pins like these, but they were not on the circuit, so they have to be polled instead
 /*
  #define ENDSTOP_DDR       DDRJ
  #define ENDSTOP_PORT      PORTJ
  #define ENDSTOP_PIN       PINJ
  #define ENDSTOP_X_BIT     3         
  #define ENDSTOP_Y_BIT     4 
  #define ENDSTOP_Z_BIT     5 
  
  #define ENDSTOP_MASK ((1<<ENDSTOP_X_BIT)|(1<<ENDSTOP_Y_BIT)|(1<<ENDSTOP_Z_BIT)) 

  
  
  #define ENDSTOP_INT       PCIE1  // Pin change interrupt enable pin
  #define ENDSTOP_INT_vect  PCINT1_vect 
  #define ENDSTOP_PCMSK     PCMSK1 // Pin change interrupt register
  #define ENDSTOP_MASK ((1<<ENDSTOP_X_BIT)|(1<<ENDSTOP_Y_BIT)|(1<<ENDSTOP_Z_BIT)) // All endstop bits
  */

/*--------------LCD-------------------*/

#define LCD_PORT	PORTB
#define LCD_DDR		DDRB
#define LCD_PIN		PINB

#define LCD_LCD4_BIT  	6
#define LCD_LCD5_BIT  	7
#define LCD_RS_BIT 	5
#define LCD_EN_BIT	4

#define LCD67_PORT	PORTJ
#define LCD67_DDR	DDRJ
#define LCD67_PIN	PINJ

#define LCD_LCD6_BIT	1
#define LCD_LCD7_BIT	0

/*--------------SD CARD----------------*/

#define SD_PORT		PORTB
#define SD_DDR		DDRB
#define SD_PIN		PINB

#define SD_CS_BIT		0
#define SD_CLK_BIT    	1
#define SD_MOSI_BIT 	2
#define SD_MISO_BIT 	3

#define SD_DETECT_PORT	PORTE
#define SD_DETECT_DDR	DDRE
#define SD_DETECT_PIN	PINE
#define SD_DETECT_BIT	4


/*-----------ENCODER and Button-----------*/


// ALM V1 Board
#define PANEL_BUTTON_PORT 	PORTE 
#define PANEL_BUTTON_DDR	DDRE	
#define PANEL_BUTTON_PIN	PINE
#define PANEL_BUTTON_BIT	5

#define ENCODER_DDR		DDRD
#define ENCODER_PORT	PORTD
#define ENCODER_PIN		PIND

#define ENCODER_DIRA_BIT 	0
#define ENCODER_DIRB_BIT 	1
#define ENCODER_BUTTON_BIT 	2

#endif
