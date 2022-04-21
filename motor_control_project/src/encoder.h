#ifndef ENCODER_H 
#define ENCODER_H

// Return encoder counts 
int encoder_counts(void);

// Return encoder counts converted to degrees 
double encoder_counts_deg(void);

// Reset encoder counts to default value of 32768 counts or 0 degrees
void encoder_reset_counts(void);

// Initialize encoder that is connected using PIC32 SPI4 pins.
void encoder_init(void);

#endif // ENCODER_H
