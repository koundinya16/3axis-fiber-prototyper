#ifndef parameters_h
#define parameters_h


extern volatile int encoderButton_count;
extern volatile uint8_t encoderButton_buttonPress; // for registering encoder button push event 1-if button is pushed 
extern volatile uint8_t encoderButton_dir; // 1-clockwise , 0-anti-clockwise

extern FATFS sdCard_Pointer;
extern uint8_t sdCard_detect_flag;
extern uint8_t sdCard_mounted_flag;


extern volatile uint32_t X_steps;
extern volatile uint32_t Y_steps;
extern volatile uint32_t Z_steps;
extern volatile uint32_t F_steps;
extern volatile uint32_t P_steps;

extern uint8_t feedRate;
extern uint8_t compressionFactor;
extern uint8_t temperature;
extern uint8_t jobPercentage;
extern uint8_t timeElapsed_hours;
extern uint8_t timeElapsed_minutes;
extern uint8_t jobPercentage;


#endif
