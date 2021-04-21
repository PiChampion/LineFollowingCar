//------------------------------------------------------------------------------
//
//  Description: This file contains code to interact with the display
//
//
//  Jan 2020
//  Built with IAR Embedded Workbench Version: V4.10A/W32 (7.12.4)
//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
#include  "functions.h"
#include  "msp430.h"
#include  "macros.h"
#include <string.h>

//extern volatile unsigned int Time_Sequence;
extern char display_line[LINES][CHAR_SPACES];
extern volatile unsigned char display_changed;
volatile int backlight_state = RESET_STATE;
volatile int backlight_state_1 = RESET_STATE;
extern unsigned volatile int display_state;
extern volatile unsigned char update_display;
unsigned int time_display_enable = RESET_STATE;
char time[] = "  000.0   ";
unsigned int current_time = RESET_STATE;

void Update_Display_Process(void) {
//------------------------------------------------------------------------------
// Updates display every 200ms and updates display after a change
//------------------------------------------------------------------------------
  
  unsigned int tmp, tmp1;
  
  if(display_state > CHANGE) {
    update_display = YES;
    display_state = RESET_STATE;
    if(time_display_enable) {
      current_time = current_time + TWO_HUNDRED_MS;
      tmp = HEXtoBCD(current_time);
      
      tmp1 = tmp & FIRST_NIBBLE_MASK;
      time[TIME_DECIMAL_DIGIT] = ASCII_START + tmp1;
      tmp1 = tmp & SECOND_NIBBLE_MASK;
      tmp1 = tmp1 >> SECOND_NIBBLE_SHIFT;
      time[TIME_ONES_DIGIT] = ASCII_START + tmp1;
      tmp1 = tmp & THIRD_NIBBLE_MASK;
      tmp1 = tmp1 >> THIRD_NIBBLE_SHIFT;
      time[TIME_TENS_DIGIT] = ASCII_START + tmp1;
      tmp1 = tmp & FOURTH_NIBBLE_MASK;
      tmp1 = tmp1 >> FOURTH_NIBBLE_SHIFT;
      time[TIME_HUNDREDS_DIGIT] = ASCII_START + tmp1;
      
      strcpy(display_line[LINE_FOUR], time);           // Update Time on Display
      update_string(display_line[LINE_FOUR], STRING_FOUR);
      display_changed = YES;
    }
  }
//------------------------------------------------------------------------------
}

void Backlight_Update(void) {
//------------------------------------------------------------------------------
// Changes backlight every half second
//------------------------------------------------------------------------------
  if(backlight_state > UPDATE_BACKLIGHT_CTR) {
    backlight_state = RESET_STATE;
    backlight_state_1++;
  }
    
  if(backlight_state_1) {
    if(P6OUT & LCD_BACKLITE) {
        P6OUT &= ~LCD_BACKLITE;                 // Set LCD_BACKLITE Off [Low]
    }
    else {
      P6OUT |= LCD_BACKLITE;                    // Set LCD_BACKLITE On [High]
    }
    backlight_state_1 = RESET_STATE;
  }
//------------------------------------------------------------------------------
}


void set_display(const char line1[DISPLAY_LINE],const char line2[DISPLAY_LINE],
                 const char line3[DISPLAY_LINE],const char line4[DISPLAY_LINE]) {
//------------------------------------------------------------------------------
// Changes all lines of the display
//------------------------------------------------------------------------------                  
  strcpy(display_line[LINE_ONE], line1);
  update_string(display_line[LINE_ONE], STRING_ONE);
  strcpy(display_line[LINE_TWO], line2);
  update_string(display_line[LINE_TWO], STRING_TWO);
  strcpy(display_line[LINE_THREE], line3);
  update_string(display_line[LINE_THREE], STRING_THREE);
  strcpy(display_line[LINE_FOUR], line4);
  update_string(display_line[LINE_FOUR], STRING_FOUR);
  display_changed = YES;
//------------------------------------------------------------------------------
}

void set_display_line(char data[DISPLAY_LINE], unsigned int line) {
//------------------------------------------------------------------------------
// Changes one line of the display
//------------------------------------------------------------------------------                  
  switch(line) {
    case(LINE_ONE):
      strcpy(display_line[LINE_ONE], data);
      update_string(display_line[LINE_ONE], STRING_ONE);
      display_changed = YES;
      break;
    case(LINE_TWO):
      strcpy(display_line[LINE_TWO], data);
      update_string(display_line[LINE_TWO], STRING_TWO);
      display_changed = YES;
      break;
    case(LINE_THREE):
      strcpy(display_line[LINE_THREE], data);
      update_string(display_line[LINE_THREE], STRING_THREE);
      display_changed = YES;
      break;
    case(LINE_FOUR):
      strcpy(display_line[LINE_FOUR], data);
      update_string(display_line[LINE_FOUR], STRING_FOUR);
      display_changed = YES;
      break;
    default:
      break;
  }
//------------------------------------------------------------------------------
}






