//------------------------------------------------------------------------------
//
//  Description: This file contains code to control the car movement
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

extern char display_line[LINES][CHAR_SPACES];
extern volatile unsigned char display_changed;
extern unsigned int time_display_enable;
extern volatile unsigned int Time_Sequence;
unsigned volatile int movement_state = RESET_STATE;
unsigned int done_turning_R = RESET_STATE;
unsigned int R_turn_routine = RESET_STATE;
unsigned int done_turning_L = RESET_STATE;
unsigned int L_turn_routine = RESET_STATE;
extern unsigned volatile int ADC_Left_Detect;
extern unsigned volatile int ADC_Right_Detect;
unsigned int IR_off_value;
unsigned int black_value;
unsigned int white_value;
unsigned int gray_value;
extern unsigned volatile int calibration_state;
unsigned int ROUTINE_STATE = RESET_STATE;
unsigned int center_to_edge = RESET_STATE;
unsigned int line_threshold = LINE_THRESHOLD;
extern unsigned int routine_engaged;

void Movement_Process(void) {
//------------------------------------------------------------------------------
// State machine for movement routine
//------------------------------------------------------------------------------
  switch(ROUTINE_STATE) {
      case(RESET_STATE):
        break;
      case(INITIAL_TURN):
          Spin_CW();
          movement_state = RESET_STATE;
          ROUTINE_STATE = INITIAL_TURN_END;
          set_display_line(" BL START ", LINE_ONE);
        break;
      case(INITIAL_TURN_END):
        if(movement_state > TURN_90_TIME_CW) {
          Stop_Movement();
          movement_state = RESET_STATE;
          ROUTINE_STATE = WAIT_BUFFER_INITIAL;
        }
        break;
      case(WAIT_BUFFER_INITIAL):
        if(movement_state > ONE_SECOND) {
          Forward_Movement();
          movement_state = RESET_STATE;
          ROUTINE_STATE = WAIT_BUFFER;
        }
        break;
      case(WAIT_BUFFER):
          if(movement_state > TWO_SECONDS) ROUTINE_STATE = FORWARD_STOP;
        break;
      case(FORWARD_STOP):
        if(((ADC_Left_Detect > line_threshold) || (ADC_Right_Detect > line_threshold))) {
          Stop_Movement();
          ROUTINE_STATE = WAIT_BUFFER_1;
          movement_state = RESET_STATE;
          set_display_line("INTERCEPT ", LINE_ONE);
        }
        break;
      case(WAIT_BUFFER_1):
        if(movement_state >= TWO_SECONDS) {
          ROUTINE_STATE = SPIN_AND_SEARCH;
          movement_state = RESET_STATE;
        }
        break;
      case(SPIN_AND_SEARCH):
        Spin_CCW_SLOW();
        if(((ADC_Left_Detect > line_threshold) || (ADC_Right_Detect > line_threshold))) {
          Stop_Movement();
          ROUTINE_STATE = WAIT_BUFFER_2;
          movement_state = RESET_STATE;
        }
        break;
      case(WAIT_BUFFER_2):
        Stop_Movement();
        if(movement_state >= TWO_SECONDS) {
          set_display_line("BL TRAVEL ", LINE_ONE);
          ROUTINE_STATE = MOVE_TO_EDGE;
          movement_state = RESET_STATE;
        }
        break;
      case(MOVE_TO_EDGE):
        Forward_Movement_Slow();
        if(ADC_Left_Detect < line_threshold) {
          ROUTINE_STATE = TRAVERSE_CIRCLE;
          movement_state = RESET_STATE;
        }
        break;
      case(TRAVERSE_CIRCLE):
        if((ADC_Right_Detect < line_threshold)) {
          if(ADC_Left_Detect > SENSITIVE_THRESHOLD) {
            Turn_L_Five_Degrees();
            ROUTINE_STATE = WAIT_FOR_L_TURN;
          }
          else {
            Turn_R_Five_Degrees();
            ROUTINE_STATE = WAIT_FOR_R_TURN;
          }
        }
        break;
      case(WAIT_FOR_R_TURN):
        Turn_R_Five_Degrees();
        if(done_turning_R) {
          if(movement_state > TEN_SECONDS) {
            set_display_line("BL CIRCLE ", LINE_ONE);
          }      
          Forward_Movement_Slow();
          done_turning_R = RESET_STATE;
          ROUTINE_STATE = TRAVERSE_CIRCLE;
        }
        break;
      case(WAIT_FOR_L_TURN):
        Turn_L_Five_Degrees();
        if(done_turning_L) {
          if(movement_state > TEN_SECONDS) {
            set_display_line("BL CIRCLE ", LINE_ONE);
          } 
          Forward_Movement_Slow();
          done_turning_L = RESET_STATE;
          ROUTINE_STATE = TRAVERSE_CIRCLE;
        }
        break;
      case(WAIT_BUFFER_3):
        Stop_Movement();
        set_display_line(" BL EXIT  ", LINE_ONE);
        if(movement_state > TWO_SECONDS) {
          Spin_CCW_SLOW();
          movement_state = RESET_STATE;
          ROUTINE_STATE = TURN_BACK;
        }
        break;
      case(TURN_BACK):
        if(movement_state > TURN_90_TIME_CCW) {
          Stop_Movement();
          movement_state = RESET_STATE;
          ROUTINE_STATE = WAIT_BUFFER_4;
        }
        break;
      case(WAIT_BUFFER_4):
        if(movement_state > TWO_SECONDS) {
          Forward_Movement();
          movement_state = RESET_STATE;
          ROUTINE_STATE = FIND_CENTER;
        }
        break;
      case(FIND_CENTER):
        if(movement_state > THREE_SECONDS) {
          Stop_Movement();
          TB0CCTL2 &= ~CCIE;                    // CCR2 disable interrupt
          ROUTINE_STATE = RESET_STATE;
          routine_engaged = RESET_STATE;
          time_display_enable = RESET_STATE;
          set_display_line(" BL STOP  ", LINE_ONE);
        }
        break;
      default:
        break;
  }
//------------------------------------------------------------------------------
}

void Stop_Movement(void) {
  RIGHT_FORWARD_SPEED = WHEEL_OFF;
  LEFT_FORWARD_SPEED = WHEEL_OFF;
  RIGHT_REVERSE_SPEED = WHEEL_OFF;
  LEFT_REVERSE_SPEED = WHEEL_OFF;
}

void Forward_Movement(void) {
  RIGHT_FORWARD_SPEED = RIGHT_FULL_SPEED_F;
  LEFT_FORWARD_SPEED = LEFT_FULL_SPEED_F;
  RIGHT_REVERSE_SPEED = WHEEL_OFF;
  LEFT_REVERSE_SPEED = WHEEL_OFF;
}

void Forward_Movement_Medium(void) {
  RIGHT_FORWARD_SPEED = RIGHT_MED_SPEED_F;
  LEFT_FORWARD_SPEED = LEFT_MED_SPEED_F;
  RIGHT_REVERSE_SPEED = WHEEL_OFF;
  LEFT_REVERSE_SPEED = WHEEL_OFF;
}

void Forward_Movement_Slow(void) {
  RIGHT_FORWARD_SPEED = RIGHT_SLOW_SPEED_F;
  LEFT_FORWARD_SPEED = LEFT_SLOW_SPEED_F;
  RIGHT_REVERSE_SPEED = WHEEL_OFF;
  LEFT_REVERSE_SPEED = WHEEL_OFF;
}

void Reverse_Movement(void) {
  RIGHT_FORWARD_SPEED = WHEEL_OFF;
  LEFT_FORWARD_SPEED = WHEEL_OFF;
  RIGHT_REVERSE_SPEED = RIGHT_FULL_SPEED_R;
  LEFT_REVERSE_SPEED = LEFT_FULL_SPEED_R;
}

void Spin_CW(void) {
  RIGHT_FORWARD_SPEED = WHEEL_OFF;
  LEFT_FORWARD_SPEED = LEFT_MED_SPEED_F;
  RIGHT_REVERSE_SPEED = RIGHT_FULL_SPEED_R;
  LEFT_REVERSE_SPEED = WHEEL_OFF;
}

void Spin_CW_SLOW(void) {
  RIGHT_FORWARD_SPEED = WHEEL_OFF;
  LEFT_FORWARD_SPEED = LEFT_SLOW_SPEED_F;
  RIGHT_REVERSE_SPEED = RIGHT_SLOW_SPEED_R;
  LEFT_REVERSE_SPEED = WHEEL_OFF;
}

void Spin_CCW(void) {
  RIGHT_FORWARD_SPEED = RIGHT_MED_SPEED_F;
  LEFT_FORWARD_SPEED = WHEEL_OFF;
  RIGHT_REVERSE_SPEED = WHEEL_OFF;
  LEFT_REVERSE_SPEED = LEFT_MED_SPEED_R;
}

void Spin_CCW_SLOW(void) {
  RIGHT_FORWARD_SPEED = RIGHT_SLOW_SPEED_F;
  LEFT_FORWARD_SPEED = WHEEL_OFF;
  RIGHT_REVERSE_SPEED = WHEEL_OFF;
  LEFT_REVERSE_SPEED = LEFT_SLOW_SPEED_R;
}

void Turn_R_Five_Degrees(void) {
  
  switch(R_turn_routine) {
    case(RESET_STATE):
      Stop_Movement();
      TB0CCR0 = TB0R + TB0CCR0_INTERVAL;
      Time_Sequence = RESET_STATE;
      R_turn_routine = STATE_1;
      break;
    case(STATE_1):
      if(Time_Sequence >= TEN_MS) {
        Spin_CW();
        R_turn_routine = STATE_2;
      }
      break;
    case(STATE_2):
      if(Time_Sequence >= SIXTY_MS) {
        Stop_Movement();
        R_turn_routine = STATE_3;
      }
      break;
    case(STATE_3):
      if(Time_Sequence >= EIGHTY_MS) {
        R_turn_routine = RESET_STATE;
        done_turning_R = YES;
      }
      break;
    default:
      break;
  }
}

void Turn_L_Five_Degrees(void) {
  
  switch(L_turn_routine) {
    case(RESET_STATE):
      Stop_Movement();
      TB0CCR0 = TB0R + TB0CCR0_INTERVAL;
      Time_Sequence = RESET_STATE;
      L_turn_routine = STATE_1;
      break;
    case(STATE_1):
      if(Time_Sequence >= TEN_MS) {
        Spin_CCW();
        L_turn_routine = STATE_2;
      }
      break;
    case(STATE_2):
      if(Time_Sequence >= THIRTY_MS) {
        Stop_Movement();
        L_turn_routine = STATE_3;
      }
      break;
    case(STATE_3):
      if(Time_Sequence >= FORTY_MS) {
        L_turn_routine = RESET_STATE;
        done_turning_L = YES;
      }
      break;
    default:
      break;
  }
}



