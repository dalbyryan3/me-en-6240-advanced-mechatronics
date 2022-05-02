#include "NU32.h"          // config bits, constants, funcs for startup and UART
// include other header files here
#include <stdio.h>
#include "encoder.h"
#include "isense.h"
#include "currentcontrol.h"                   
#include "positioncontrol.h"                   
#include "utilities.h"                   

#define BUF_SIZE 200

int main() 
{
  char buffer[BUF_SIZE];
  NU32_Startup(); // cache on, min flash wait, interrupts on, LED/button init, UART init
  NU32_LED1 = 1;  // turn off the LEDs
  NU32_LED2 = 1;        
  __builtin_disable_interrupts();
  // in future, initialize modules or peripherals here
  set_operating_mode(IDLE);
  encoder_init();
  adc_init();
  currentcontrol_init();
  positioncontrol_init();
  __builtin_enable_interrupts();

  while(1)
  {
    NU32_ReadUART3(buffer,BUF_SIZE); // we expect the next character to be a menu command
    NU32_LED2 = 1;                   // clear the error LED
    switch (buffer[0]) {
      case 'x':
      {
        // Add two numbers and give result
        int n1, n2, res;

        NU32_ReadUART3(buffer,BUF_SIZE);
        sscanf(buffer, "%d", &n1);
        NU32_ReadUART3(buffer,BUF_SIZE);
        sscanf(buffer, "%d", &n2);
        res = n1+n2;
        sprintf(buffer, "%d\r\n", res);
        NU32_WriteUART3(buffer); // send to client
        break;
      }
      case 'c': 
      {
        // Get encoder counts
        sprintf(buffer, "%d\r\n", encoder_counts());
        NU32_WriteUART3(buffer); // send to client 
        break;
      }
      case 'e':
      {
        // Reset encoder count to 32768
        encoder_reset_counts();
        break;
      }
      case 'd': 
      {
        // Get encoder counts converted to degrees
        sprintf(buffer, "%f\r\n", encoder_counts_deg());
        NU32_WriteUART3(buffer); // send to client 
        break;
      }
      case 'a': 
      {
        // Get ADC counts
        sprintf(buffer, "%d\r\n", adc_counts());
        NU32_WriteUART3(buffer); // send to client 
        break;
      }
      case 'b': 
      {
        // Get ADC reading in mA
        sprintf(buffer, "%.3f\r\n", adc_current_sense_value_mA());
        NU32_WriteUART3(buffer); // send to client 
        break;
      }
      case 'f': 
      {
        double pwm_val;
        NU32_ReadUART3(buffer,BUF_SIZE);
        sscanf(buffer, "%f", &pwm_val);
        set_motor_pwm_and_direction_values(pwm_val);
        set_operating_mode(PWM);
        break;
      }
      case 'p': 
      {
        set_operating_mode(IDLE);
        break;
      }
      case 'r': 
      {
        // Get operating mode
        sprintf(buffer, "%s\r\n", get_operating_mode_str());
        NU32_WriteUART3(buffer); // send to client
        break;
      }
      case 'g': 
      {
        // Set current PI gains
        double PGain = 0;
        NU32_ReadUART3(buffer,BUF_SIZE);
        sscanf(buffer, "%f", &PGain);
        set_current_proportional_gain(PGain);

        double IGain = 0;
        NU32_ReadUART3(buffer,BUF_SIZE);
        sscanf(buffer, "%f", &IGain);
        set_current_integral_gain(IGain);

        break;
      }
      case 'h': 
      {
        // Get current PI gains
        sprintf(buffer, "%f\r\n", get_current_proportional_gain());
        NU32_WriteUART3(buffer); // send to client
        sprintf(buffer, "%f\r\n", get_current_integral_gain());
        NU32_WriteUART3(buffer); // send to client
        break;
      }
      case 'k':
      {
        set_operating_mode(IDLE);
        // Test current gains
        set_operating_mode(ITEST);
        // Wait for test to complete
        while (get_operating_mode() == ITEST) { ; }
        // Send results to user
        int len = get_current_ITESTIArrayLength();
        sprintf(buffer, "%d\r\n", len);
        NU32_WriteUART3(buffer); // send to client
        double *actual = get_current_ITESTIActualArray();
        double *reference = get_current_ITESTIReferenceArray();
        int i;
        for (i=0; i < len; i++)
        {
          sprintf(buffer, "%f %f\r\n", reference[i], actual[i]);
          NU32_WriteUART3(buffer); // send to client
        }
        break;
      }
      case 'i': 
      {
        // Set position PID gains
        double PGain = 0;
        NU32_ReadUART3(buffer,BUF_SIZE);
        sscanf(buffer, "%f", &PGain);
        set_position_proportional_gain(PGain);

        double IGain = 0;
        NU32_ReadUART3(buffer,BUF_SIZE);
        sscanf(buffer, "%f", &IGain);
        set_position_integral_gain(IGain);

        double DGain = 0;
        NU32_ReadUART3(buffer,BUF_SIZE);
        sscanf(buffer, "%f", &DGain);
        set_position_derivative_gain(DGain);

        break;
      }
      case 'j': 
      {
        // Get position PID gains
        sprintf(buffer, "%f\r\n", get_position_proportional_gain());
        NU32_WriteUART3(buffer); // send to client
        sprintf(buffer, "%f\r\n", get_position_integral_gain());
        NU32_WriteUART3(buffer); // send to client
        sprintf(buffer, "%f\r\n", get_position_derivative_gain());
        NU32_WriteUART3(buffer); // send to client
        break;
      }
      case 'l':
      {
        // Go to angle (deg)
        set_operating_mode(IDLE);
        double holdRef = 0;
        NU32_ReadUART3(buffer,BUF_SIZE);
        sscanf(buffer, "%f", &holdRef);
        set_position_HOLDReferencePositionDeg(holdRef);
        set_operating_mode(HOLD);
        break;
      }
      case 'm':
      case 'n':
      {
        // Load trajectory (can be a step ('m') or cubic ('n') trajectory)
        int numTrajectorySamples = 0;
        NU32_ReadUART3(buffer,BUF_SIZE);
        sscanf(buffer, "%d", &numTrajectorySamples);
        if (numTrajectorySamples > get_position_TRACKArrayMaxLength())
        {
          NU32_WriteUART3("TRAJECTORY NOT LOADED: TOO MANY SAMPLES FOR PIC32 DATA ARRAY\r\n"); // send to client
          break;
        }

        set_position_TRACKArrayLength(numTrajectorySamples);

        double *arr = get_position_TRACKReferenceArray();
        int i;
        for (i=0; i < numTrajectorySamples; i++)
        {
          NU32_ReadUART3(buffer,BUF_SIZE);
          sscanf(buffer, "%f", &(arr[i]));
        }
        NU32_WriteUART3("TRAJECTORY LOADED\r\n"); // send to client
        break;
      }
      case 'o':
      {
        set_operating_mode(IDLE);
        // Execute trajectory
        set_operating_mode(TRACK);
        // Wait for trajectory tracking to complete
        while (get_operating_mode() == TRACK) { ; }
        // Send results to user
        int len = get_position_TRACKArrayLength();
        sprintf(buffer, "%d\r\n", len);
        NU32_WriteUART3(buffer); // send to client
        double *actual = get_position_TRACKActualArray();
        double *reference = get_position_TRACKReferenceArray();
        int i;
        for (i=0; i < len; i++)
        {
          sprintf(buffer, "%f %f\r\n", reference[i], actual[i]);
          NU32_WriteUART3(buffer); // send to client
        }
        break;
      }
      case 'q':
      {
        // handle q for quit. Return to IDLE mode. 
        set_operating_mode(IDLE);
        break;
      }
      default:
      {
        // Error case
        NU32_LED2 = 0;  // turn on LED2 to indicate an error
        break;
      }
    }
  }
  return 0;
}
