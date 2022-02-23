// In-class Quiz 1 Ryan Dalby
// The format below denotes a solution to a part of the quiz, uncomment between the ### everywhere for that part to run the solution for that part (be sure to also comment out ORGINAL if Part is not denoted as same as original) (For helper functions may have to comment out corresponding code in function too).
/* (I did not do this for part 8 9 10 11) bc of time but the solution is in the code*/
// ### Part X
// 
// ###


/******************************************************************************
 * PROGRAM COMMENTS (PURPOSE, HISTORY)
 ******************************************************************************/

/*
 * invest.c
 *
 * This program takes an initial investment amount, an expected annual
 * return rate, and the number of years, and calculates the growth of
 * the investment.  The main point of this program, though, is to
 * demonstrate some C syntax.  
 *
 * References to further reading are indicated by ==SecA.B.C==
 *
 * HISTORY:  
 * Dec 20, 2011   Created by Kevin Lynch
 * Jan 4, 2012    Modified by Kevin Lynch (small changes, altered comments)
 */

/******************************************************************************
 * PREPROCESSOR COMMANDS   ==SecA.4.3==
 ******************************************************************************/

#include <stdio.h>      // input/output library
// ### Part 1
#include <stdlib.h>
// ###

#define MAX_YEARS 100   // Constant indicating max number of years to track

/******************************************************************************
 * DATA TYPE DEFINITIONS (HERE, A STRUCT)  ==SecA.4.4==
 ******************************************************************************/

/* typedef struct { */
/*   double inv0;                    // initial investment */
/*   double growth;                  // growth rate, where 1.0 = zero growth */
/*   int years;                      // number of years to track */
/*   double invarray[MAX_YEARS+1];   // investment array   ==SecA.4.9== */
/* } Investment;                     // the new data type is called Investment */


// ### Part 7
typedef struct {
  float inv0;                    // initial investment
  float growth;                  // growth rate, where 1.0 = zero growth
  int years;                      // number of years to track
  float invarray[MAX_YEARS+1];   // investment array   ==SecA.4.9==
} Investment;                     // the new data type is called Investment
// ###

/******************************************************************************
 * GLOBAL VARIABLES   ==SecA.4.2, A.4.5==
 ******************************************************************************/

// no global variables in this program

/******************************************************************************
 * HELPER FUNCTION PROTOTYPES  ==SecA.4.2==
 ******************************************************************************/

int getUserInput(Investment *invp);     // invp is a pointer to type ...
void calculateGrowth(Investment *invp); // ... Investment ==SecA.4.6, A.4.8==
void sendOutput(float *arr, int *years);

/******************************************************************************
 * MAIN FUNCTION   ==SecA.4.2==
 ******************************************************************************/

int main(void) {

  Investment inv;                // variable definition, ==SecA.4.5==

  // ### Part 1
  /* while(1){ */
  /*   if(!getUserInput(&inv)){ */
  /*     exit(0); // Although input was invalid, we successfully exited */
  /*     /1* break; *1/ */ 
  /*   } */
  /*   inv.invarray[0] = inv.inv0;  // struct access ==SecA.4.4== */
  /*   calculateGrowth(&inv);       // & referencing (pointers) ==SecA.4.6, A.4.8== */
  /*   sendOutput(inv.invarray,     // passing a pointer to an array ==SecA.4.9== */
  /*              inv.years);       // passing a value, not a pointer ==SecA.4.6== */
  /* } */
  // ###

  // ### Part 2
  /* while(getUserInput(&inv)) {    // while loop ==SecA.4.14== */ 
  /*   calculateGrowth(&inv);       // & referencing (pointers) ==SecA.4.6, A.4.8== */
  /*   sendOutput(inv.invarray,     // passing a pointer to an array ==SecA.4.9== */
  /*              inv.years);       // passing a value, not a pointer ==SecA.4.6== */
  /* } */
  // ###

  // ### ORIGINAL, Part 3, Part 4, Part 5, Part 6, Part 7, Part 8, Part 9, Part 10, Part 11
  while(getUserInput(&inv)) {    // while loop ==SecA.4.14== 
    inv.invarray[0] = inv.inv0;  // struct access ==SecA.4.4==
    calculateGrowth(&inv);       // & referencing (pointers) ==SecA.4.6, A.4.8==
    sendOutput(inv.invarray,     // passing a pointer to an array ==SecA.4.9==
               &(inv.years));       // passing a value, not a pointer ==SecA.4.6==
  }
  // ###
  return(0);                     // return value of main ==SecA.4.6==
} // ***** END main *****

/******************************************************************************
 * HELPER FUNCTIONS   ==SecA.4.2==
 ******************************************************************************/

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


  // ### Part 5 and 6
  for (i=1; i!=(invp->years + 1); i+=1) {   // relational operators ==SecA.4.10==
                                         // struct access ==SecA.4.4==
    invp->invarray[i] = invp->growth * invp->invarray[i-1]; 
  }
  // ###
} // ***** END calculateGrowth *****


/* getUserInput
 * 
 * This reads the user's input into the struct pointed at by invp, 
 * and returns TRUE (1) if the input is valid, FALSE (0) if not.
 */
int getUserInput(Investment *invp) {

  int valid;  	   // int used as a boolean ==SecA.4.10==

  // I/O functions in stdio.h ==SecA.4.15==
  printf("Enter investment, growth rate, number of yrs (up to %d): ",MAX_YEARS);
  /* scanf("%lf %lf %d", &(invp->inv0), &(invp->growth), &(invp->years)); */
  scanf("%f %f %d", &(invp->inv0), &(invp->growth), &(invp->years));

  // ### Part 3
  /* printf("You entered %lf, %lf, and %d\n", invp->inv0, invp->growth, invp->years); */
  // ###

  // logical operators ==SecA.4.11==
  valid = (invp->inv0 > 0) && (invp->growth > 0) &&
    (invp->years > 0) && (invp->years <= MAX_YEARS);
  printf("Valid input?  %d\n",valid);

  // ### Part 11
  /* valid = !((invp->inv0 > 0) || (invp->growth > 0) || */ 
  /*   (invp->years > 0) || (invp->years <= MAX_YEARS)); */
  /* printf("Valid input?  %d\n",valid); */

  // ###

  // if-else ==SecA.4.13==
  if (!valid) { // ! is logical NOT ==SecA.4.11== 
    printf("Invalid input; exiting.\n");
  }
  // ### Part 9
  else{
    printf("Input is valid\n");
  }
  // ###

  // ### Part 2
  /* else{ */
  /*   invp->invarray[0] = invp->inv0; */
  /* } */
  // ###

  return(valid);
} // ***** END getUserInput *****


/* sendOutput
 *
 * This function takes the array of investment values (a pointer to the first
 * element, which is a double) and the number of years (an int).  We could
 * have just passed a pointer to the entire investment record, but we decided 
 * to demonstrate some different syntax.
 */
void sendOutput(float *arr, int *yrs) {

  int i;
  char outstring[100];  // defining a string ==SecA.4.9==

  printf("\nRESULTS:\n\n");
  for (i=0; i<=(*yrs); i++) {  // ++, +=, math in ==SecA.4.7==
    sprintf(outstring,"Year %3d:  %10.2f\n",i,arr[i]); 
    // ### Part 4
    /* //outstring[2] = 0; // Thinks termination occurs after 3rd element because 0 in ascii is NULL */
    /* outstring[2] = '0'; */
    // ###
    printf("%s",outstring);
  }


  // ### Part 10
  /* int i = 0; */
  /* while (i <= (*yrs)){ */
  /*   sprintf(outstring,"Year %3d:  %10.2f\n",i,arr[i]); */ 
  /*   printf("%s",outstring); */
  /*   i += 1; */
  /* } */

  // ###

  printf("\n");
} // ***** END sendOutput *****
