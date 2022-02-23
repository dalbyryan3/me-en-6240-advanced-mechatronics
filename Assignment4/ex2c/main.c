/******************************************************************************
 * PROGRAM COMMENTS (PURPOSE, HISTORY)
 ******************************************************************************/
/*
 * main.c (from invest.c)
 *
 * This program takes an initial investment amount, an expected annual
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

/******************************************************************************
 * PREPROCESSOR COMMANDS   ==SecA.4.3==
 ******************************************************************************/

#include "io.h"     // IO helper functions
#include "calculate.h"     // Calculation helper functions
#include "investment.h"     // Investment data structure 

/******************************************************************************
 * MAIN FUNCTION   ==SecA.4.2==
 ******************************************************************************/

int main(void) {

  Investment inv;                // variable definition, ==SecA.4.5==

  while(getUserInput(&inv)) {    // while loop ==SecA.4.14== 
    inv.invarray[0] = inv.inv0;  // struct access ==SecA.4.4==
    calculateGrowth(&inv);       // & referencing (pointers) ==SecA.4.6, A.4.8==
    sendOutput(inv.invarray,     // passing a pointer to an array ==SecA.4.9==
               inv.years);       // passing a value, not a pointer ==SecA.4.6==
  }
  return(0);                     // return value of main ==SecA.4.6==
} // ***** END main *****

