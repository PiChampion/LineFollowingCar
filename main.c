//------------------------------------------------------------------------------
//
//  Description: This file contains the Main Operating System
//
//
//  Ian Hellmer
//  April 2020
//  Built with IAR Embedded Workbench Version: V4.10A/W32 (7.12.4)
//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
#include  "functions.h"
#include  "msp430.h"
#include  "macros.h"
#include <string.h>

// Global Variables
volatile char slow_input_down;
unsigned char display_mode;
extern unsigned int change_IOT_reset;
unsigned int startup_complete = RESET_STATE;

void main(void){
//------------------------------------------------------------------------------
// Main Program
// This is the main routine for the program. Execution of code starts here.
// The operating system is Back Ground Fore Ground.
//------------------------------------------------------------------------------
// Disable the GPIO power-on default high-impedance mode to activate
// previously configured port settings
  PM5CTL0 &= ~LOCKLPM5;
  Init_Ports();                         // Initialize Ports
  Init_Clocks();                        // Initialize Clock System
  Init_Conditions();                    // Initialize Variables and Initial Conditions
  Init_Timers();                        // Initialize Timers
  Init_LCD();                           // Initialize LCD
  Init_ADC();                           // Initialize ADC
  Init_Serial_UCA0(BAUD_115200);        // Initialize Serial Port for USB
  Init_Serial_UCA1(BAUD_115200);
  
  change_IOT_reset = RESET_STATE;
  set_display(" WAITING  ", " STARTUP  ", "          ", "FOR INPUT ");
  
//------------------------------------------------------------------------------
// Begining of the "While" Operating System
//------------------------------------------------------------------------------
  
  while(ALWAYS) { 
//    Backlight_Update();
//    ADC_Process();
//    if(startup_complete) {
      Update_Display_Process();
      Display_Process();
      Serial_Process();
      IOT_Process();
      Command_Process();
      Movement_Process();
//      Menu_Process();
//    }
//    else {
//      Startup_Process();
//      IOT_Process();
//      Update_Display_Process();
//      Display_Process();
//    }
  }
//------------------------------------------------------------------------------
}

