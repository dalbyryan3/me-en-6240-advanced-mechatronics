#ifndef ISENSE_H 
#define ISENSE_H

// Sample and convert the adc pin value and give the value in adc counts. 
unsigned int adc_counts(void);

// Sample and convert the adc pin value and give the value in voltage. 
double adc_voltage(void);

// Get adc counts of current sensor analog input and convert to the corresponding current value in mA. Uses empirically found transfer function to better account for error. 
double adc_current_sense_value_mA(void);

// Initialize A5 which is PIC32 pin 11 (NU32 pin B5) for adc sampling with manual sampling but automatic conversion.
void adc_init(void);

#endif // ISENSE_H
