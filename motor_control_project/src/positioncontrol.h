#ifndef POSITIONCONTROL_H 
#define POSITIONCONTROL_H

// Assumes interrupts are disabled before this function then renabled at some time after this function
void positioncontrol_init(void);

void set_position_proportional_gain(double positionProportionalGain);
double get_position_proportional_gain(void);

void set_position_integral_gain(double positionIntegralGain);
double get_position_integral_gain(void);

void set_position_derivative_gain(double positionDerivativeGain);
double get_position_derivative_gain(void);

void set_position_HOLDReferencePositionDeg(double positionHOLDReferencePositionDeg);

#endif // POSITIONCONTROL_H
