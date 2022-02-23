/******************************************************************************
 * PROGRAM COMMENTS (PURPOSE, HISTORY)
 ******************************************************************************/
/*
 * helper.c (from invest.c)
 *
 * This is the helper library for the program takes an initial investment amount, an expected annual
 * return rate, and the number of years, and calculates the growth of
 * the investment.  The main point of this program, though, is to
 * demonstrate some C syntax.  
 *
 *
 * HISTORY:  
 * Dec 20, 2011   Created by Kevin Lynch
 * Jan 4, 2012    Modified by Kevin Lynch (small changes, altered comments)
 * February 14, 2022    Modified by Ryan Dalby (changed to work with a PIC32 microcontroller)
 */
#include "helper.h"     // Helper functions
#include "NU32.h"       // Include processor specific header files and UART read/writing functions
#include<stdio.h>       // Standard input/output library

/* calculateGrowth
 *
 * This optimistically-named function fills the array with the investment 
 * value over the years, given the parameters in *invp.  
 */
void calculateGrowth(Investment *invp) {

  int i;

  // for loop ==SecA.4.14==
  for (i=1; i <= invp->years; i=i+1) {   // relational operators ==SecA.4.10==
                                         // struct access ==SecA.4.4==
    invp->invarray[i] = invp->growth * invp->invarray[i-1]; 
  }
} // ***** END calculateGrowth *****


/* getUserInput
 * 
 * This reads the user's input into the struct pointed at by invp, 
 * and returns TRUE (1) if the input is valid, FALSE (0) if not.
 */
int getUserInput(Investment *invp) {

  int valid;  	   // int used as a boolean ==SecA.4.10==
  char outstring[100]; // defining a string

  // I/O functions in stdio.h ==SecA.4.15==
  sprintf(outstring, "Enter investment, growth rate, number of yrs (up to %d): \r\n", MAX_YEARS);
  NU32_WriteUART3(outstring);
  NU32_ReadUART3(outstring, MAX_READ_LENGTH);
  sscanf(outstring, "%lf %lf %d", &(invp->inv0), &(invp->growth), &(invp->years));

  // logical operators ==SecA.4.11==
  valid = (invp->inv0 > 0) && (invp->growth > 0) &&
    (invp->years > 0) && (invp->years <= MAX_YEARS);
  sprintf(outstring, "Valid input?  %d\r\n", valid);
  NU32_WriteUART3(outstring);

  // if-else ==SecA.4.13==
  if (!valid) { // ! is logical NOT ==SecA.4.11== 
    NU32_WriteUART3("Invalid input; exiting.\r\n");
  }
  return(valid);
} // ***** END getUserInput *****


/* sendOutput
 *
 * This function takes the array of investment values (a pointer to the first
 * element, which is a double) and the number of years (an int).  We could
 * have just passed a pointer to the entire investment record, but we decided 
 * to demonstrate some different syntax.
 */
void sendOutput(double *arr, int yrs) {

  int i;
  char outstring[100];  // defining a string ==SecA.4.9==

  NU32_WriteUART3("\r\nRESULTS:\r\n\r\n");
  for (i=0; i<=yrs; i++) {  // ++, +=, math in ==SecA.4.7==
    sprintf(outstring,"Year %3d:  %10.2f\r\n",i,arr[i]); 
    NU32_WriteUART3(outstring);
  }
  NU32_WriteUART3("\r\n");
} // ***** END sendOutput *****
