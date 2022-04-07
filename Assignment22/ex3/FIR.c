#include "FIR.h"
#include <stdio.h>
#include "NU32.h"

// Initialize function for the filter
void initFilterInformation(FIRFilterInformation *filterInfoPtr, int filterOrder, double *bValues, double *memory)
{
  filterInfoPtr->filterSlots = (filterOrder-1);

  // Using getFIRCoefficent.m can get bValues by passing in fN
  filterInfoPtr->bValues = bValues;

  // Will initialize memory of filter to be default double values
  filterInfoPtr->memory = memory;
}

// Manage store signal vlues
void updateMemory(FIRFilterInformation *filterInfoPtr, double signal_val)
{
  int i;
  double nextVal = signal_val;
  for(i=0; i < filterInfoPtr->filterSlots; i++)
  {
    double tmp = filterInfoPtr->memory[i];
    filterInfoPtr->memory[i] = nextVal;
    nextVal = tmp;
  }  
}

// Apply filter to signal
double filterSignal(FIRFilterInformation *filterInfoPtr, double signal_val)
{
  int i;
  // Test:
  // char buf[100];
  // for(i=0; i < filterInfoPtr->filterSlots; i++)
  // {
  //   sprintf(buf, "i=%d mem=$%.2f\r\n", i, filterInfoPtr->memory[i]);
  //   NU32_WriteUART3(buf);
  // }

  // Update memory
  updateMemory(filterInfoPtr, signal_val);

  // // Test:
  // NU32_WriteUART3("\r\n");
  // for(i=0; i < filterInfoPtr->filterSlots; i++)
  // {
  //   sprintf(buf, "i=%d mem=$%.2f\r\n", i, filterInfoPtr->memory[i]);
  //   NU32_WriteUART3(buf);
  // }
  // NU32_WriteUART3("DONE\r\n");

  // FIR filter signal
  double filtered_signal_val = 0;
  for(i=0; i < filterInfoPtr->filterSlots; i++)
  {
    filtered_signal_val += filterInfoPtr->bValues[i] * filterInfoPtr->memory[i];
  }  

  return filtered_signal_val;
}
