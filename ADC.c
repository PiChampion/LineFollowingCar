//------------------------------------------------------------------------------
//
//  Description: This file contains ADC functions
//
//
//  Feb 2020
//  Built with IAR Embedded Workbench Version: V4.10A/W32 (7.12.4)
//------------------------------------------------------------------------------

//------------------------------------------------------------------------------

#include  "functions.h"
#include  "msp430.h"
#include  "macros.h"
#include <string.h>

char ADC_Left_Detect_String[] = "  0x0000  ";
char ADC_Right_Detect_String[] = "  0x0000  ";
char ADC_Thumb_String[] = "  0x0000  ";
//char ADC_Tmp_String[] = "  0x0000  ";
unsigned volatile int ADC_update_1 = RESET_STATE;
unsigned volatile int ADC_update_2 = RESET_STATE;
unsigned volatile int ADC_update_3 = RESET_STATE;
unsigned volatile int ADC_update_1_en = RESET_STATE;
unsigned volatile int ADC_update_2_en = RESET_STATE;
unsigned volatile int ADC_update_3_en = RESET_STATE;
extern unsigned volatile int ADC_Left_Detect;
extern unsigned volatile int ADC_Right_Detect;
extern unsigned volatile int ADC_Thumb;
extern char display_line[LINES][CHAR_SPACES];
extern volatile unsigned char display_changed;
unsigned int LINE_MOVEMENT_STATE = RESET_STATE;

void ADC_Process(void) {
//------------------------------------------------------------------------------
// Updates ADC values on LCD every quarter second
//------------------------------------------------------------------------------
  unsigned int tmp;
  
  if(ADC_update_3 > QUARTER_SECOND) {
    tmp = HEXtoBCD(ADC_Thumb);                         //
    adc_line4(tmp, THUMB);                                   // Place String in Display
    ADC_update_3 = RESET_STATE;
  }
  
  if(ADC_update_2 > QUARTER_SECOND) {
    tmp = HEXtoBCD(ADC_Right_Detect);           //
    adc_line4(tmp, RIGHT_DETECT);                            // Place String in Display
    ADC_update_2 = RESET_STATE;
  }
  
  if(ADC_update_1 > QUARTER_SECOND) {
    tmp = HEXtoBCD(ADC_Left_Detect);             //
    adc_line4(tmp, LEFT_DETECT);                             // Place String in Display
    ADC_update_1 = RESET_STATE;
  }
//------------------------------------------------------------------------------
}

unsigned int HEXtoBCD(unsigned int data) {
//------------------------------------------------------------------------------
// Converts hexadecimal values received into BCD representations
//------------------------------------------------------------------------------
  int tmp = data;
  unsigned int bcd = RESET_STATE;
  unsigned int thousands = RESET_STATE;
  unsigned int hundreds = RESET_STATE;
  unsigned int tens = RESET_STATE;
  unsigned int ones = RESET_STATE;
   
  while (tmp >= THOUSAND) {                                  // Calculate BCD
     tmp = tmp - THOUSAND;
     thousands++;
  }
  while (tmp >= HUNDRED) {                                  // Calculate BCD
     tmp = tmp - HUNDRED;
     hundreds++;
  }
  while (tmp >= TEN) {                                  // Calculate BCD
     tmp = tmp - TEN;
     tens++;
  }
  while (tmp >= ONE) {                                  // Calculate BCD
     tmp = tmp - ONE;
     ones++;
  }
      
  bcd = bcd + ones;
  bcd = bcd + (tens << SECOND_NIBBLE_SHIFT);// Insert digit
  bcd = bcd + (hundreds << THIRD_NIBBLE_SHIFT);// Insert digit
  bcd = bcd + (thousands << FOURTH_NIBBLE_SHIFT);// Insert digit
   
  return bcd;
//------------------------------------------------------------------------------
}

void adc_line4(unsigned int data, int x) {
//------------------------------------------------------------------------------
// Places BCD values calculated in the HEXtoBCD function onto the display
//------------------------------------------------------------------------------
unsigned int tmp = RESET_STATE;
  
  switch(x) {
    case(LEFT_DETECT):
      tmp = data & FIRST_NIBBLE_MASK;
      ADC_Left_Detect_String[ONES_DIGIT] = ASCII_START + tmp;
      tmp = data & SECOND_NIBBLE_MASK;
      tmp = tmp >> SECOND_NIBBLE_SHIFT;
      ADC_Left_Detect_String[TENS_DIGIT] = ASCII_START + tmp;
      tmp = data & THIRD_NIBBLE_MASK;
      tmp = tmp >> THIRD_NIBBLE_SHIFT;
      ADC_Left_Detect_String[HUNDREDS_DIGIT] = ASCII_START + tmp;
      tmp = data & FOURTH_NIBBLE_MASK;
      tmp = tmp >> FOURTH_NIBBLE_SHIFT;
      ADC_Left_Detect_String[THOUSANDS_DIGIT] = ASCII_START + tmp;
      strcpy(display_line[LINE_TWO], ADC_Left_Detect_String);           // Update Right_Detect on Display
      update_string(display_line[LINE_TWO], STRING_TWO);
      display_changed = YES;
      break;
    case(RIGHT_DETECT):
      tmp = data & FIRST_NIBBLE_MASK;
      ADC_Right_Detect_String[ONES_DIGIT] = ASCII_START + tmp;
      tmp = data & SECOND_NIBBLE_MASK;
      tmp = tmp >> SECOND_NIBBLE_SHIFT;
      ADC_Right_Detect_String[TENS_DIGIT] = ASCII_START + tmp;
      tmp = data & THIRD_NIBBLE_MASK;
      tmp = tmp >> THIRD_NIBBLE_SHIFT;
      ADC_Right_Detect_String[HUNDREDS_DIGIT] = ASCII_START + tmp;
      tmp = data & FOURTH_NIBBLE_MASK;
      tmp = tmp >> FOURTH_NIBBLE_SHIFT;
      ADC_Right_Detect_String[THOUSANDS_DIGIT] = ASCII_START + tmp;
      strcpy(display_line[LINE_THREE], ADC_Right_Detect_String);        // Update Right_Detect on Display
      update_string(display_line[LINE_THREE], STRING_THREE);
      display_changed = YES;
      break;
    case(THUMB):
      tmp = data & FIRST_NIBBLE_MASK;
      ADC_Thumb_String[ONES_DIGIT] = ASCII_START + tmp;
      tmp = data & SECOND_NIBBLE_MASK;
      tmp = tmp >> SECOND_NIBBLE_SHIFT;
      ADC_Thumb_String[TENS_DIGIT] = ASCII_START + tmp;
      tmp = data & THIRD_NIBBLE_MASK;
      tmp = tmp >> THIRD_NIBBLE_SHIFT;
      ADC_Thumb_String[HUNDREDS_DIGIT] = ASCII_START + tmp;
      tmp = data & FOURTH_NIBBLE_MASK;
      tmp = tmp >> FOURTH_NIBBLE_SHIFT;
      ADC_Thumb_String[THOUSANDS_DIGIT] = ASCII_START + tmp;
      strcpy(display_line[LINE_FOUR], ADC_Thumb_String);                // Update Right_Detect on Display
      update_string(display_line[LINE_FOUR], STRING_FOUR);
      display_changed = YES;
      break;
    default:
      break;
  }
//------------------------------------------------------------------------------
}

void HEXtoASCII(char string[DISPLAY_LINE], unsigned int data) {
//------------------------------------------------------------------------------
// Changes given string in the format "  0x????  " to represent decimal value
//------------------------------------------------------------------------------
  unsigned int tmp, tmp1;
  
  tmp = HEXtoBCD(data);
  tmp1 = tmp & FIRST_NIBBLE_MASK;
  string[ONES_DIGIT] = ASCII_START + tmp1;
  tmp1 = tmp & SECOND_NIBBLE_MASK;
  tmp1 = tmp1 >> SECOND_NIBBLE_SHIFT;
  string[TENS_DIGIT] = ASCII_START + tmp1;
  tmp1 = tmp & THIRD_NIBBLE_MASK;
  tmp1 = tmp1 >> THIRD_NIBBLE_SHIFT;
  string[HUNDREDS_DIGIT] = ASCII_START + tmp1;
  tmp1 = tmp & FOURTH_NIBBLE_MASK;
  tmp1 = tmp1 >> FOURTH_NIBBLE_SHIFT;
  string[THOUSANDS_DIGIT] = ASCII_START + tmp1;
//------------------------------------------------------------------------------
}








