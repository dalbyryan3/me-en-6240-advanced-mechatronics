#include<stdio.h>
#include "NU32.h" // constants, functions for startup and UART

#define CLOCK_FREQUENCY_HZ 80000000
#define LED1_FREQUENCY_HZ 1


int freqToPeriodCount(const float freqHz, const float clockSpeedHz, const int prescalerValue);

void __ISR(_TIMER_3_VECTOR, IPL5SOFT) Timer23ISR(void) // INT step 1: the ISR
{ 
  LATFINV = 0x1; // toggle RF0 (LED1)
  IFS0bits.T3IF = 0; // clear interrupt flag
}

void __ISR(_TIMER_5_VECTOR, IPL5SOFT) Timer45ISR(void) // INT step 1: the ISR
{ 
  LATFINV = 0x2; // toggle RF1 (LED2)
  IFS0bits.T5IF = 0; // clear interrupt flag
}

int main(void) 
{
  NU32_Startup(); // cache on, min flash wait, interrupts on, LED/button init, UART init

  // Will assume LED2 is less than LED1 thus LED1 gets higher priority
  float LED2FrequencyHz = 1.0; // holds interactively defined LED2 frequency, default is 1Hz
  int isLED2FreqGreaterThanLED1 = 0;
  int LED1SubPriority = 1;
  int LED2SubPriority = 0;
  char msg[100] = {};

  NU32_WriteUART3("Enter the desired frequency for LED2:\r\n");
  NU32_ReadUART3(msg, 100);
  sscanf(msg, "%f", &LED2FrequencyHz);
  isLED2FreqGreaterThanLED1 = (LED2FrequencyHz > LED1_FREQUENCY_HZ);
  if(isLED2FreqGreaterThanLED1)
  {
    LED1SubPriority = 0;
    LED2SubPriority = 1;
  }
  sprintf(msg, "An LED2 frequency of %f was read.\r\n", LED2FrequencyHz); 
  NU32_WriteUART3(msg);
  sprintf(msg, "Is this greater than the preset 1 Hz LED frequency? %d (1 is yes, 0 is no).\r\n", isLED2FreqGreaterThanLED1); 
  NU32_WriteUART3(msg);
  sprintf(msg, "LED1 subpriority is %d, LED2 subpriority is %d (priorities are the same thus this tie breaks order on queue).\r\n\r\n", LED1SubPriority, LED2SubPriority); 
  NU32_WriteUART3(msg);


  // Configure timer23 for LED1 interrupt
  T2CONbits.T32 = 1; // Use timer 23 to get frequency values under 5Hz
  PR2 = freqToPeriodCount(LED1_FREQUENCY_HZ, CLOCK_FREQUENCY_HZ, 256); // set period register for user defined value
  TMR2 = 0; // initialize count to 0
  T2CONbits.TCKPS = 0x7; // 0b111 (set prescaler to 256)
  // PCBLK input is only  default for timers 2-5
  T2CONbits.ON = 1; // turn on Timer23

  IPC3bits.T3IP = 5; // INT step 4: priority
  IPC3bits.T3IS = LED1SubPriority; // subpriority
  IFS0bits.T3IF = 0; // INT step 5: clear interrupt flag
  IEC0bits.T3IE = 1; // INT step 6: enable interrupt
  __builtin_enable_interrupts(); // INT step 7: enable interrupts at CPU


  // Configure timer45 for LED2 interrupt
  T4CONbits.T32 = 1; // Use timer 45 to get frequency values under 5Hz
  PR4 = freqToPeriodCount(LED2FrequencyHz, CLOCK_FREQUENCY_HZ, 256); // set period register for user defined value
  TMR4 = 0; // initialize count to 0
  T4CONbits.TCKPS = 0x7; // 0b111 (set prescaler to 256)
  // PCBLK input is only  default for timers 2-5
  T4CONbits.ON = 1; // turn on Timer45

  IPC5bits.T5IP = 5; // INT step 4: priority
  IPC5bits.T5IS = LED2SubPriority; // subpriority
  IFS0bits.T5IF = 0; // INT step 5: clear interrupt flag
  IEC0bits.T5IE = 1; // INT step 6: enable interrupt
  __builtin_enable_interrupts(); // INT step 7: enable interrupts at CPU


  while (1) 
  {
    ; // infinite loop
  }

  return 0;
}

int freqToPeriodCount(const float freqHz, const float clockSpeedHz, const int prescalerValue)
{
  return ((int)((1.0/freqHz) * (clockSpeedHz/prescalerValue)))-1;
}
