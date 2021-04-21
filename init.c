//------------------------------------------------------------------------------
//
//  Description: This file initializes variables and initial conditions
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


void Init_Conditions(void){
//------------------------------------------------------------------------------
  int i;
  extern char display_line[LINES][CHAR_SPACES];
  extern char *display[LINES];
  extern volatile unsigned char update_display;
  extern volatile unsigned int update_display_count;

  for(i=FIRST_CHAR;i<CHAR_SPACES;i++){
    display_line[LINE_ONE][i] = RESET_STATE;
    display_line[LINE_TWO][i] = RESET_STATE;
    display_line[LINE_THREE][i] = RESET_STATE;
    display_line[LINE_FOUR][i] = RESET_STATE;
  }
  display_line[LINE_ONE][LAST_CHAR] = RESET_STATE;
  display_line[LINE_TWO][LAST_CHAR] = RESET_STATE;
  display_line[LINE_THREE][LAST_CHAR] = RESET_STATE;
  display_line[LINE_FOUR][LAST_CHAR] = RESET_STATE;

  display[LINE_ONE] = &display_line[LINE_ONE][FIRST_CHAR];
  display[LINE_TWO] = &display_line[LINE_TWO][FIRST_CHAR];
  display[LINE_THREE] = &display_line[LINE_THREE][FIRST_CHAR];
  display[LINE_FOUR] = &display_line[LINE_FOUR][FIRST_CHAR];
  update_display = RESET_STATE;
  update_display_count = RESET_STATE;
// Interrupts are disabled by default, enable them.
  enable_interrupts();
//------------------------------------------------------------------------------
}