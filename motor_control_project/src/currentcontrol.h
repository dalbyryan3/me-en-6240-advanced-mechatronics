#ifndef CURRENTCONTROL_H 
#define CURRENTCONTROL_H

// Assumes interrupts are disabled before this function then renabled at some time after this function
void currentcontrol_init(void);

// Set the pwm duty cycle in percent and the direction based on the sign of the duty cycle value passed in. For when in 
void set_motor_pwm_and_direction_values(double signed_duty_cycle);

#endif // CURRENTCONTROL_H
