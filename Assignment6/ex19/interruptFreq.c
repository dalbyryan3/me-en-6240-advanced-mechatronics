#include<stdio.h>
#include "NU32.h"

// Prototypes
void __ISR(_CORE_TIMER_VECTOR, IPL3SOFT) CoreTimerISR(void);
void promptInputInterruptPeriod(int minPeriod, int maxPeriod);
void readAndSetInterruptPeriodIfValid(int *interruptPeriod, int minPeriod, int maxPeriod);
char inputValid(int input, int minPeriod, int maxPeriod);

// Constants 
#define MIN_INTERRUPT_PERIOD 4000000 // 0.1 seconds
#define MAX_INTERRUPT_PERIOD 400000000 // 10 seconds
int InterruptPeriod = 40000000; // Ticks corresponding to 1 second is default value

int main()
{
  NU32_Startup(); // cache on, min flash wait, interrupts on, LED/button init, UART init

  __builtin_disable_interrupts(); // disable interrupts at CPU
  _CP0_SET_COMPARE(InterruptPeriod); // set the core timer compare value
  IPC0bits.CTIP = 3; // set priority
  IPC0bits.CTIS = 0; // set subpriority
  IFS0bits.CTIF = 0; // clear core timer interrupt flag
  IEC0bits.CTIE = 1; // enable core timer interrupt
  __builtin_enable_interrupts(); // reenable interrupts at CPU

  _CP0_SET_COUNT(0); // set core timer counter to 0

  while(1){
    promptInputInterruptPeriod(MIN_INTERRUPT_PERIOD, MAX_INTERRUPT_PERIOD);
    readAndSetInterruptPeriodIfValid(&InterruptPeriod, MIN_INTERRUPT_PERIOD, MAX_INTERRUPT_PERIOD);
  }

  return 0;
}

void __ISR(_CORE_TIMER_VECTOR, IPL3SOFT) CoreTimerISR(void)
{
  IFS0bits.CTIF = 0; // clear CT int flag
  LATFINV = 0x2; // invert pin RF1
  _CP0_SET_COUNT(0); // set core timer counter to 0
  _CP0_SET_COMPARE(InterruptPeriod); // set CP0_COMPARE again after interrupt
}

void promptInputInterruptPeriod(int minPeriod, int maxPeriod)
{
  char outstring[100];
  sprintf(outstring, "Enter an interrupt period between %d ticks and %d ticks:\r\n", minPeriod, maxPeriod);
  NU32_WriteUART3(outstring);
}

void readAndSetInterruptPeriodIfValid(int *interruptPeriod, int minPeriod, int maxPeriod)
{
  // Will set interruptPeriod if input is valid
  const int MAX_READ_LENGTH = 100;
  char outstring[100];
  NU32_ReadUART3(outstring, MAX_READ_LENGTH);
  NU32_WriteUART3("\r\n\r\n");
  int userInput = -1;
  sscanf(outstring, "%d", &userInput);
  if(inputValid(userInput, minPeriod, maxPeriod))
  {
    *interruptPeriod = userInput;
    _CP0_SET_COUNT(0); // set core timer counter to 0
    _CP0_SET_COMPARE(*interruptPeriod); // set CP0_COMPARE
    sprintf(outstring, "Input %d ticks was set as the new core timer interrupt frequency \r\n", userInput);
    NU32_WriteUART3(outstring);
  }
  else
  {
    sprintf(outstring, "Input %d ticks was not a valid input between %d and %d\r\n", userInput, minPeriod, maxPeriod);
    NU32_WriteUART3(outstring);
  }
}

char inputValid(int input, int minPeriod, int maxPeriod)
{
  if(input >= minPeriod && input <= maxPeriod)
  {
    return 1;
  }
  return 0;
}
