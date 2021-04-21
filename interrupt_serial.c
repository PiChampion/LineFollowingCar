//------------------------------------------------------------------------------
//
//  Description: This file contains Serial Interrupt functions
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

volatile unsigned int usb_rx_ring_wr_UCA0 = RESET_STATE;
volatile unsigned int usb_rx_ring_rd_UCA0 = RESET_STATE;
volatile char USB_Char_Rx_UCA0[SMALL_RING_SIZE];
volatile extern unsigned int UCA0_index;
volatile extern char test_command_UCA0[SMALL_RING_SIZE];
extern char received_string_UCA0[DISPLAY_LINE];
extern char UCA0_transmit_message[PROC_RING_SIZE];

volatile unsigned int usb_rx_ring_wr_UCA1 = RESET_STATE;
volatile unsigned int usb_rx_ring_rd_UCA1 = RESET_STATE;
volatile char USB_Char_Rx_UCA1[SMALL_RING_SIZE];
volatile extern unsigned int UCA1_index;
volatile extern char test_command_UCA1[SMALL_RING_SIZE];
extern char received_string_UCA1[DISPLAY_LINE];
extern char UCA1_transmit_message[PROC_RING_SIZE];

extern volatile unsigned int OK_to_send;

#pragma vector=EUSCI_A0_VECTOR
__interrupt void eUSCI_A0_ISR(void){
//------------------------------------------------------------------------------
// Serial Communication Interrupt handler
//------------------------------------------------------------------------------
  unsigned int temp;
  
  switch(__even_in_range(UCA0IV, 0x08)) {
    case NO_INTERRUPT:                             // Vector 0 - no interrupt
      break;
    case RXIFG_CASE:                             // Vector 2 - RXIFG
      temp = usb_rx_ring_wr_UCA0++;
      USB_Char_Rx_UCA0[temp] = UCA0RXBUF;    // RX --> USB_Char_Rx character
      //UCA0_messaged_received = YES;
      if(usb_rx_ring_wr_UCA0 >= (SMALL_RING_SIZE)) {
        usb_rx_ring_wr_UCA0 = BEGINNING;     // Circular buffer back to beginning
      }
      break;
    case TXIFG_CASE:                             // Vector 4 - TXIFG
      UCA0_index++;
//      if(UCA0_transmit_message[UCA0_index - 1] == NULL) {
//        UCA0TXBUF = LINE_FEED;
//        UCA0IE &= ~UCTXIE;                // Disable TX interrupt
//        UCA0_index = RESET_STATE;
//      }
//      else 
      if(UCA0_transmit_message[UCA0_index] == NULL) {
        UCA0TXBUF = CARRIAGE_RETURN;
        UCA0IE &= ~UCTXIE;                // Disable TX interrupt
        UCA0_index = RESET_STATE;
      }
      else {
        UCA0TXBUF = UCA0_transmit_message[UCA0_index];
      }
      break;  
    default: break;
  }
}
//------------------------------------------------------------------------------

#pragma vector=EUSCI_A1_VECTOR
__interrupt void eUSCI_A1_ISR(void){
//------------------------------------------------------------------------------
// Serial Communication Interrupt handler
//------------------------------------------------------------------------------
  unsigned int temp;
  
  switch(__even_in_range(UCA1IV, 0x08)) {
    case NO_INTERRUPT:                             // Vector 0 - no interrupt
      break;
    case RXIFG_CASE:                             // Vector 2 - RXIFG
      if(!OK_to_send) {
        OK_to_send = YES;
      }
      temp = usb_rx_ring_wr_UCA1++;
      USB_Char_Rx_UCA1[temp] = UCA1RXBUF;    // RX --> USB_Char_Rx character
      //UCA1_messaged_received = YES;
      if(usb_rx_ring_wr_UCA1 >= (sizeof(USB_Char_Rx_UCA1))) {
        usb_rx_ring_wr_UCA1 = BEGINNING;     // Circular buffer back to beginning
      }
      break;
    case TXIFG_CASE:                             // Vector 4 - TXIFG
      UCA1_index++;
      //if(OK_to_send) {
//        if(UCA1_transmit_message[UCA1_index - 1] == NULL) {
//          UCA1TXBUF = LINE_FEED;
//          UCA1IE &= ~UCTXIE;                // Disable TX interrupt
//          UCA1_index = RESET_STATE;
//        }
//        else 
        if(UCA1_transmit_message[UCA1_index] == NULL) {
          UCA1TXBUF = CARRIAGE_RETURN;
          UCA1IE &= ~UCTXIE;                // Disable TX interrupt
          UCA1_index = RESET_STATE;
        }
        else {
          UCA1TXBUF = UCA1_transmit_message[UCA1_index];
        }
        break;
      //}
    default: break;
  }
}
//------------------------------------------------------------------------------







