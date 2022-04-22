#include "NU32.h"          // config bits, constants, funcs for startup and UART
// include other header files here
#include <stdio.h>
#include "encoder.h"
#include "isense.h"
#include "currentcontrol.h"                   
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
  __builtin_enable_interrupts();

  while(1)
  {
    NU32_ReadUART3(buffer,BUF_SIZE); // we expect the next character to be a menu command
    NU32_LED2 = 1;                   // clear the error LED
    switch (buffer[0]) {
      // case 'd':                      
      // {
      //   // dummy command for demonstration purposes
      //   int n = 0;
      //   NU32_ReadUART3(buffer,BUF_SIZE);
      //   sscanf(buffer, "%d", &n);
      //   sprintf(buffer,"%d\r\n", n + 1); // return the number + 1
      //   NU32_WriteUART3(buffer);
      //   break;
      // }
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
        NU32_WriteUART3(buffer);
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

        // sprintf(buffer, "%f\r\n", adc_voltage());
        // NU32_WriteUART3(buffer); // send to client 

        // sprintf(buffer, "%f\r\n", adc_current_sense_value_mA());
        // NU32_WriteUART3(buffer); // send to client 

        // Get averaged ADC counts
        // NU32_WriteUART3("\r\n");
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

        sprintf(buffer, "PWM direction val is now %.3f and mode is PWM \r\n", pwm_val);
        NU32_WriteUART3(buffer);
        break;
      }
      case 'p': 
      {
        set_operating_mode(IDLE);

        NU32_WriteUART3("Mode is IDLE \r\n");
        break;
      }
      case 'r': 
      {
        // Get operating mode
        sprintf(buffer, "%s\r\n", get_operating_mode_str());
        NU32_WriteUART3(buffer); // send to client
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
