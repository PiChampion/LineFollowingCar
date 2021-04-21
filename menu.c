//------------------------------------------------------------------------------
//
//  Description: This file contains code for a menu
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

unsigned int menu;
unsigned int previous_menu = DUMMY_VALUE;
extern unsigned volatile int ADC_Thumb;

void Menu_Process(void) {
//------------------------------------------------------------------------------
// Displays menu options to the user
//------------------------------------------------------------------------------ 
  menu = ADC_Thumb >> DIVIDE_BY_128; // menu will be 0 - 7 (divide by 128)
  
  switch(menu) {
    case(EVERYTHING):
      if(previous_menu == menu);
      else {
        set_display("   FIND   ", "   INFO   ", "  115200  ", "          ");
        previous_menu = EVERYTHING;
      }
      break;
    case(MENU_1):
      if(previous_menu == menu);
      else {
        set_display("    NO    ", "   MENU   ", "  OPTION  ", "    1     ");
        previous_menu = MENU_1;
      }
      break;
    case(MENU_2):
      if(previous_menu == menu);
      else {
        set_display("    NO    ", "   MENU   ", "  OPTION  ", "    2     ");
        previous_menu = MENU_2;
      }
      break;
    case(MENU_3):
      if(previous_menu == menu);
      else {
        set_display("    NO    ", "   MENU   ", "  OPTION  ", "    3     ");
        previous_menu = MENU_3;
      }
      break;
    case(MENU_4):
      if(previous_menu == menu);
      else {
        set_display("    NO    ", "   MENU   ", "  OPTION  ", "    4     ");
        previous_menu = MENU_4;
      }
      break;
    case(MENU_5):
      if(previous_menu == menu);
      else {
        set_display("    NO    ", "   MENU   ", "  OPTION  ", "    5     ");
        previous_menu = MENU_5;
      }
      break;
    case(MENU_6):
      if(previous_menu == menu);
      else {
        set_display("    NO    ", "   MENU   ", "  OPTION  ", "    6     ");
        previous_menu = MENU_6;
      }
      break;
    case(MENU_7):
      if(previous_menu == menu);
      else {
        set_display("    NO    ", "   MENU   ", "  OPTION  ", "    7     ");
        previous_menu = MENU_7;
      }
      break;
    default:
        set_display("    NO    ", "   MENU   ", "  OPTION  ", "          ");
      break;
  }
//------------------------------------------------------------------------------
}