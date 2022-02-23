#ifndef INVESTMENT
#define INVESTMENT	

/******************************************************************************
 * PROGRAM COMMENTS (PURPOSE, HISTORY)
 ******************************************************************************/
/*
 * investment.h (from invest.c)
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

#define MAX_YEARS 100   // Constant indicating max number of years to track

/******************************************************************************
 * DATA TYPE DEFINITIONS (HERE, A STRUCT)  ==SecA.4.4==
 ******************************************************************************/

typedef struct {
  double inv0;                    // initial investment
  double growth;                  // growth rate, where 1.0 = zero growth
  int years;                      // number of years to track
  double invarray[MAX_YEARS+1];   // investment array   ==SecA.4.9==
} Investment;                     // the new data type is called Investment

#endif
