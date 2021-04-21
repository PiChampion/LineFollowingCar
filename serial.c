//------------------------------------------------------------------------------
//
//  Description: This file contains Serial Communication functions
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

extern volatile unsigned int usb_rx_ring_wr_UCA0;
extern volatile unsigned int usb_rx_ring_rd_UCA0;
unsigned int process_ring_rd_UCA0 = RESET_STATE;
extern volatile char USB_Char_Rx_UCA0[SMALL_RING_SIZE];
char Process_Char_Rx_UCA0[PROC_RING_SIZE];
unsigned int use_process_2 = RESET_STATE;
unsigned int using_secong_buffer = RESET_STATE;

extern volatile unsigned int usb_rx_ring_wr_UCA1;
extern volatile unsigned int usb_rx_ring_rd_UCA1;
unsigned int process_ring_rd_UCA1 = RESET_STATE;
extern volatile char USB_Char_Rx_UCA1[SMALL_RING_SIZE];
char Process_Char_Rx_UCA1[PROC_RING_SIZE];

unsigned volatile int process_the_buffer_1 = RESET_STATE;
unsigned volatile int process_the_buffer_2 = RESET_STATE;
unsigned volatile int UCA1_messaged_received = RESET_STATE;

extern unsigned int transmit_UCA0;
extern unsigned int transmit_UCA1;

char UCA0_transmit_message[PROC_RING_SIZE] = "A1234567I";
char UCA1_transmit_message[PROC_RING_SIZE] = "ABCDEFGHI";
volatile extern unsigned int UCA0_index;
volatile extern unsigned int UCA1_index;

volatile unsigned int OK_to_send = RESET_STATE;
unsigned volatile int transmit_every_second = RESET_STATE;

unsigned int serial_state = RESET_STATE;
unsigned int UCA0_state_0 = RESET_STATE;
unsigned int UCA0_state_1 = RESET_STATE;

unsigned int initialize_port = RESET_STATE;
unsigned int found_ip = RESET_STATE;
volatile unsigned int transmit_delay = RESET_STATE;
unsigned int transmission_state = RESET_STATE;

char Command_Buffer[COMMAND_LINES][COMMAND_CHARS] = {NULL};
unsigned int current_command = RESET_STATE;
unsigned int current_commands = RESET_STATE;
unsigned int next_empty_command = RESET_STATE;
unsigned int command_ring_rd_UCA0 = RESET_STATE;


void Serial_Process(void) {
//------------------------------------------------------------------------------
// Handles serial processes such as receiving and transmitting messages
//------------------------------------------------------------------------------
  unsigned int write_point_UCA0 = usb_rx_ring_wr_UCA0;
  unsigned int read_point_UCA0 = usb_rx_ring_rd_UCA0;
  unsigned int write_point_UCA1 = usb_rx_ring_wr_UCA1;
  unsigned int read_point_UCA1 = usb_rx_ring_rd_UCA1;
  
  int i = RESET_STATE;
  
  if(write_point_UCA1 != read_point_UCA1) {
  }
  
  if(UCA1_messaged_received) {
    UCA1_messaged_received = RESET_STATE;
  }
  
  if(write_point_UCA0 != read_point_UCA0) {
    Process_Char_Rx_UCA0[process_ring_rd_UCA0] = USB_Char_Rx_UCA0[read_point_UCA0];
    usb_rx_ring_rd_UCA0++;
    if(usb_rx_ring_rd_UCA0 >= (SMALL_RING_SIZE)) {
      usb_rx_ring_rd_UCA0 = BEGINNING;     // Circular buffer back to beginning
    }
    UCA1TXBUF = Process_Char_Rx_UCA0[process_ring_rd_UCA0];
    switch(UCA0_state_0) {
      case(RESET_STATE):
        if(Process_Char_Rx_UCA0[process_ring_rd_UCA0] == 'a') {
          UCA0_state_0 = STATE_1;
          Process_Char_Rx_UCA0[process_ring_rd_UCA0] = NULL;
          process_ring_rd_UCA0 = BEGINNING;
        }
        else if(Process_Char_Rx_UCA0[process_ring_rd_UCA0] == 'v') {
          UCA0_state_0 = DISCONNECT_CASE;
          Process_Char_Rx_UCA0[process_ring_rd_UCA0] = NULL;
          process_ring_rd_UCA0 = BEGINNING;
        }
        else if(Process_Char_Rx_UCA0[process_ring_rd_UCA0] == 'C') {
          UCA0_state_0 = RECONNECT_CASE;
          Process_Char_Rx_UCA0[process_ring_rd_UCA0] = NULL;
          process_ring_rd_UCA0 = BEGINNING;
        }
        else if(Process_Char_Rx_UCA0[process_ring_rd_UCA0] == '^') {
          process_ring_rd_UCA0++;
          if(process_ring_rd_UCA0 >= PROC_RING_SIZE) {
            process_ring_rd_UCA0 = BEGINNING;     // Circular buffer back to beginning
          }
          UCA0_state_0 = STATE_6;
        }
        else {
          Process_Char_Rx_UCA0[process_ring_rd_UCA0] = NULL;
          process_ring_rd_UCA0 = BEGINNING;
        }
        break;
      case(RECONNECT_CASE):
        if(Process_Char_Rx_UCA0[process_ring_rd_UCA0] == 'C') {
          for(i = RESET_STATE; i < (UCA0_state_0 + BUFFER_BUFFER); i++) Process_Char_Rx_UCA0[i] = NULL_HEX;
          process_ring_rd_UCA0 = BEGINNING;
          UCA0_state_0 = RESET_STATE;
          strcpy(UCA0_transmit_message, "AT+NSTAT=?");
          transmit_UCA0 = YES;
        }
        else {
          for(i = RESET_STATE; i < (UCA0_state_0 + BUFFER_BUFFER); i++) Process_Char_Rx_UCA0[i] = NULL_HEX;
          process_ring_rd_UCA0 = BEGINNING;
          UCA0_state_0 = RESET_STATE;
        }
          Process_Char_Rx_UCA0[process_ring_rd_UCA0] = NULL;
          process_ring_rd_UCA0 = BEGINNING;
        break;
      case(DISCONNECT_CASE):
        if(Process_Char_Rx_UCA0[process_ring_rd_UCA0] == 'e') {
          for(i = RESET_STATE; i < (UCA0_state_0 + BUFFER_BUFFER); i++) Process_Char_Rx_UCA0[i] = NULL_HEX;
          process_ring_rd_UCA0 = BEGINNING;
          UCA0_state_0 = RESET_STATE;
          set_display_line("DISCONNECT", LINE_TWO);
          set_display_line("DISCONNECT", LINE_THREE);
        }
        else {
          for(i = RESET_STATE; i < (UCA0_state_0 + BUFFER_BUFFER); i++) Process_Char_Rx_UCA0[i] = NULL_HEX;
          process_ring_rd_UCA0 = BEGINNING;
          UCA0_state_0 = RESET_STATE;
        }
          Process_Char_Rx_UCA0[process_ring_rd_UCA0] = NULL;
          process_ring_rd_UCA0 = BEGINNING;
        break;
      case(STATE_1):
        if(Process_Char_Rx_UCA0[process_ring_rd_UCA0] == 'd') {
          UCA0_state_0 = STATE_2;
        }
        else {
          for(i = RESET_STATE; i < (UCA0_state_0 + BUFFER_BUFFER); i++) Process_Char_Rx_UCA0[i] = NULL_HEX;
          process_ring_rd_UCA0 = BEGINNING;
          UCA0_state_0 = RESET_STATE;
        }
          Process_Char_Rx_UCA0[process_ring_rd_UCA0] = NULL;
          process_ring_rd_UCA0 = BEGINNING;
        break;
      case(STATE_2):
        if(Process_Char_Rx_UCA0[process_ring_rd_UCA0] == 'd') {
          UCA0_state_0 = STATE_3;
        }
        else {
          for(i = RESET_STATE; i < (UCA0_state_0 + BUFFER_BUFFER); i++) Process_Char_Rx_UCA0[i] = NULL_HEX;
          process_ring_rd_UCA0 = BEGINNING;
          UCA0_state_0 = RESET_STATE;
        }
        Process_Char_Rx_UCA0[process_ring_rd_UCA0] = NULL;
          process_ring_rd_UCA0 = BEGINNING;
        break;
      case(STATE_3):
        if(Process_Char_Rx_UCA0[process_ring_rd_UCA0] == 'r') {
          UCA0_state_0 = STATE_4;
        }
        else {
          for(i = RESET_STATE; i < (UCA0_state_0 + BUFFER_BUFFER); i++) Process_Char_Rx_UCA0[i] = NULL_HEX;
          process_ring_rd_UCA0 = BEGINNING;
          UCA0_state_0 = RESET_STATE;
        }
          Process_Char_Rx_UCA0[process_ring_rd_UCA0] = NULL;
          process_ring_rd_UCA0 = BEGINNING;
        break;
      case(STATE_4):
        if(Process_Char_Rx_UCA0[process_ring_rd_UCA0] == '=') {
          UCA0_state_0 = STATE_5;
        }
        else {
          for(i = RESET_STATE; i < (UCA0_state_0 + BUFFER_BUFFER); i++) Process_Char_Rx_UCA0[i] = NULL_HEX;
          process_ring_rd_UCA0 = BEGINNING;
          UCA0_state_0 = RESET_STATE;
        }
        Process_Char_Rx_UCA0[process_ring_rd_UCA0] = NULL;
        process_ring_rd_UCA0 = BEGINNING;
        break;
      case(STATE_5):
        if((Process_Char_Rx_UCA0[process_ring_rd_UCA0] == '.') || (Process_Char_Rx_UCA0[process_ring_rd_UCA0] == ' ') || ((Process_Char_Rx_UCA0[process_ring_rd_UCA0] >= '0') && (Process_Char_Rx_UCA0[process_ring_rd_UCA0] <= '9'))) {
          process_ring_rd_UCA0++;
          if(process_ring_rd_UCA0 >= PROC_RING_SIZE) {
            process_ring_rd_UCA0 = BEGINNING;     // Circular buffer back to beginning
          }
        }
        else if(Process_Char_Rx_UCA0[process_ring_rd_UCA0] == 'G') {
          process_the_buffer_1 = YES;
          use_process_2 = YES;
          UCA0_state_0 = RESET_STATE;
          initialize_port = YES;
          found_ip = YES;
        }
        break;
      case(STATE_6):
        if(Process_Char_Rx_UCA0[process_ring_rd_UCA0] == '^') {
          process_the_buffer_1 = YES;
          use_process_2 = YES;
          UCA0_state_0 = RESET_STATE;
          process_ring_rd_UCA0++;
          if(process_ring_rd_UCA0 >= PROC_RING_SIZE) {
            process_ring_rd_UCA0 = BEGINNING;     // Circular buffer back to beginning
          }
        }
        else if(Process_Char_Rx_UCA0[process_ring_rd_UCA0] == '1') {
          UCA0_state_0 = STATE_7;
        
          process_ring_rd_UCA0++;
          if(process_ring_rd_UCA0 >= PROC_RING_SIZE) {
            process_ring_rd_UCA0 = BEGINNING;     // Circular buffer back to beginning
          }
        }
        else {
          for(i = RESET_STATE; i < (UCA0_state_0 + BUFFER_BUFFER); i++) Process_Char_Rx_UCA0[i] = NULL_HEX;
          process_ring_rd_UCA0 = BEGINNING;
          UCA0_state_0 = RESET_STATE;
        }
        break;
      case(STATE_7):
        if(Process_Char_Rx_UCA0[process_ring_rd_UCA0] == '3') {
          UCA0_state_0 = STATE_8;
          process_ring_rd_UCA0++;
          if(process_ring_rd_UCA0 >= PROC_RING_SIZE) {
            process_ring_rd_UCA0 = BEGINNING;     // Circular buffer back to beginning
          }
        }
        else {
          for(i = RESET_STATE; i < (UCA0_state_0 + BUFFER_BUFFER); i++) Process_Char_Rx_UCA0[i] = NULL_HEX;
          process_ring_rd_UCA0 = BEGINNING;
          UCA0_state_0 = RESET_STATE;
        }
        break;
      case(STATE_8):
        if(Process_Char_Rx_UCA0[process_ring_rd_UCA0] == '6') {
          UCA0_state_0 = STATE_9;
          process_ring_rd_UCA0++;
          if(process_ring_rd_UCA0 >= PROC_RING_SIZE) {
            process_ring_rd_UCA0 = BEGINNING;     // Circular buffer back to beginning
          }
        }
        else {
          for(i = RESET_STATE; i < (UCA0_state_0 + BUFFER_BUFFER); i++) Process_Char_Rx_UCA0[i] = NULL_HEX;
          process_ring_rd_UCA0 = BEGINNING;
          UCA0_state_0 = RESET_STATE;
        }
        break;
      case(STATE_9):
        if(Process_Char_Rx_UCA0[process_ring_rd_UCA0] == '8') {
          UCA0_state_0 = STATE_10;
          process_ring_rd_UCA0++;
          if(process_ring_rd_UCA0 >= PROC_RING_SIZE) {
            process_ring_rd_UCA0 = BEGINNING;     // Circular buffer back to beginning
          }
        }
        else {
          for(i = RESET_STATE; i < (UCA0_state_0 + BUFFER_BUFFER); i++) Process_Char_Rx_UCA0[i] = NULL_HEX;
          process_ring_rd_UCA0 = BEGINNING;
          UCA0_state_0 = RESET_STATE;
        }
        break;
      case(STATE_10):
        UCA0_state_0 = STATE_11;
        process_ring_rd_UCA0++;
        if(process_ring_rd_UCA0 >= PROC_RING_SIZE) {
          process_ring_rd_UCA0 = BEGINNING;     // Circular buffer back to beginning
        }
        break;
      case(STATE_11):
        UCA0_state_0 = STATE_12;
        process_ring_rd_UCA0++;
        if(process_ring_rd_UCA0 >= PROC_RING_SIZE) {
          process_ring_rd_UCA0 = BEGINNING;     // Circular buffer back to beginning
        }
        break;
      case(STATE_12):
        UCA0_state_0 = STATE_13;
        process_ring_rd_UCA0++;
        if(process_ring_rd_UCA0 >= PROC_RING_SIZE) {
          process_ring_rd_UCA0 = BEGINNING;     // Circular buffer back to beginning
        }
        break;
      case(STATE_13):
        process_the_buffer_1 = YES;
        use_process_2 = YES;
        UCA0_state_0 = RESET_STATE;
        process_ring_rd_UCA0++;
        if(process_ring_rd_UCA0 >= PROC_RING_SIZE) {
          process_ring_rd_UCA0 = BEGINNING;     // Circular buffer back to beginning
        }
        break;
      default:
        break;
    }
  }
  
  
  if(process_the_buffer_1) {
    if(found_ip) {
      find_ip_address(Process_Char_Rx_UCA0);
      found_ip = RESET_STATE;
    }
    else {
      switch(Process_Char_Rx_UCA0[FIRST_CHAR_RECEIVED]) {
        case('^'):
          switch(Process_Char_Rx_UCA0[PASSWORD_CHAR_1]) {
            case('^'):
              strcpy(UCA1_transmit_message, "\nI'm here");
              transmit_UCA1 = YES;
              break;
            case('F'):
              UCA0BRW = BRW_115200;                               // 115,200 Baud
              UCA0MCTLW = MCTLW_115200;
              set_display_line("  115200  ", LINE_ONE);
              break;
            case('S'):
              UCA0BRW = BRW_9600;                                 // 9,600 Baud
              UCA0MCTLW = MCTLW_9600;
              set_display_line("   9600   ", LINE_ONE);
              break;
            default: 
              if((Process_Char_Rx_UCA0[PASSWORD_CHAR_1] == '1') && (Process_Char_Rx_UCA0[PASSWORD_CHAR_2] == '3') && (Process_Char_Rx_UCA0[PASSWORD_CHAR_3] == '6') && (Process_Char_Rx_UCA0[PASSWORD_CHAR_4] == '8')) {
                if(current_commands < COMMAND_LINES) {
                  Command_Buffer[next_empty_command][COMMAND] = Process_Char_Rx_UCA0[COMMAND_CHAR];
                  Command_Buffer[next_empty_command][COMMAND_VALUE_HUNDRED] = Process_Char_Rx_UCA0[COMMAND_VALUE_1];
                  Command_Buffer[next_empty_command][COMMAND_VALUE_TEN] = Process_Char_Rx_UCA0[COMMAND_VALUE_2];
                  Command_Buffer[next_empty_command][COMMAND_VALUE_ONE] = Process_Char_Rx_UCA0[COMMAND_VALUE_3];
                  next_empty_command++;
                  if(next_empty_command >= COMMAND_LINES) {
                    next_empty_command = BEGINNING;     // Circular buffer back to beginning
                  }
                  current_commands++;
                }
              }
              break;
          }
          break;
        
        default: 
          break;
      }
    }
    process_the_buffer_1 = RESET_STATE;
    for(i = RESET_STATE; i < sizeof(Process_Char_Rx_UCA0); i++) Process_Char_Rx_UCA0[i] = NULL_HEX;
    process_ring_rd_UCA0 = RESET_STATE;
  }
  
  
  if(transmit_UCA0) {
    UCA0TXBUF = UCA0_transmit_message[RESET_STATE];
    UCA0IE |= UCTXIE;                // Enable TX interrupt
    UCA0_index = RESET_STATE;
    transmit_UCA0 = RESET_STATE;
  }
  
  
  if(transmit_UCA1) {
    UCA1TXBUF = UCA1_transmit_message[RESET_STATE];
    UCA1IE |= UCTXIE;                // Enable TX interrupt
    UCA1_index = RESET_STATE;
    transmit_UCA1 = RESET_STATE;
  }

//------------------------------------------------------------------------------
}





