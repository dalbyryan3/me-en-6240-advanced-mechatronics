#include "positioncontrol.h"                   
#include "encoder.h"                   
#include "utilities.h"
#include "NU32.h"

#define POSTION_CONTROL_SAMPLE_PERIOD (1.0/200)
#define TRACK_ARRAY_MAX_LENGTH 5000

static double HOLDReferencePositionDeg = 0; // deg
static double proportionalGain = 14; // mA/deg
static double integralGain = 0; // mA/(deg*seconds)
static double derivativeGain = 0.05; // mA/(deg/seconds)
static double integralError = 0; // deg*seconds
static double lastErrorDeg = 0; // deg

static int TRACKCount = 0;
static int TRACKArrayLength = TRACK_ARRAY_MAX_LENGTH;
static double TRACKActualArray[TRACK_ARRAY_MAX_LENGTH]; // deg
static double TRACKReferenceArray[TRACK_ARRAY_MAX_LENGTH]; // deg

void __ISR(_TIMER_4_VECTOR, IPL5SOFT) Timer4ISR(void) { // INT step: the ISR
  switch (get_operating_mode())
  {
    case IDLE:
    {
      position_clean_state_IDLE();
      break;
    }
    case HOLD:
    {
      double measuredPositionDeg = encoder_counts_deg();
      // PID Control
      position_PID_control(HOLDReferencePositionDeg, measuredPositionDeg);
      break;
    }
    case TRACK:
    {
      double measuredPositionDeg = encoder_counts_deg();

      // Get measured position and update arrays for subsequent data processing/viz
      TRACKActualArray[TRACKCount] = measuredPositionDeg;

      // PID Control
      position_PID_control(TRACKReferenceArray[TRACKCount], measuredPositionDeg);

      // Update count and see if done
      TRACKCount++;
      if (TRACKCount == get_position_TRACKArrayLength()) // Are done with tracking trajectory 
      {
        set_operating_mode(HOLD);
        HOLDReferencePositionDeg = TRACKReferenceArray[(TRACKCount-1)];
        TRACKCount = 0;
        break;
      }
      break;
    }
  }

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

void position_PID_control(double referenceDeg, double measuredDeg)
{
  // PID Control
  double errDeg = referenceDeg - measuredDeg;
  integralError += errDeg * POSTION_CONTROL_SAMPLE_PERIOD; 
  double derivativeErr = (errDeg - lastErrorDeg)/POSTION_CONTROL_SAMPLE_PERIOD;
  double uEff = (errDeg * proportionalGain) + (integralError * integralGain) + (derivativeErr * derivativeGain); // Control effort, proportionalGain in units of mA/deg, integralGain in units of mA/(deg*seconds), and derivative gain in units of mA/(deg/seconds)  
  lastErrorDeg = errDeg;

  // Set reference current value for current controller to track (essentially decoupled from position control because frequency of current control is much higher)
  set_current_HOLDIReferencemA(uEff);
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

double* get_position_TRACKActualArray(void)
{
  return TRACKActualArray;
}
double* get_position_TRACKReferenceArray(void)
{
  return TRACKReferenceArray;
}
int get_position_TRACKArrayMaxLength(void)
{
  return TRACK_ARRAY_MAX_LENGTH;
}
int get_position_TRACKArrayLength(void)
{
  return TRACKArrayLength;
}
void set_position_TRACKArrayLength(int arrayLength)
{
  TRACKArrayLength = arrayLength;
}

void position_clean_state_IDLE(void)
{
  integralError = 0; // deg*seconds
  lastErrorDeg = 0; // deg

  TRACKCount = 0;
}
