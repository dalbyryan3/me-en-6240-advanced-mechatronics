#include <xc.h>          // Load the proper header for the processor

#define MAXCYCLES 1000000
#define DELTACYCLES 100000

void delay(int cycles);

int main(void) {
  TRISF = 0xFFFC;        // Pins 0 and 1 of Port F are LED1 and LED2.  Clear
                         // bits 0 and 1 to zero, for output.  Others are inputs.
  LATFbits.LATF0 = 0;    // Turn LED1 on and LED2 off.  These pins sink current
  LATFbits.LATF1 = 1;    // on the NU32, so "high" (1) = "off" and "low" (0) = "on"

  int currentCycles = MAXCYCLES;

  while(1) {
    currentCycles -= DELTACYCLES;
    if (currentCycles < 0)
    {
      currentCycles = MAXCYCLES;
    }
    delay(currentCycles);
    LATFINV = 0x0003;    // toggle LED1 and LED2; same as LATFINV = 0x3;
  }
  return 0;
}

void delay(int cycles) {
  int j;
  for (j = 0; j < cycles; j++) { 
    while(!PORTDbits.RD7) {
        ;   // Pin D7 is the USER switch, low (FALSE) if pressed.
    }
  }
}
