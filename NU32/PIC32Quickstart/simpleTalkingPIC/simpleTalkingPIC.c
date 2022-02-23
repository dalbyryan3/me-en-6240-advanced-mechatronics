#include <xc.h>          // Load the proper header for the processor
#include "NU32.h"          // constants, funcs for startup and UART
#include<stdio.h>

#define MAX_MESSAGE_LENGTH 200

// void delay(int);

int main(void) {

  char message[MAX_MESSAGE_LENGTH];
  // int delayTime = 5000000;
  
  NU32_Startup(); // cache on, interrupts on, LED/button init, UART init

  // Input 0 for slow, 1 for medium, 2 for fast LED flashing

  while(1) {
    NU32_ReadUART3(message, MAX_MESSAGE_LENGTH);  // get message from computer
    NU32_WriteUART3(message);                     // send message back
    NU32_WriteUART3("\r\n");                      // carriage return and newline
    // Will wait to change LED until input is recieved
    LATFINV = 0x0003;    // toggle LED1 and LED2; same as LATFINV = 0x3;
  }
  return 0;
}

// void delay(int delayTime) {
//   int j;
//   for (j = 0; j < delayTime; j++) { // number is 1 million
//     while(!PORTDbits.RD7) {
//         ;   // Pin D7 is the USER switch, low (FALSE) if pressed.
//     }
//   }
// }
