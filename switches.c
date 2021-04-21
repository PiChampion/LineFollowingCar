//------------------------------------------------------------------------------
//
//  Description: This file contains the switches functions
//
//
//  Jim Carlson
//  Jan 2020
//  Built with IAR Embedded Workbench Version: V4.10A/W32 (7.11.2)
//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
#include  "functions.h"
#include  "msp430.h"
#include  "macros.h"
#include <string.h>


  // Global Variables
extern volatile unsigned int Time_Sequence;


void Switches_Process(void) {
  
  if (!(P4IN & SW1)){
//    while(Time_Sequence < SWITCH_WAIT) {}         // Provide time for switch to settle
//    set_display("          ", "  USING   ", "  SMCLK   ", "          ");  // Set the LCD display
    Init_Port3(USE_SMCLK);
  }
  
  if (!(P2IN & SW2)){
//    while(Time_Sequence < SWITCH_WAIT) {}         // Provide time for switch to settle
//    set_display("          ", "  USING   ", "  GPIO    ", "          ");  // Set the LCD display
    Init_Port3(USE_GPIO);
  }
  return;
}