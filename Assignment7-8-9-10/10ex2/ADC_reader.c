#include <stdio.h>
#include "NU32.h"          // constants, functions for startup and UART

#define VOLTS_PER_COUNT (3.3/1024)
#define CORE_TICK_TIME 25    // nanoseconds between core ticks
#define SAMPLE_TIME 100       // 100 core timer ticks = 2500 ns (found this sufficient amount of time to get sample)
#define DELAY_TICKS 20000000 // delay 1/2 sec, 20 M core ticks, between messages

unsigned int adc_sample_convert(int pin) { // sample & convert the value on the given 
                                           // adc pin the pin should be configured as an 
                                           // analog input in AD1PCFG.
                                           // Assumes manual sampling but automatic conversion
    unsigned int elapsed = 0, finish_time = 0;
    AD1CHSbits.CH0SA = pin;                // connect chosen pin to MUXA for sampling
    AD1CON1bits.SAMP = 1;                  // start sampling
    elapsed = _CP0_GET_COUNT();
    finish_time = elapsed + SAMPLE_TIME;
    while (_CP0_GET_COUNT() < finish_time) { 
      ;                                   // sample for more than 250 ns
    }
    return ADC1BUF0;                      // read the buffer with the result
}

int main(void) {
  unsigned int sample5 = 0, elapsed = 0;
  char msg[100] = {};

  NU32_Startup();                 // cache on, interrupts on, LED/button init, UART init

  AD1PCFGbits.PCFG5 = 0;                 // AN5 is an adc pin
  AD1CON3bits.ADCS = 2;                   // ADC clock period is Tad = 2*(ADCS+1)*Tpb =
                                          //                           2*3*12.5ns = 75ns
  AD1CON1bits.ADON = 1;                   // turn on A/D converter

  AD1CON1bits.SSRC = 0x7; // 0b111 (set automatic conversion)

  while (1) {
    _CP0_SET_COUNT(0);                    // set the core timer count to zero
    sample5 = adc_sample_convert(5);    // sample and convert pin 5
    elapsed = _CP0_GET_COUNT();           // how long it took to do two samples
                                          // send the results over serial
    sprintf(msg, "Time elapsed: %5u ns"
                 "  AN15: %4u (%5.3f volts) \r\n",
                 elapsed * CORE_TICK_TIME, 
                 sample5, sample5 * VOLTS_PER_COUNT);
    NU32_WriteUART3(msg);
    _CP0_SET_COUNT(0);                    // delay to prevent a flood of messages
    while(_CP0_GET_COUNT() < DELAY_TICKS) { 
      ;
    }
  }
  return 0;
}
