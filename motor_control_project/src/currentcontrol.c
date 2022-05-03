#include "currentcontrol.h"                   
#include "isense.h"                   
#include "utilities.h"
#include "NU32.h"
#include <math.h>

#define ITEST_I_REFERENCE_MAG_mA 200 
#define ITEST_ARRAY_LENGTH 100
#define CURRENT_CONTROL_SAMPLE_PERIOD (1.0/5000)
#define INTEGRAL_EFFORT_WINDUP_LIMIT 100

static int PWMDutyCycleOCxRSValue = 0;
static unsigned char PWMDutyCycleDirection = 0x0;

// static double proportionalGain = 0; // %/mA
static double proportionalGain = 0.5; // %/mA
// static double integralGain = 0; // %/(mA*seconds)
static double integralGain = 5; // %/(mA*seconds)
static double integralError = 0; // mA*seconds

static int ITESTCount = 0;
static double ITESTIReferencemA = ITEST_I_REFERENCE_MAG_mA; // mA
static double ITESTIActualArray[ITEST_ARRAY_LENGTH]; // mA
static double ITESTIReferenceArray[ITEST_ARRAY_LENGTH]; // mA

static double HOLDIReferencemA = 0;

void __ISR(_TIMER_5_VECTOR, IPL5SOFT) Timer5ISR(void) { // INT step: the ISR
  switch (get_operating_mode())
  {
    case IDLE:
    {
      // Make sure if we exited from another mode that we have clean state
      current_clean_state_IDLE();
      // H-bridge brake mode
      OC1RS = 0;
      LATDbits.LATD1 = PWMDutyCycleDirection ^ 0x1; // Do opposite of present value for brake?
      break;
    }
    case PWM:
    {
      // Set duty cyle to present PWM value
      command_motor_pwm_and_direction();
      break;
    }
    case ITEST:
    {
      if (ITESTCount > 100) // We have gotten over 100 so we want to reset
      {
        ITESTCount = 0;
      }
      // PI current control test to track two full cycles of a +/- 200mA 100Hz square wave reference
      if (ITESTCount == 0) // Test begins
      {
        ITESTIReferencemA = ITEST_I_REFERENCE_MAG_mA;
      }
      else if (ITESTCount == 24 || ITESTCount==49 || ITESTCount==74) // Reference changes sign 
      {
        ITESTIReferencemA *= -1;
      }

      double measuredCurrentmA = adc_current_sense_value_mA();

      // Get measured current and update arrays for subsequent data processing/viz
      ITESTIReferenceArray[ITESTCount] = ITESTIReferencemA;
      ITESTIActualArray[ITESTCount] = measuredCurrentmA;

      // PI control
      current_PI_control(ITESTIReferencemA, measuredCurrentmA);

      // Update count and see if done
      ITESTCount++;
      if (ITESTCount == 100) // Are done with the test
      {
        ITESTCount = 0;
        set_operating_mode(IDLE);
        break;
      }
      break;
    }
    case HOLD:
    case TRACK:
    {
      // PI control (same as HOLD case from current control perspective)
      double measuredCurrentmA = adc_current_sense_value_mA();
      current_PI_control(HOLDIReferencemA, measuredCurrentmA);
      break;
    }
  }

  IFS0bits.T5IF = 0; // clear interrupt flag
}

void current_PI_control(double referencemA, double measuredmA)
{
  // PI Control
  double errmA = referencemA - measuredmA; // units of mA
  integralError += errmA * CURRENT_CONTROL_SAMPLE_PERIOD; // units of mA*seconds
  double integralEff = integralError * integralGain;
  if (integralEff > INTEGRAL_EFFORT_WINDUP_LIMIT)
  {
    integralEff = INTEGRAL_EFFORT_WINDUP_LIMIT;
  }
  double uEff = (errmA * proportionalGain) + integralEff; // Control effort, proportionalGain in units of %/mA and integralGain in units of %/(mA*seconds), note % implies % duty cycle

  // Apply control effort
  set_motor_pwm_and_direction_values(uEff);
  command_motor_pwm_and_direction();
}

void currentcontrol_init(void)
{
  // Digital output 
  TRISDbits.TRISD1 = 0; // make RD1 (PIC32 pin 49, D1 on NU32) a digital output

  // 5 kHz ISR (using timer 5)
  T5CONbits.TCKPS = 0x4; // Timer5 prescaler N=16 (1:16)
  PR5 = 999; // Period = (PR5+1) * N * 12.5ns = 200 microseconds, 5kHz
  TMR5 = 0; // initial TMR5 count is 0
  T5CONbits.ON = 1; // turn on Timer5
  IPC5bits.T5IP = 5; // INT step: priority
  IPC5bits.T5IS = 1; // subpriority
  IFS0bits.T5IF = 0; // INT step: clear interrupt flag
  IEC0bits.T5IE = 1; // INT step: enable interrupt

  // 20 kHz PWM signal initialization (using timer 2)
  T2CONbits.TCKPS = 0x2; // Timer2 prescaler N=4 (1:4)
  PR2 = 999; // Period = (PR2+1) * N * 12.5ns = 50 microseconds, 20kHz
  TMR2 = 0; // initial TMR2 count is 0
  OC1CONbits.OCM = 0b110; // PWM mode without fault pin; other OC1CON bits are defaults
  OC1CONbits.OCTSEL = 0; // use Timer2
  OC1CONbits.OC32 = 0; // use 16-bit Timer2
  OC1RS = 0; // initial duty cycle = OC1RS/(PR2+1) = 0%
  OC1R = 0; // initialize before turning OC1 on; afterward it is read-only (changed by OC1RS)
  T2CONbits.ON = 1; // turn on Timer2
  OC1CONbits.ON = 1; // turn on OC1
}


void set_motor_pwm_and_direction_values(double signed_duty_cycle)
{

  if (signed_duty_cycle < 0)
  {
    // Enforce constraints
    if (signed_duty_cycle < -100)
    {
      signed_duty_cycle = -100;
    }

    // Set PWM parameters and direction
    PWMDutyCycleOCxRSValue = (int) ((-signed_duty_cycle/100) * (PR2+1));
    PWMDutyCycleDirection = 0x0;
  }
  else
  {
    if (signed_duty_cycle > 100)
    {
      signed_duty_cycle = 100;
    }

    // Set PWM parameters and direction
    PWMDutyCycleOCxRSValue = (int) ((signed_duty_cycle/100) * (PR2+1));
    PWMDutyCycleDirection = 0x1;
  }
}
void command_motor_pwm_and_direction(void)
{
  OC1RS = PWMDutyCycleOCxRSValue;
  LATDbits.LATD1 = PWMDutyCycleDirection;
}

void set_current_proportional_gain(double currentProportionalGain)
{
  proportionalGain = currentProportionalGain;
}
double get_current_proportional_gain(void)
{
  return proportionalGain;
}

void set_current_integral_gain(double currentIntegralGain)
{
  integralGain = currentIntegralGain;
}
double get_current_integral_gain(void)
{
  return integralGain;
}

double* get_current_ITESTIActualArray(void)
{
  return ITESTIActualArray;
}
double* get_current_ITESTIReferenceArray(void)
{
  return ITESTIReferenceArray;
}
int get_current_ITESTIArrayLength(void)
{
  return ITEST_ARRAY_LENGTH;
}

void set_current_HOLDIReferencemA(double currentHOLDIReferencemA)
{
  HOLDIReferencemA = currentHOLDIReferencemA;
}

void current_clean_state_IDLE(void)
{
  ITESTCount = 0;
  ITESTIReferencemA = ITEST_I_REFERENCE_MAG_mA; // mA
  integralError = 0;
}
