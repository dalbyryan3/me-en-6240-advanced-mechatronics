#include "currentcontrol.h"                   
#include "utilities.h"
#include "NU32.h"
#include <math.h>

static int PWMDutyCycleOCxRSValue = 0;
static unsigned char PWMDutyCycleDirection = 0x0;

void __ISR(_TIMER_5_VECTOR, IPL5SOFT) Timer5ISR(void) { // INT step: the ISR
  switch (get_operating_mode())
  {
    case IDLE:
      // H-bridge brake mode
      OC1RS = 0;
      LATDbits.LATD1 = PWMDutyCycleDirection ^ 0x1; // Do opposite of present value for brake?
      break;
    case PWM:
      // Set duty cyle to present PWM value
      OC1RS = PWMDutyCycleOCxRSValue;
      LATDbits.LATD1 = PWMDutyCycleDirection;
      break;
    case ITEST:
      break;
    case HOLD:
      break;
    case TRACK:
      break;
  }
  IFS0bits.T5IF = 0; // clear interrupt flag
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
  IPC5bits.T5IS = 0; // subpriority
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
