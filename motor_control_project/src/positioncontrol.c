#include "positioncontrol.h"                   
#include "encoder.h"                   
#include "utilities.h"
#include "NU32.h"

#define POSTION_CONTROL_SAMPLE_PERIOD (1.0/200)

static double HOLDReferencePositionDeg = 0;
static double proportionalGain = 0; // mA/deg
static double integralGain = 0; // mA/(deg*seconds)
static double derivativeGain = 0; // mA/(deg/seconds)
static double integralError = 0; // deg*seconds
static double lastErrorDeg = 0; // deg

void __ISR(_TIMER_4_VECTOR, IPL5SOFT) Timer4ISR(void) { // INT step: the ISR
  switch (get_operating_mode())
  {
    case HOLD:
    {
      double measuredPositionDeg = encoder_counts_deg();
      double errDeg = HOLDReferencePositionDeg - measuredPositionDeg;
      integralError += errDeg * POSTION_CONTROL_SAMPLE_PERIOD; 
      double derivativeErr = (errDeg - lastErrorDeg)/POSTION_CONTROL_SAMPLE_PERIOD;
      double uEff = (errDeg * proportionalGain) + (integralError * integralGain) + (derivativeErr * derivativeGain); // Control effort, proportionalGain in units of mA/deg, integralGain in units of mA/(deg*seconds), and derivative gain in units of mA/(deg/seconds)  
      lastErrorDeg = errDeg;

      // Set reference current value for current controller to track (essentially decoupled from position control because frequency of current control is much higher)
      set_current_HOLDIReferencemA(uEff);

      break;
    }
    case TRACK:
    {
      break;
    }
  }
  // Confirm ISR  
  // if (proportionalGain > 5)
  // {
  //   LATFbits.LATF0 = 0;
  // }
  // else
  // {
  //   LATFbits.LATF0 = 1;
  // }
  IFS0bits.T4IF = 0; // clear interrupt flag
}

void positioncontrol_init(void)
{
  // 200 Hz ISR (using timer 4)
  T4CONbits.TCKPS = 0x6; // Timer4 prescaler N=64 (1:64)
  PR4 = 6249; // Period = (PR4+1) * N * 12.5ns = 5 milliseconds, 200Hz
  TMR4 = 0; // initial TMR4 count is 0
  T4CONbits.ON = 1; // turn on Timer4
  IPC4bits.T4IP = 5; // INT step: priority
  IPC4bits.T4IS = 1; // subpriority
  IFS0bits.T4IF = 0; // INT step: clear interrupt flag
  IEC0bits.T4IE = 1; // INT step: enable interrupt
}


void set_position_proportional_gain(double positionProportionalGain)
{
  proportionalGain = positionProportionalGain;
}
double get_position_proportional_gain(void)
{
  return proportionalGain;
}

void set_position_integral_gain(double positionIntegralGain)
{
  integralGain = positionIntegralGain;
}
double get_position_integral_gain(void)
{
  return integralGain;
}

void set_position_derivative_gain(double positionDerivativeGain)
{
  derivativeGain = positionDerivativeGain;
}
double get_position_derivative_gain(void)
{
  return derivativeGain;
}

void set_position_HOLDReferencePositionDeg(double positionHOLDReferencePositionDeg)
{
  HOLDReferencePositionDeg = positionHOLDReferencePositionDeg;
}
