#ifndef motorDriver_h
#define motorDriver_h


#define STEPPER_PULSE_WIDTH 20   // in microseconds
#define STEPPER_TIMER_COUNTER_PRELOAD_VALUE (65536-STEPPER_PULSE_WIDTH*2) 
#define MICROSTEPPING_FACTOR 16.0
#define STEP_RESOLUTION 1.8/(MICROSTEPPING_FACTOR)    // degrees per step
#define DRIVE_RADIUS  11.4 // in mm
#define STEP_DIST_RESOLUTION  DRIVE_RADIUS*((STEP_RESOLUTION)*(3.14/180))   // (in mm/step)
#define SPEED 1.0 // (in cm/sec)
#define ISR_TIMER_DELAY 1000000*(STEP_DIST_RESOLUTION/SPEED)   // (in micro seconds)
#define TIMER_TICKS 0.25*ISR_TIMER_DELAY  // Using prescale factor of 64
#define X 1
#define Y 2

void drawLine(float x,float y);
void init_stepperMotors();
void disable_steppers();
void enable_steppers();
void init_servoMotor();
void start_run();
void stop_run();
void cut();
void autoHome();
void drawLine(float x,float y);

#endif
