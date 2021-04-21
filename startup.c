//------------------------------------------------------------------------------
//
//  Description: This file contains code for the startup
//
//
//  Jan 2019
//  Built with IAR Embedded Workbench Version: V4.10A/W32 (7.12.4)
//------------------------------------------------------------------------------

//------------------------------------------------------------------------------

#include  "functions.h"
#include  "msp430.h"
#include  "macros.h"
#include <string.h>

extern volatile unsigned int startup_counter;
extern unsigned int startup_complete;
unsigned int startup_began = RESET_STATE;

void Startup_Process(void) {
//------------------------------------------------------------------------------
// Controls the startup process
//------------------------------------------------------------------------------
  if(!startup_began) {
    set_display(" START UP ", "          ", "          ", "          ");
    startup_began = YES;
  }
  if(startup_counter > ONE_SECOND_STARTUP) {
    startup_complete = YES;
  }
//------------------------------------------------------------------------------
}