#ifndef POSITIONCONTROL_H 
#define POSITIONCONTROL_H

// Assumes interrupts are disabled before this function then renabled at some time after this function
void positioncontrol_init(void);

// Perform single PID control iteration 
void position_PID_control(double referenceDeg, double measuredDeg);

void set_position_proportional_gain(double positionProportionalGain);
double get_position_proportional_gain(void);

void set_position_integral_gain(double positionIntegralGain);
double get_position_integral_gain(void);

void set_position_derivative_gain(double positionDerivativeGain);
double get_position_derivative_gain(void);

void set_position_HOLDReferencePositionDeg(double positionHOLDReferencePositionDeg);

double* get_position_TRACKActualArray(void);
double* get_position_TRACKReferenceArray(void);
int get_position_TRACKArrayMaxLength(void);
int get_position_TRACKArrayLength(void);
void set_position_TRACKArrayLength(int arrayLength);

void position_clean_state_IDLE(void);

#endif // POSITIONCONTROL_H
