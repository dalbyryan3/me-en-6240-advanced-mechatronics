#ifndef IO
#define IO	

/******************************************************************************
 * PROGRAM COMMENTS (PURPOSE, HISTORY)
 ******************************************************************************/
/*
 * io.h (from invest.c)
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

#include "investment.h"     // Investment data structure 

/******************************************************************************
 * DATA TYPE DEFINITIONS (HERE, A STRUCT)  ==SecA.4.4==
 ******************************************************************************/

/* getUserInput
 * 
 * This reads the user's input into the struct pointed at by invp, 
 * and returns TRUE (1) if the input is valid, FALSE (0) if not.
 */
int getUserInput(Investment *invp);


/* sendOutput
 *
 * This function takes the array of investment values (a pointer to the first
 * element, which is a double) and the number of years (an int).  We could
 * have just passed a pointer to the entire investment record, but we decided 
 * to demonstrate some different syntax.
 */
void sendOutput(double *arr, int yrs);

#endif
