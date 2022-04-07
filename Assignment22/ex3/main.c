#include <stdio.h>
#include <math.h>
#include "NU32.h"
#include "FIR.h"

#define BUFFER_SIZE 100
#define SIGNAL_LENGTH 1000
#define FIR_FILTER_ORDER 9 
#define FIR_FILTER_SLOTS (FIR_FILTER_ORDER+1)

void buildSignalEx3(double *signal, int signalLength, double Fn);

int main(void)
{
  // Buffer
  char buffer[BUFFER_SIZE];

  // Create a signal to be filtered 
  double signal[SIGNAL_LENGTH];
  // Its corresponding filtered signal
  double filtered_signal[SIGNAL_LENGTH];

  // Assign the order and coefficent values to the filter
  // Frequency for problem
  double Fn = 20;
  // Create signal
  buildSignalEx3(signal, SIGNAL_LENGTH, Fn);
  // Using getFIRCoefficent.m can get bValues by passing in fN
  double bVals[FIR_FILTER_SLOTS] = {0.0162, 0.0379, 0.0931, 0.1559, 0.1969, 0.1969, 0.1559, 0.0931, 0.0379, 0.0162};
  // Will initialize memory of filter to have 0.0 values
  double filterMem[FIR_FILTER_SLOTS] = {0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0};
  // Defining filter
  FIRFilterInformation filterInfo;
  initFilterInformation(&filterInfo, FIR_FILTER_ORDER, bVals, filterMem);

  // Filter the signal- emulating data streaming
  int i;
  for(i=0; i < SIGNAL_LENGTH; i++)
  {
    filtered_signal[i] = filterSignal(&filterInfo, signal[i]);
  }

  // Send the filtered and unfiltered signal back to the host computer to analyze the results
  NU32_WriteUART3("Sending unfiltered signal(col1), filtered signal(col2):\r\n");
  for(i=0; i < SIGNAL_LENGTH; i++)
  {
    sprintf(buffer, "%f,%f\r\n", signal[i], filtered_signal[i]);
    NU32_WriteUART3(buffer);
  }
  NU32_WriteUART3("END\r\n");
  return 0;
}

void buildSignalEx3(double *signal, int signalLength, double Fn)
{
  double dt = 1.0/signalLength; // Signal is assumed to be 1 second long
  double t = 0;
  int i;
  for (i = 0; i < signalLength; i++)
  {
    signal[i] = 0.5*sin(2*M_PI*(0.1*Fn*t)) + 0.5*sin(2*M_PI*(0.5*Fn*t));
    t += dt;
  }
}
