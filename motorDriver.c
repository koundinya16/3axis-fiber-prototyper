#include "alm.h"

uint8_t feedRate=70;
uint8_t compressionFactor=12;
uint8_t temperature=45;
uint8_t jobPercentage=70;
uint8_t timeElapsed_hours=1;
uint8_t timeElapsed_minutes=20;

volatile uint8_t busy=0;
volatile uint8_t auto_homing=0;
volatile uint8_t drawing_line=0;
volatile uint8_t major_axis=0;

volatile uint8_t pulse_x=0;   // 1-> to step; 0 -> to not step
volatile uint8_t pulse_y=0;
volatile uint8_t pulse_z=0;
volatile uint8_t pulse_f=0;
volatile uint8_t pulse_p=0;

volatile uint32_t X_steps=0;  
volatile uint32_t Y_steps=0;
volatile uint32_t Z_steps=0;
volatile uint32_t F_steps=0;
volatile uint32_t P_steps=0;

uint32_t X_steps_target=0;
uint32_t Y_steps_target=0;

float over=0;
float distance_to_target_X=0;
float distance_to_target_Y=0;





void init_stepperMotors()
{
  // Disable any running interrupts
  cli();
  
 // Initialize axis stepper motor pins
 MOTOR_AXIS_X_DDR |= (1<<MOTOR_AXIS_X_PULSE_BIT) | (1<<MOTOR_AXIS_X_DIR_BIT) | (1<<MOTOR_AXIS_X_EN_BIT);
 MOTOR_AXIS_Y_DDR |= (1<<MOTOR_AXIS_Y_PULSE_BIT) | (1<<MOTOR_AXIS_Y_DIR_BIT) | (1<<MOTOR_AXIS_Y_EN_BIT);
 MOTOR_AXIS_Z_DDR |= (1<<MOTOR_AXIS_Z_PULSE_BIT) | (1<<MOTOR_AXIS_Z_DIR_BIT) | (1<<MOTOR_AXIS_Z_EN_BIT);

 // Initialize spool stepper motor pins
 MOTOR_AXIS_F_DDR |= (1<<MOTOR_AXIS_F_PULSE_BIT) | (1<<MOTOR_AXIS_F_DIR_BIT) | (1<<MOTOR_AXIS_F_EN_BIT);
 MOTOR_AXIS_P_DDR |= (1<<MOTOR_AXIS_P_PULSE_BIT) | (1<<MOTOR_AXIS_P_DIR_BIT) | (1<<MOTOR_AXIS_P_EN_BIT);

 // Enable the Steppers
 MOTOR_AXIS_X_PORT &= ~(1<<MOTOR_AXIS_X_EN_BIT);
 MOTOR_AXIS_Y_PORT &= ~(1<<MOTOR_AXIS_Y_EN_BIT);
 MOTOR_AXIS_Z_PORT &= ~(1<<MOTOR_AXIS_Z_EN_BIT);
 MOTOR_AXIS_F_PORT &= ~(1<<MOTOR_AXIS_F_EN_BIT);
 MOTOR_AXIS_P_PORT &= ~(1<<MOTOR_AXIS_P_EN_BIT);

 
 // Set Direction
 MOTOR_AXIS_X_PORT &=~(1<<MOTOR_AXIS_X_DIR_BIT); //Towards X-end stop 
 MOTOR_AXIS_Y_PORT &=~(1<<MOTOR_AXIS_Y_DIR_BIT); //Towards Y-end stop


 // Initialize the end_stops
 ENDSTOP_DDR &= ~(ENDSTOP_MASK);

/* Configure Timers : Timer 2 and Timer 0 are used for generating interrupts to drive all the motors */


  // Configure Timer 1
  TCCR1B &= ~(1<<WGM13);// Set CTC(Clear Timer on Compare Mode) for Interrupt generation 
  TCCR1B |=  (1<<WGM12);
  TCCR1A &= ~((1<<WGM11) | (1<<WGM10));
  //Disconnect OC1 output
  TCCR1A &= ~((1<<COM1A1) | (1<<COM1A0) | (1<<COM1B1) | (1<<COM1B0)); 
  // Set a prescaling factor of 64 : timer frequency = default clk I/O frequency of arduino Mega:16Mhz
  TCCR1B |= (1<<CS10);
  TCCR1B |= (1<<CS11);
  TCCR1B &= ~(1<<CS10); 


  // Configure Timer 0
  TIMSK0 &= ~((1<<OCIE0B) | (1<<OCIE0A) | (1<<TOIE0)); // Disconnect OC0 outputs and OVF interrupt.
  TCCR0A = 0; // Normal operation
  TCCR0B = 0; // Disable Timer0 until needed
}

void disable_steppers()
{
 MOTOR_AXIS_X_PORT |= (1<<MOTOR_AXIS_X_EN_BIT);
 MOTOR_AXIS_Y_PORT |= (1<<MOTOR_AXIS_Y_EN_BIT);
 MOTOR_AXIS_Z_PORT |= (1<<MOTOR_AXIS_Z_EN_BIT);
 MOTOR_AXIS_F_PORT |= (1<<MOTOR_AXIS_F_EN_BIT);
 MOTOR_AXIS_P_PORT |= (1<<MOTOR_AXIS_P_EN_BIT);
}

void enable_steppers()
{
 MOTOR_AXIS_X_PORT &= ~(1<<MOTOR_AXIS_X_EN_BIT);
 MOTOR_AXIS_Y_PORT &= ~(1<<MOTOR_AXIS_Y_EN_BIT);
 MOTOR_AXIS_Z_PORT &= ~(1<<MOTOR_AXIS_Z_EN_BIT);
 MOTOR_AXIS_F_PORT &= ~(1<<MOTOR_AXIS_F_EN_BIT);
 MOTOR_AXIS_P_PORT &= ~(1<<MOTOR_AXIS_P_EN_BIT);
}

void init_servoMotor()
{
  // Servo Motor-uses Timer 4 for PWM, the servo motor signal pin is
  // connected on OC4C channel 
  TCCR4A |= 1<<WGM11 | 1<<COM4A1 | 1<<COM4B1;  // Non-inverted PWM 
  TCCR4B |= 1<<WGM13 | 1<<WGM12 | 1<<CS10| 1<<CS11; // Set prescaler of 64,MODE-14(Fast PWM)
  ICR4 = 4999; // Set Pulse frequency pf 50Hz/Time period 20ms
  // Enable output
  MOTOR_AXIS_C_DDR |= (1<<MOTOR_AXIS_C_BIT);

  // The pulse width is set in OCR4A reg. , after setting wait for some time(100ms)
  // for the servo to move

 // OCR4C = 180 for 0 degrees
 // OCR4C = 415 for 90 degrees
 // OCR4C = 650 for 180 degrees 
}



void start_run()
{
   // Enable Timer0 overflow interrupt
  TIMSK0 |= (1<<TOIE0); 

  // Enable Timer 1 interrupt
  TIMSK1 |= (1<<OCIE1A);
  TCNT1=0;
  OCR1A=TIMER_TICKS;
  
  sei();

}

void stop_run()
{
	 TIMSK0 &= ~(1<<TOIE0);  // Disable Timer 0 Interrupt
	 TIMSK1 &= ~(1<<OCIE1A); // Disable Timer 1 Interrupt
	 cli(); // Global Interrupt Disable
}


// The interrupt service routine for Timer 1 compare match - generates pulses to step the motors- does all the actuation(except servo Cutter C)
ISR(TIMER1_COMPA_vect)
{
  //if (busy)
   // return (0);

 
 // Pulse the motor stepper pins
if(pulse_x)
{

MOTOR_AXIS_X_PORT |= 1<<(MOTOR_AXIS_X_PULSE_BIT);
X_steps+=(MOTOR_AXIS_X_PORT & 1<<MOTOR_AXIS_X_DIR_BIT)? -1:1;

if(!auto_homing)
pulse_x=0;
}


if(pulse_y)
{
MOTOR_AXIS_Y_PORT |= 1<<(MOTOR_AXIS_Y_PULSE_BIT);
Y_steps+=(MOTOR_AXIS_Y_PORT & 1<<MOTOR_AXIS_Y_DIR_BIT)? -1:1;

if(!auto_homing)
pulse_y=0;
}


// Reload Timer 0
TCNT0=STEPPER_TIMER_COUNTER_PRELOAD_VALUE;

// Begin Timer 0 , with prescale factor 8 
TCCR0B = (1<<CS01); 
  
  busy=1;
  sei();


if(drawing_line)
{
 	if(major_axis==X)
 	{
 		if(X_steps<X_steps_target)
 		{
 			pulse_x=1;
 			over+=distance_to_target_Y;
 			if(over>=distance_to_target_X)
 			{
 			over-=distance_to_target_X;
 			pulse_y=1;
 			}
 		}
 	}
 	else
 	{
	 	if(Y_steps<Y_steps_target)
	 	{
 			pulse_y=1;
 			over+=distance_to_target_X;
 			if(over>=distance_to_target_Y)
 			{
 				over-=distance_to_target_Y;
 				pulse_x=1;
 			}
 		}

 	}
 	//if(X_steps>=X_steps_target && Y_steps>=Y_steps_target)
 	//{	
 		//pulse_x=0;
 		//pulse_y=0;
 		//drawing_line=0;
 	//}
}


busy=0;

}



// resets the pulse pins set by the Timer 1 ISR- to complete the pulse for driving steppers 
ISR(TIMER0_OVF_vect)
{
MOTOR_AXIS_X_PORT &= ~(1<<MOTOR_AXIS_X_PULSE_BIT);
MOTOR_AXIS_Y_PORT &= ~(1<<MOTOR_AXIS_Y_PULSE_BIT);
MOTOR_AXIS_Z_PORT &= ~(1<<MOTOR_AXIS_Z_PULSE_BIT);
MOTOR_AXIS_F_PORT &= ~(1<<MOTOR_AXIS_F_PULSE_BIT);
MOTOR_AXIS_P_PORT &= ~(1<<MOTOR_AXIS_P_PULSE_BIT);

// Disable Timer0
TCCR0B=0;
}


void cut()
{
  init_servoMotor();
  //while(1)
 // {
  //OCR4C = 97;
 // _delay_ms(1000);
 // OCR4C = 200;
   // _delay_ms(1000);
  //}
}


void autoHome()
{
  	MOTOR_AXIS_X_PORT &=~(1<<MOTOR_AXIS_X_DIR_BIT); //Towards X-end stop 
	MOTOR_AXIS_Y_PORT &=~(1<<MOTOR_AXIS_Y_DIR_BIT); //Towards Y-end stop
	start_run();
	
	auto_homing=1;
  	pulse_x=1;
	pulse_y=1;
	while(pulse_x || pulse_y)
	{
    	if(!(ENDSTOP_PIN & 1<<ENDSTOP_X_BIT))
       	pulse_x=0;
    	if(!(ENDSTOP_PIN & 1<<ENDSTOP_Y_BIT))
       	pulse_y=0;  
   	}	 
  	auto_homing=0;
  	X_steps=0;
  	Y_steps=0;
  	stop_run();
}

// (x,y) in mm with respect to home(endstops) as origin
void drawLine(float x,float y)
{
 X_steps_target=(float) x/STEP_DIST_RESOLUTION;
 Y_steps_target=(float) y/STEP_DIST_RESOLUTION;
// Set Direction
 
 if(X_steps_target>X_steps)
 	MOTOR_AXIS_X_PORT &=~(1<<MOTOR_AXIS_X_DIR_BIT);
 else
 	MOTOR_AXIS_X_PORT |= (1<<MOTOR_AXIS_X_DIR_BIT);

 if(Y_steps_target>Y_steps)
 	MOTOR_AXIS_Y_PORT &=~(1<<MOTOR_AXIS_Y_DIR_BIT);
 else
 	MOTOR_AXIS_Y_PORT |= (1<<MOTOR_AXIS_Y_DIR_BIT);

  distance_to_target_X=abs(X_steps_target-X_steps);
  distance_to_target_Y=abs(Y_steps_target-Y_steps);
  
  if(distance_to_target_X>distance_to_target_Y)
	major_axis=X;
  else
  	major_axis=Y;
  
  drawing_line=1;
  start_run(); 
  while(drawing_line)
  {

  }
over=0;
distance_to_target_X=0;
distance_to_target_Y=0;

}
