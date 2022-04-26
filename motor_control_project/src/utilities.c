#include "utilities.h"                   
#include "NU32.h"

OperatingMode_t operatingMode = IDLE;

void set_operating_mode(OperatingMode_t mode)
{
  operatingMode = mode;
}

OperatingMode_t get_operating_mode(void)
{
  return operatingMode;
}

const char* get_operating_mode_str(void)
{
  switch (operatingMode)
  {
    case IDLE: return "IDLE";
    case PWM: return "PWM";
    case ITEST: return "ITEST";
    case HOLD: return "HOLD";
    case TRACK: return "TRACK";
  }
}

