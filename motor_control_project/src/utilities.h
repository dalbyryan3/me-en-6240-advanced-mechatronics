#ifndef UTILITIES_H 
#define UTILITIES_H

typedef enum { IDLE, PWM, ITEST, HOLD, TRACK } OperatingMode_t; 

// Set operating mode
void set_operating_mode(OperatingMode_t mode);

// Return operating mode
OperatingMode_t get_operating_mode(void);

// Return string representation of operating mode
const char* get_operating_mode_str(void);

// Global to hold operating mode
extern OperatingMode_t operatingMode;

#endif // UTILITIES_H
