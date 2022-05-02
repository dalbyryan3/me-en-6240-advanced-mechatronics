#ifndef CURRENTCONTROL_H 
#define CURRENTCONTROL_H

// Assumes interrupts are disabled before this function then renabled at some time after this function
void currentcontrol_init(void);

// Perform single PI control iteration 
void current_PI_control(double referencemA, double measuredmA);

// Set the pwm duty cycle in percent and the direction based on the sign of the duty cycle value passed in. For when in 
void set_motor_pwm_and_direction_values(double signed_duty_cycle);
// Command the current pwm and direction values to the motor
void command_motor_pwm_and_direction(void);

void set_current_proportional_gain(double currentProportionalGain);
double get_current_proportional_gain(void);

void set_current_integral_gain(double currentIntegralGain);
double get_current_integral_gain(void);

double* get_current_ITESTIActualArray(void);
double* get_current_ITESTIReferenceArray(void);
int get_current_ITESTIArrayLength(void);

void set_current_HOLDIReferencemA(double currentHOLDIReferencemA);

void current_clean_state_IDLE(void);

#endif // CURRENTCONTROL_H
