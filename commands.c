//------------------------------------------------------------------------------
//
//  Description: This file contains code to interpret received commands
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

extern unsigned int time_display_enable;
unsigned int forward_movement_state = RESET_STATE;
unsigned int backwards_movement_state = RESET_STATE;
unsigned int left_movement_state = RESET_STATE;
unsigned int right_movement_state = RESET_STATE;

extern unsigned volatile int movement_time;

unsigned int forward_command_engaged = RESET_STATE;
unsigned int backwards_command_engaged = RESET_STATE;
unsigned int left_command_engaged = RESET_STATE;
unsigned int right_command_engaged = RESET_STATE;
unsigned int routine_engaged = RESET_STATE;
unsigned int number_visited = RESET_STATE;
char on_number[DISPLAY_LINE] = "ARRIVED X ";

unsigned int command_state = RESET_STATE;
unsigned int movement_value = RESET_STATE;
extern char Command_Buffer[COMMAND_LINES][COMMAND_CHARS];
extern unsigned int current_command;
extern unsigned int current_commands;
extern unsigned int ROUTINE_STATE;
extern unsigned volatile int movement_state;

void Command_Process(void) {
//------------------------------------------------------------------------------
// State machine for commands routine
//------------------------------------------------------------------------------
  
  if(current_commands) {
    if(Command_Buffer[current_command][DIRECTION_CHAR] == 'T') {
      movement_state = RESET_STATE;
      ROUTINE_STATE = WAIT_BUFFER_3;
      TB0CCTL2 |= CCIE;                   // CCR2 enable interrupt
      routine_engaged = YES;
      current_command++;
      if(current_command >= COMMAND_LINES) {
        current_command = BEGINNING;     // Circular buffer back to beginning
      }
      current_commands--;
    }
    if(!(forward_command_engaged || backwards_command_engaged || left_command_engaged || right_command_engaged || routine_engaged)) {
      switch(Command_Buffer[current_command][DIRECTION_CHAR]) {
        case('F'):
          movement_value = movement_value + ((Command_Buffer[current_command][HUNDREDS_CHAR] - ASCII_START)*HUNDRED);
          movement_value = movement_value + ((Command_Buffer[current_command][TENS_CHAR] - ASCII_START)*TEN);
          movement_value = movement_value + ((Command_Buffer[current_command][ONES_CHAR] - ASCII_START));
          forward_command_engaged = YES;
          break;
        case('B'):
          movement_value = movement_value + ((Command_Buffer[current_command][HUNDREDS_CHAR] - ASCII_START)*HUNDRED);
          movement_value = movement_value + ((Command_Buffer[current_command][TENS_CHAR] - ASCII_START)*TEN);
          movement_value = movement_value + ((Command_Buffer[current_command][ONES_CHAR] - ASCII_START));
          backwards_command_engaged = YES;
          break;
        case('R'):
          movement_value = movement_value + ((Command_Buffer[current_command][HUNDREDS_CHAR] - ASCII_START)*HUNDRED);
          movement_value = movement_value + ((Command_Buffer[current_command][TENS_CHAR] - ASCII_START)*TEN);
          movement_value = movement_value + ((Command_Buffer[current_command][ONES_CHAR] - ASCII_START));
          right_command_engaged = YES;
          break;
        case('L'):
          movement_value = movement_value + ((Command_Buffer[current_command][HUNDREDS_CHAR] - ASCII_START)*HUNDRED);
          movement_value = movement_value + ((Command_Buffer[current_command][TENS_CHAR] - ASCII_START)*TEN);
          movement_value = movement_value + ((Command_Buffer[current_command][ONES_CHAR] - ASCII_START));
          left_command_engaged = YES;
          break;
        case('A'):
          ROUTINE_STATE = INITIAL_TURN;
          TB0CCTL2 |= CCIE;                   // CCR2 enable interrupt
          routine_engaged = YES;
          current_command++;
          if(current_command >= COMMAND_LINES) {
            current_command = BEGINNING;     // Circular buffer back to beginning
          }
          break;
        case('K'):
          on_number[NUMBER_POSITION] = Command_Buffer[current_command][ONES_CHAR];
          set_display_line(on_number, LINE_ONE);
          current_command++;
          if(current_command >= COMMAND_LINES) {
            current_command = BEGINNING;     // Circular buffer back to beginning
          }
          break;
        case('I'):
          if(Command_Buffer[current_command][ONES_CHAR] - ASCII_START) {
            set_display_line("IR_LED ON ", LINE_ONE);
            P3OUT |= IR_LED;
          }
          else {
            set_display_line("IR_LED OFF", LINE_ONE);
            P3OUT &= ~IR_LED;
          }
          current_command++;
          if(current_command >= COMMAND_LINES) {
            current_command = BEGINNING;     // Circular buffer back to beginning
          }
          break;
        case('T'):
          break;
        default: break;
      }
      time_display_enable = YES;
      current_commands--;
    }
  }
  
  if(forward_command_engaged) {
    switch(forward_movement_state) {
      case(RESET_STATE):
        set_display_line(" FORWARD  ", LINE_ONE);
        Forward_Movement();
        movement_time = RESET_STATE;
        forward_movement_state++;
        break;
      case(STATE_1):
        if(movement_time > movement_value) {
          Stop_Movement();
          forward_movement_state = STATE_2;
        }
        break;
      case(STATE_2):
        if(movement_time > movement_value + FIFTY_MSEC) {
          forward_movement_state = RESET_STATE;
          forward_command_engaged = RESET_STATE;
          current_command++;
          if(current_command >= COMMAND_LINES) {
            current_command = BEGINNING;     // Circular buffer back to beginning
          }
          movement_value = RESET_STATE;
        }
        break;
      default:
        break;
    }
  }

  if(backwards_command_engaged) {
    switch(backwards_movement_state) {
      case(RESET_STATE):
        set_display_line(" BACKWARD ", LINE_ONE);
        Reverse_Movement();
        movement_time = RESET_STATE;
        backwards_movement_state++;
        break;
      case(STATE_1):
        if(movement_time > movement_value) {
          Stop_Movement();
          backwards_movement_state = STATE_2;
        }
        break;
      case(STATE_2):
        if(movement_time > movement_value + FIFTY_MSEC) {
          backwards_movement_state = RESET_STATE;
          backwards_command_engaged = RESET_STATE;
          current_command++;
          if(current_command >= COMMAND_LINES) {
            current_command = BEGINNING;     // Circular buffer back to beginning
          }
          movement_value = RESET_STATE;
        }
        break;
      default:
        break;
    }
  }
  
  if(left_command_engaged) {
    switch(left_movement_state) {
      case(RESET_STATE):
        set_display_line("   LEFT   ", LINE_ONE);
        Spin_CCW();
        movement_time = RESET_STATE;
        left_movement_state++;
        break;
      case(STATE_1):
        if(movement_time > movement_value) {
          Stop_Movement();
          left_movement_state = STATE_2;
        }
        break;
      case(STATE_2):
        if(movement_time > movement_value + FIFTY_MSEC) {
          left_movement_state = RESET_STATE;
          left_command_engaged = RESET_STATE;
          current_command++;
          if(current_command >= COMMAND_LINES) {
            current_command = BEGINNING;     // Circular buffer back to beginning
          }
          movement_value = RESET_STATE;
        }
        break;
      default:
        break;
    }
  }
  
  if(right_command_engaged) {
    switch(right_movement_state) {
      case(RESET_STATE):
        set_display_line("  RIGHT   ", LINE_ONE);
        Spin_CW();
        movement_time = RESET_STATE;
        right_movement_state++;
        break;
      case(STATE_1):
        if(movement_time > movement_value) {
          Stop_Movement();
          right_movement_state = STATE_2;
        }
        break;
      case(STATE_2):
        if(movement_time > movement_value + FIFTY_MSEC) {
          right_movement_state = RESET_STATE;
          right_command_engaged = RESET_STATE;
          current_command++;
          if(current_command >= COMMAND_LINES) {
            current_command = BEGINNING;     // Circular buffer back to beginning
          }
          movement_value = RESET_STATE;
        }
        break;
      default:
        break;
    }
  }
  
//------------------------------------------------------------------------------
}








