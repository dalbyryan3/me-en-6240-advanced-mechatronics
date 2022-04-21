#include "isense.h"                   
#include <xc.h>

#define VOLTS_PER_COUNT (3.3/1024)
// #define SAMPLE_TIME_CORE_TIMER_TICKS 100 // 100 core timer ticks corresponds to 2500 ns
#define ADC_PIN 5
#define NUM_ADC_SAMPLES_FOR_AVERAGE 5
#define R_SENSE_OHMS 0.015
#define V_SENSE_GAIN 33

unsigned int adc_counts(void)
{
  AD1CON1bits.SAMP = 1;                  // start sampling, when finished conversion start automatically
  while (!AD1CON1bits.DONE) { 
    ;                                   // wait for conversion file to finsih
  }
  return ADC1BUF0;                      // read the buffer with the result
}

double adc_voltage(void)
{
  return (adc_counts() * VOLTS_PER_COUNT);
}

double adc_current_sense_value_mA(void)
{
  // If not using emperical relation, and measurements were exact, the realtion would be:
  // double vOut = VOLTS_PER_COUNT * adc_counts();
  // double vSense = (vOut-1.65) / V_SENSE_GAIN; 
  // double currentSenseA = vSense / (R_SENSE_OHMS);
  // double currentSensemA = currentSenseA*1000;

  double currentSensemA = 3.2894*adc_counts() - 1681.62;

  return currentSensemA;
}

void adc_init(void)
{
  AD1PCFGbits.PCFG5 = 0;                 // AN5 is an adc pin
  AD1CON3bits.ADCS = 2;                   // ADC clock period is Tad = 2*(ADCS+1)*Tpb =
                                          //                           2*3*12.5ns = 75ns
  AD1CON1bits.ADON = 1;                   // turn on A/D converter

  AD1CON1bits.SSRC = 0x7; // 0b111 (set automatic conversion)

  AD1CHSbits.CH0SA = ADC_PIN;                // connect chosen pin to MUXA for sampling
}
