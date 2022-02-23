#include<stdio.h>
#include<math.h>
#include "NU32.h"

int main()
{
  float f1=2.07, f2;
  long double d1=2.07, d2;

  unsigned int elapsedns;
  char outstring[100];

  NU32_WriteUART3("\r\ncosf(f1):\r\n");
  _CP0_SET_COUNT(0);

  f2 = cosf(f1);
  f2 = cosf(f1);
  f2 = cosf(f1);
  f2 = cosf(f1);
  f2 = cosf(f1);
  f2 = cosf(f1);
  f2 = cosf(f1);
  f2 = cosf(f1);
  f2 = cosf(f1);
  f2 = cosf(f1);
  elapsedns = (25 * _CP0_GET_COUNT())/10;
  sprintf(outstring, "%u\r\n", elapsedns);
  NU32_WriteUART3(outstring);

  NU32_WriteUART3("\r\nsqrtf(f1):\r\n");
  _CP0_SET_COUNT(0);
  f2 = sqrtf(f1);
  f2 = sqrtf(f1);
  f2 = sqrtf(f1);
  f2 = sqrtf(f1);
  f2 = sqrtf(f1);
  f2 = sqrtf(f1);
  f2 = sqrtf(f1);
  f2 = sqrtf(f1);
  f2 = sqrtf(f1);
  f2 = sqrtf(f1);
  elapsedns = (25 * _CP0_GET_COUNT())/10;
  sprintf(outstring, "%u\r\n", elapsedns);
  NU32_WriteUART3(outstring);

  NU32_WriteUART3("\r\ncos(d1):\r\n");
  _CP0_SET_COUNT(0);
  d2 = cos(d1);
  d2 = cos(d1);
  d2 = cos(d1);
  d2 = cos(d1);
  d2 = cos(d1);
  d2 = cos(d1);
  d2 = cos(d1);
  d2 = cos(d1);
  d2 = cos(d1);
  d2 = cos(d1);
  elapsedns = (25 * _CP0_GET_COUNT())/10;
  sprintf(outstring, "%u\r\n", elapsedns);
  NU32_WriteUART3(outstring);

  NU32_WriteUART3("\r\nsqrt(d1):\r\n");
  _CP0_SET_COUNT(0);
  d2 = sqrt(d1);
  d2 = sqrt(d1);
  d2 = sqrt(d1);
  d2 = sqrt(d1);
  d2 = sqrt(d1);
  d2 = sqrt(d1);
  d2 = sqrt(d1);
  d2 = sqrt(d1);
  d2 = sqrt(d1);
  d2 = sqrt(d1);
  elapsedns = (25 * _CP0_GET_COUNT())/10;
  sprintf(outstring, "%u\r\n", elapsedns);
  NU32_WriteUART3(outstring);


  return(0);
}

