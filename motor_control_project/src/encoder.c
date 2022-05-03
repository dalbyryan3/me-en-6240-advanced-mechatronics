#include "encoder.h"                   
#include "NU32.h"

// The motor being used has 48 counts per revolution
#define ENCODER_COUNTS_PER_REV 48

static int encoder_command(int read) { // send a command to the encoder chip
                                       // 0 = reset count to 32,768, 1 = return the count

  SPI4BUF = read;                      // send the command
  while (!SPI4STATbits.SPIRBF) { ; }   // wait for the response
  SPI4BUF;                             // garbage was transferred, ignore it

  SPI4BUF = 5;                         // write garbage, but the read will have the data
  while (!SPI4STATbits.SPIRBF) { ; }
  int resp = SPI4BUF; 

  // Do this again, for some reason (likely something happening on the pre-programmed encoder chip) this is necessary
  SPI4BUF = 5;                         // write garbage, but the read will have the data
  while (!SPI4STATbits.SPIRBF) { ; }
  resp = SPI4BUF; 
  
  // Clear buffer
  while (SPI4STATbits.SPIRBF) 
  { 
    SPI4BUF;
  }

  return resp;
}

int encoder_counts(void) {
  int resp = encoder_command(1);
  return resp;
}

void encoder_reset_counts(void) {
  encoder_command(0);
}

double encoder_counts_deg(void){
  double shifted_counts = encoder_counts() - 32768;
  return 360.0 * (shifted_counts)/((double)ENCODER_COUNTS_PER_REV);
}

void encoder_init(void) {
  // SPI initialization for reading from the decoder chip
  SPI4CON = 0;              // stop and reset SPI4
  SPI4BUF;                  // read to clear the rx receive buffer
  SPI4BRG = 0x4;            // bit rate to 8 MHz, SPI4BRG = 80000000/(2*desired)-1
  SPI4STATbits.SPIROV = 0;  // clear the overflow
  SPI4CONbits.MSTEN = 1;    // master mode
  SPI4CONbits.MSSEN = 1;    // slave select enable
  SPI4CONbits.MODE16 = 1;   // 16 bit mode
  SPI4CONbits.MODE32 = 0; 
  SPI4CONbits.SMP = 1;      // sample at the end of the clock
  SPI4CONbits.ON = 1;       // turn SPI on
}
