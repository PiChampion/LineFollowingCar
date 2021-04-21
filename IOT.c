//------------------------------------------------------------------------------
//
//  Description: This file contains IOT functions
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

unsigned int change_IOT_reset = RESET_STATE;
unsigned int IOT_reset_changed = RESET_STATE;
extern unsigned int initialize_port;

char ip_line3[DISPLAY_LINE] = "  1.xxx   ";

char subnet_line1[DISPLAY_LINE] = "xxxxxxxxxx";

extern char UCA0_transmit_message[PROC_RING_SIZE];
extern unsigned int transmit_UCA0;


void IOT_Process(void) {
//------------------------------------------------------------------------------
// Controls IOT reset process and sends a command to the IOT to initialize port
// 3141 when requested.
//------------------------------------------------------------------------------
  if(!IOT_reset_changed && (change_IOT_reset > ONE_SECOND_RESET)) {
    P5OUT |= IOT_RESET;                  // Set IOT_RESET Off [Low]
    IOT_reset_changed = YES;
  }
  
  if(initialize_port) {
    strcpy(UCA0_transmit_message, "AT+NSTCP=3141,1");
    transmit_UCA0 = YES;
    initialize_port = RESET_STATE;
  }
//------------------------------------------------------------------------------ 
}

void find_ip_address(char string[PROC_RING_SIZE]) {
//------------------------------------------------------------------------------
// Displays the IP address of the device given a string.
//------------------------------------------------------------------------------
  ip_line3[IP_NUM_1] = string[IP_NUM_1_STRING];
  ip_line3[IP_NUM_2] = string[IP_NUM_2_STRING];
  ip_line3[IP_NUM_3] = string[IP_NUM_3_STRING];
  
  set_display_line(" 192.168  ", LINE_TWO);
  set_display_line(ip_line3, LINE_THREE);
  
  //find_subnet(string);
//------------------------------------------------------------------------------
}

void find_subnet(char string[PROC_RING_SIZE]) {
//------------------------------------------------------------------------------
// Displays the subnet of the device given a string.
//------------------------------------------------------------------------------
  subnet_line1[SUBNET_NUM_0] = string[SUBNET_NUM_0_STRING];
  subnet_line1[SUBNET_NUM_1] = string[SUBNET_NUM_1_STRING];
  subnet_line1[SUBNET_NUM_2] = string[SUBNET_NUM_2_STRING];
  subnet_line1[SUBNET_NUM_3] = string[SUBNET_NUM_3_STRING];
  subnet_line1[SUBNET_NUM_4] = string[SUBNET_NUM_4_STRING];
  subnet_line1[SUBNET_NUM_5] = string[SUBNET_NUM_5_STRING];
  subnet_line1[SUBNET_NUM_6] = string[SUBNET_NUM_6_STRING];
  subnet_line1[SUBNET_NUM_7] = string[SUBNET_NUM_7_STRING];
  subnet_line1[SUBNET_NUM_8] = string[SUBNET_NUM_8_STRING];
  subnet_line1[SUBNET_NUM_9] = string[SUBNET_NUM_9_STRING];
  
  set_display_line(subnet_line1, LINE_ONE);
//------------------------------------------------------------------------------
}

