#include <stdio.h>
#include "NU32.h"

#ifndef FIR
#define FIR

// Create a new datatype for your filter
typedef struct {
    int filterSlots; // How many bValues there are, filter order+1
    double *bValues; // Must have length of filterSlots 
    double *memory; // Must have length of filterSlots 
}FIRFilterInformation;

// Declare public functions
void initFilterInformation(FIRFilterInformation *filterInfoPtr, int filterOrder, double *bValues, double *memory);
void updateMemory(FIRFilterInformation *filterInfo, double signal_val);
double filterSignal(FIRFilterInformation *filterInfo, double signal_val);

#endif
