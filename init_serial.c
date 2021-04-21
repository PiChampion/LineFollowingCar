//------------------------------------------------------------------------------
//
//  Description: This file initializes the Serial Communications
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
extern volatile char USB_Char_Rx_UCA0[SMALL_RING_SIZE];

extern volatile unsigned int usb_rx_ring_wr_UCA1;
extern volatile unsigned int usb_rx_ring_rd_UCA1;
extern volatile char USB_Char_Rx_UCA1[SMALL_RING_SIZE];

volatile extern char test_command_UCA0[SMALL_RING_SIZE];
volatile extern char test_command_UCA1[SMALL_RING_SIZE];

volatile unsigned int UCA0_index;
volatile unsigned int UCA1_index;

unsigned int baudrate = BAUD_115200;

void Init_Serial_UCA0(unsigned int baud){
//------------------------------------------------------------------------------
// Initializes Serial Port UCA0
//------------------------------------------------------------------------------
  int i;
  for(i = RESET_STATE; i < SMALL_RING_SIZE; i++) {
    USB_Char_Rx_UCA0[i] = NULL_HEX;              // USB Rx Buffer
  }
  usb_rx_ring_wr_UCA0 = BEGINNING;
  usb_rx_ring_rd_UCA0 = BEGINNING;

  // Configure UART 0
  UCA0CTLW0 = RESET_STATE;              // Use word register
  UCA0CTLW0 |= UCSWRST;                 // Set Software reset enable
  UCA0CTLW0 |= UCSSEL__SMCLK;           // Set SMCLK as fBRCLK

  switch(baud) {
    case(BAUD_115200):
    // 115,200 Baud Rate
    // 1. Calculate N = fBRCLK / Baudrate
    //      N = SMCLK / 115,200 => 8,000,000 / 115,200 = 69.4444444
    // if N > 16 continue with step 3, otherwise with step 2
    // 2. OS16 = 0, UCBRx = INT(N)
    //  continue with step 4
    // 3. OS16 = 1,
    //      UCx     = INT(N/16),
    //              = INT(N/16) = 69.4444444/16 => 4
    //      UCFx    = INT([(N/16) - INT(N/16)]×16)
    //              = ([69.4444444/16 - INT(69.4444444/16)]*16)
    //              = (4.340277778 - 4)*16
    //              = 0.340277778*16 = 5
    // 4. UCSx is found by looking up the fractional part of N (= N-INT(N)) in table Table 18-4
    //      Decimal of SMCLK / 8,000,000 / 115,200 = 69.4444444 => 0.444 yields 0x55 [Table]
    // 5. If OS16 = 0 was chosen, a detailed error calculation is recommended to be performed
    //                                                      TX error (%)    RX error (%)
    // BRCLK      Baudrate  UCOS16  UCBRx   UCFx    UCSx    neg     pos     neg     pos
    // 8000000    115,200   1       4       5       0x55    ?       ?       ?       ?
      UCA0BRW = BRW_115200;                          // 115,200 Baud
    // UCA0MCTLW = UCSx concatenate UCFx    concatenate UCOS16;
    // UCA0MCTLW = 0x55 concatenate 5       concatenate 1;
      UCA0MCTLW = MCTLW_115200;
      UCA0CTLW0 &= ~UCSWRST;                // Set Software reset enable
      UCA0IE |= UCRXIE;                     // Enable RX interrupt
      break;
    case(BAUD_460800):
    // 460,800 Baud Rate
    // 1. Calculate N = fBRCLK / Baudrate
    //      N = SMCLK / 460,800 => 8,000,000 / 460,800 = 17.36111
    // if N > 16 continue with step 3, otherwise with step 2
    // 2. OS16 = 0, UCBRx = INT(N)
    //  continue with step 4
    // 3. OS16 = 1,
    //      UCx     = INT(N/16),
    //              = INT(N/16) = 17.36111/16 => 1
    //      UCFx    = INT([(N/16) - INT(N/16)]×16)
    //              = ([17.36111/16 - INT(17.36111/16)]*16)
    //              = (1.08507 - 1)*16
    //              = 0.08507*16 = 1
    // 4. UCSx is found by looking up the fractional part of N (= N-INT(N)) in table Table 18-4
    //      Decimal of SMCLK / 8,000,000 / 460,800 = 17.36111 => 0.36111 yields 0x4A [Table]
    // 5. If OS16 = 0 was chosen, a detailed error calculation is recommended to be performed
    //                                                      TX error (%)    RX error (%)
    // BRCLK      Baudrate  UCOS16  UCBRx   UCFx    UCSx    neg     pos     neg     pos
    // 8000000    460,800   1       1       1       0x4A    ?       ?       ?       ?
      UCA0BRW = BRW_460800;                         // 460,800 Baud
    // UCA0MCTLW = UCSx concatenate UCFx    concatenate UCOS16;
    // UCA0MCTLW = 0x4A concatenate 1       concatenate 1;
      UCA0MCTLW = MCTLW_460800;
      UCA0CTLW0 &= ~UCSWRST;                // Set Software reset enable
      UCA0IE |= UCRXIE;                     // Enable RX interrupt
      break;
    default:
      break;
  }
  UCA0IFG &= ~UCTXIFG; 
  UCA0_index = RESET_STATE;
  UCA0IE |= UCRXIE;
}

void Init_Serial_UCA1(unsigned int baud){
//------------------------------------------------------------------------------
// Initializes Serial Port UCA1
//------------------------------------------------------------------------------
  int i;
  for(i = RESET_STATE; i < SMALL_RING_SIZE; i++) {
    USB_Char_Rx_UCA1[i] = NULL_HEX;              // USB Rx Buffer
  }
  usb_rx_ring_wr_UCA1 = BEGINNING;
  usb_rx_ring_rd_UCA1 = BEGINNING;

  // Configure UART 1
  UCA1CTLW0 = RESET_STATE;                        // Use word register
  UCA1CTLW0 |= UCSWRST;                 // Set Software reset enable
  UCA1CTLW0 |= UCSSEL__SMCLK;           // Set SMCLK as fBRCLK

  switch(baud) {
    case(BAUD_115200):
    // 115,200 Baud Rate
    // 1. Calculate N = fBRCLK / Baudrate
    //      N = SMCLK / 115,200 => 8,000,000 / 115,200 = 69.4444444
    // if N > 16 continue with step 3, otherwise with step 2
    // 2. OS16 = 0, UCBRx = INT(N)
    //  continue with step 4
    // 3. OS16 = 1,
    //      UCx     = INT(N/16),
    //              = INT(N/16) = 69.4444444/16 => 4
    //      UCFx    = INT([(N/16) - INT(N/16)]×16)
    //              = ([69.4444444/16 - INT(69.4444444/16)]*16)
    //              = (4.340277778 - 4)*16
    //              = 0.340277778*16 = 5
    // 4. UCSx is found by looking up the fractional part of N (= N-INT(N)) in table Table 18-4
    //      Decimal of SMCLK / 8,000,000 / 115,200 = 69.4444444 => 0.444 yields 0x55 [Table]
    // 5. If OS16 = 0 was chosen, a detailed error calculation is recommended to be performed
    //                                                      TX error (%)    RX error (%)
    // BRCLK      Baudrate  UCOS16  UCBRx   UCFx    UCSx    neg     pos     neg     pos
    // 8000000    115,200   1       4       5       0x55    ?       ?       ?       ?
      UCA1BRW = BRW_115200;                         // 115,200 Baud
    // UCA0MCTLW = UCSx concatenate UCFx    concatenate UCOS16;
    // UCA0MCTLW = 0x55 concatenate 5       concatenate 1;
      UCA1MCTLW = MCTLW_115200;
      UCA1CTLW0 &= ~UCSWRST;                // Set Software reset enable
      UCA1IE |= UCRXIE;                     // Enable RX interrupt
      break;
    case(BAUD_460800):
    // 460,800 Baud Rate
    // 1. Calculate N = fBRCLK / Baudrate
    //      N = SMCLK / 460,800 => 8,000,000 / 460,800 = 17.36111
    // if N > 16 continue with step 3, otherwise with step 2
    // 2. OS16 = 0, UCBRx = INT(N)
    //  continue with step 4
    // 3. OS16 = 1,
    //      UCx     = INT(N/16),
    //              = INT(N/16) = 17.36111/16 => 1
    //      UCFx    = INT([(N/16) - INT(N/16)]×16)
    //              = ([17.36111/16 - INT(17.36111/16)]*16)
    //              = (1.08507 - 1)*16
    //              = 0.08507*16 = 1
    // 4. UCSx is found by looking up the fractional part of N (= N-INT(N)) in table Table 18-4
    //      Decimal of SMCLK / 8,000,000 / 460,800 = 17.36111 => 0.36111 yields 0x4A [Table]
    // 5. If OS16 = 0 was chosen, a detailed error calculation is recommended to be performed
    //                                                      TX error (%)    RX error (%)
    // BRCLK      Baudrate  UCOS16  UCBRx   UCFx    UCSx    neg     pos     neg     pos
    // 8000000    460,800   1       1       1       0x4A    ?       ?       ?       ?
      UCA1BRW = BRW_460800;                         // 460,800 Baud
    // UCA0MCTLW = UCSx concatenate UCFx    concatenate UCOS16;
    // UCA0MCTLW = 0x4A concatenate 1       concatenate 1;
      UCA1MCTLW = MCTLW_460800;
      UCA1CTLW0 &= ~UCSWRST;                // Set Software reset enable
      UCA1IE |= UCRXIE;                     // Enable RX interrupt
      break;
    default:
      break;
  }
  UCA1IFG &= ~UCTXIFG; 
  UCA1_index = RESET_STATE;
  UCA1IE |= UCRXIE;
}