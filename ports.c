//------------------------------------------------------------------------------
//
//  Description: This file initializes ports
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

void Init_Ports(void) {
//------------------------------------------------------------------------------
  Init_Port1();
  Init_Port2();
  Init_Port3(USE_GPIO);
  Init_Port4();
  Init_Port5();
  Init_Port6();
  
}

void Init_Port1(void){
//------------------------------------------------------------------------------
// Configure PORT 1
  P1SEL0 = SET_GPIO;			// Set P1 operation to GPIO
  P1SEL1 = SET_GPIO;			// Set P1 operation to GPIO
  P1DIR = SET_OUTPUTS;                  // Set P1 direction to output
  P1OUT = SET_LOW;                      // P1 set Low
  
// PIN 0
  P1SEL0 &= ~RED_LED;                   // RED_LED GPIO operation
  P1SEL1 &= ~RED_LED;                   // RED_LED GPIO operation
  P1DIR |= RED_LED;                     // Set RED_LED direction to output
  P1OUT &= ~RED_LED;                    // Set RED_LED Off [Low]
  
// PIN 1
  P1SEL0 |= A1_SEEED;                   // A1_SEEED operation
  P1SEL1 |= A1_SEEED;                   // A1_SEEED operation

// PIN 2
  P1SEL0 |= V_DETECT_L;                 // V_DETECT_L operation
  P1SEL1 |= V_DETECT_L;                 // V_DETECT_L operation

// PIN 3
  P1SEL0 |= V_DETECT_R;                 // V_DETECT_R operation
  P1SEL1 |= V_DETECT_R;                 // V_DETECT_R operation

// PIN 4
  P1SEL0 |= A4_SEEED;                   // A4_SEEED operation
  P1SEL1 |= A4_SEEED;                   // A4_SEEED operation

// PIN 5
  P1SEL0 |= V_THUMB;                    // V_THUMB operation
  P1SEL1 |= V_THUMB;                    // V_THUMB operation

// PIN 6
  P1SEL0 |= UCA0RXD;                    // UCA0RXD operation
  P1SEL1 &= ~UCA0RXD;                   // UCA0RXD operation

// PIN 7
  P1SEL0 |= UCA0TXD;                    // UCA0TXD operation
  P1SEL1 &= ~UCA0TXD;                   // UCA0TXD operation
//------------------------------------------------------------------------------  
}

void Init_Port2(void){
//------------------------------------------------------------------------------
// Configure PORT 2
  P2SEL0 = SET_GPIO;			// Set P2 operation to GPIO
  P2SEL1 = SET_GPIO;			// Set P2 operation to GPIO
  P2DIR = SET_OUTPUTS;                  // Set P2 direction to output
  P2OUT = SET_LOW;                      // P2 set Low
  
// PIN 0  
  P2SEL0 &= ~P2_0;                      // P2_0 GPIO operation
  P2SEL1 &= ~P2_0;                      // P2_0 GPIO operation
  P2DIR &= ~P2_0;                       // Direction = input
  
// PIN 1  
  P2SEL0 &= ~P2_1;                      // P2_1 GPIO operation
  P2SEL1 &= ~P2_1;                      // P2_1 GPIO operation
  P2DIR &= ~P2_1;                       // Direction = input
  
// PIN 2  
  P2SEL0 &= ~P2_2;                      // P2_2 GPIO operation
  P2SEL1 &= ~P2_2;                      // P2_2 GPIO operation
  P2DIR &= ~P2_2;                       // Direction = input
  
// PIN 3
  P2SEL0 &= ~SW2;                       // SW2 Operation
  P2SEL1 &= ~SW2;                       // SW2 Operation
  P2DIR &= ~SW2;                        // Direction = input
  P2OUT |= SW2;                         // Configure pullup resistor
  P2REN |= SW2;                         // Enable pullup resistor
  P2IES |= SW2;                         // P2.0 Hi/Lo edge interrupt
  P2IFG &= ~SW2;                        // Clear all P2.6 interrupt flags
  P2IE |= SW2;                          // P2.6 interrupt enabled
  
// PIN 4  
  P2SEL0 &= ~P2_4;                      // P2_4 GPIO operation
  P2SEL1 &= ~P2_4;                      // P2_4 GPIO operation
  P2DIR &= ~P2_4;                       // Direction = input
  
// PIN 5  
  P2SEL0 &= ~P2_5;                      // P2_5 GPIO operation
  P2SEL1 &= ~P2_5;                      // P2_5 GPIO operation
  P2DIR &= ~P2_5;                       // Direction = input
  
// PIN 6  
  P2SEL0 &= ~LFXOUT;                    // LFXOUT Clock operation
  P2SEL1 |= LFXOUT;                     // LFXOUT Clock operation
  
// PIN 7  
  P2SEL0 &= ~LFXIN;                     // LFXIN Clock operation
  P2SEL1 |= LFXIN;                      // LFXIN Clock operation
//------------------------------------------------------------------------------
}

void Init_Port3(char MODE){
//------------------------------------------------------------------------------
// Configure PORT 3
  P3SEL0 = SET_GPIO;			// Set P3 operation to GPIO
  P3SEL1 = SET_GPIO;			// Set P3 operation to GPIO
  P3DIR = SET_OUTPUTS;                  // Set P3 direction to output
  P3OUT = SET_LOW;                      // P3 set Low

// PIN 0
  P3SEL0 &= ~TEST_PROBE;                // TEST_PROBE GPIO Operation
  P3SEL1 &= ~TEST_PROBE;                // TEST_PROBE GPIO Operation
  P3DIR |= TEST_PROBE;                  // Direction = input
  P3OUT &= ~TEST_PROBE;
  
// PIN 1
  P3SEL0 |= CHECK_BAT;                  // CHECK_BAT Operation
  P3SEL1 |= CHECK_BAT;                  // CHECK_BAT Operation

// PIN 2
  P3SEL0 |= OA2N;                       // OA2N Operation
  P3SEL1 |= OA2N;                       // OA2N Operation

// PIN 3
  P3SEL0 |= OA2P;                       // OA2P Operation
  P3SEL1 |= OA2P;                       // OA2P Operation

// PIN 4
  if(MODE == USE_GPIO) {
    P3SEL0 &= ~P3_4;                    // P3_4 GPIO Operation
    P3SEL1 &= ~P3_4;                    // P3_4 GPIO Operation
    P3DIR &= ~P3_4;                     // Direction = input
  }
  else if(MODE == USE_SMCLK) {
    P3SEL0 |= SMCLK_OUT;                // SMCLK_OUT Operation
    P3SEL1 &= ~SMCLK_OUT;               // SMCLK_OUT Operation
    P3DIR |= SMCLK_OUT;                 // SMCLK_OUT Operation
  }

// PIN 5
  P3SEL0 &= ~IR_LED;                    // IR_LED GPIO Operation
  P3SEL1 &= ~IR_LED;                    // IR_LED GPIO Operation
  P3DIR |= IR_LED;                      // Direction = output
  P3OUT &= ~IR_LED;                     // Set IR_LED Off [Low]

// PIN 6
  P3SEL0 &= ~IOT_LINK;                  // IOT_LINK GPIO Operation
  P3SEL1 &= ~IOT_LINK;                  // IOT_LINK GPIO Operation
  P3DIR &= ~IOT_LINK;                   // Direction = input
  P3OUT &= ~IOT_LINK;                   // Condition = 0

// PIN 7
  P3SEL0 &= ~P3_7;                      // P3_7 GPIO Operation
  P3SEL1 &= ~P3_7;                      // P3_7 GPIO Operation
  P3DIR &= ~P3_7;                       // Direction = input  
//------------------------------------------------------------------------------  
}

void Init_Port4(void){
//------------------------------------------------------------------------------
// Configure PORT 4
  P4SEL0 = SET_GPIO;			// Set P4 operation to GPIO
  P4SEL1 = SET_GPIO;			// Set P4 operation to GPIO  
  P4DIR = SET_OUTPUTS;                  // Set P4 direction to output
  P4OUT = SET_LOW;                      // P4 set Low

// PIN 0  
  P4SEL0 &= ~RESET_LCD;                 // RESET_LCD GPIO operation
  P4SEL1 &= ~RESET_LCD;                 // RESET_LCD GPIO operation
  P4DIR |= RESET_LCD;                   // Set RESET_LCD direction to output
  P4OUT |= RESET_LCD;                   // Set RESET_LCD Off [High]

// PIN 1  
  P4SEL0 &= ~SW1;                       // SW1 GPIO operation
  P4SEL1 &= ~SW1;                       // SW1 GPIO operation
  P4DIR &= ~SW1;                        // Direction = input
  P4OUT |= SW1;                         // Configure pullup resistor
  P4REN |= SW1;                         // Enable pullup resistor
  P4IES |= SW1;                      // P2.0 Hi/Lo edge interrupt
  P4IFG &= ~SW1;                     // Clear all P2.6 interrupt flags
  P4IE |= SW1;                       // P2.6 interrupt enabled

// PIN 2  
  P4SEL0 |= UCA1TXD;                    // USCI_A1 UART operation
  P4SEL1 &= ~UCA1TXD;                   // USCI_A1 UART operation

// PIN 3  
  P4SEL0 |= UCA1RXD;                    // USCI_A1 UART operation
  P4SEL1 &= ~UCA1RXD;                   // USCI_A1 UART operation

// PIN 4  
  P4SEL0 &= ~UCB1_CS_LCD;               // UCB1_CS_LCD GPIO operation
  P4SEL1 &= ~UCB1_CS_LCD;               // UCB1_CS_LCD GPIO operation
  P4DIR |= UCB1_CS_LCD;                 // Set SPI_CS_LCD direction to output
  P4OUT |= UCB1_CS_LCD;                 // Set SPI_CS_LCD Off [High]

// PIN 5  
  P4SEL0 |= UCB1CLK;                    // UCB1CLK SPI BUS operation
  P4SEL1 &= ~UCB1CLK;                   // UCB1CLK SPI BUS operation

// PIN 6  
  P4SEL0 |= UCB1SIMO;                   // UCB1SIMO SPI BUS operation
  P4SEL1 &= ~UCB1SIMO;                  // UCB1SIMO SPI BUS operation

// PIN 7  
  P4SEL0 |= UCB1SOMI;                   // UCB1SOMI SPI BUS operation
  P4SEL1 &= ~UCB1SOMI;                  // UCB1SOMI SPI BUS operation
//------------------------------------------------------------------------------  
}

void Init_Port5(void){
//------------------------------------------------------------------------------
// Configure PORT 5
  P5SEL0 = SET_GPIO;			// Set P5 operation to GPIO
  P5SEL1 = SET_GPIO;			// Set P5 operation to GPIO
  P5DIR = SET_INPUTS;                   // Set P5 direction to input
  P5OUT = SET_LOW;                      // P5 set Low

// PIN 0
  P5SEL0 &= ~IOT_RESET;                 // IOT_RESET GPIO operation
  P5SEL1 &= ~IOT_RESET;                 // IOT_RESET GPIO operation
  P5DIR |= IOT_RESET;                   // Direction = output
  P5OUT &= ~IOT_RESET;                  // Set IOT_RESET Off [Low]

// PIN 1
  P5SEL0 &= ~V_BAT;                     // V_BAT GPIO operation
  P5SEL1 &= ~V_BAT;                     // V_BAT GPIO operation
  P5DIR &= ~V_BAT;                      // Direction = input
  // P5OUT &= ~V_BAT;                      // Set V_BAT Off [Low]  

// PIN 2
  P5SEL0 &= ~IOT_PROG_SEL;              // IOT_PROG_SEL GPIO operation
  P5SEL1 &= ~IOT_PROG_SEL;              // IOT_PROG_SEL GPIO operation
  P5DIR &= ~IOT_PROG_SEL;               // Direction = input
  // P5OUT &= ~IOT_PROG_SEL;               // Set IOT_PROG_SEL Off [Low]

// PIN 3
  P5SEL0 &= ~V_3_3;                     // V_3_3 GPIO operation
  P5SEL1 &= ~V_3_3;                     // V_3_3 GPIO operation
  P5DIR &= ~V_3_3;                      // Direction = input
  // P5OUT &= ~V_3_3;                      // Set V_3_3 Off [Low]

// PIN 4
  P5SEL0 &= ~IOT_PROG_MODE;             // IOT_PROG_MODE GPIO operation
  P5SEL1 &= ~IOT_PROG_MODE;             // IOT_PROG_MODE GPIO operation
  P5DIR &= ~IOT_PROG_MODE;              // Direction = input
  // P5OUT &= ~IOT_PROG_MODE;              // Set IOT_PROG_MODE Off [Low]
//------------------------------------------------------------------------------  
}

void Init_Port6(void){
//------------------------------------------------------------------------------
// Configure PORT 6
  P6SEL0 = SET_GPIO;			// Set P6 operation to GPIO
  P6SEL1 = SET_GPIO;			// Set P6 operation to GPIO  
  P6DIR = SET_OUTPUTS;                  // Set P6 direction to output
  P6OUT = SET_LOW;                      // P6 set Low

// PIN 0
  P6SEL0 |= R_FORWARD;                  // R_FORWARD PWM operation
  P6SEL1 &= ~R_FORWARD;                 // R_FORWARD PWM operation
  P6DIR |= R_FORWARD;                   // Set R_FORWARD direction to output

// PIN 1
  P6SEL0 |= L_FORWARD;                  // L_FORWARD PWM operation
  P6SEL1 &= ~L_FORWARD;                 // L_FORWARD PWM operation
  P6DIR |= L_FORWARD;                   // Set L_FORWARD direction to output

// PIN 2
  P6SEL0 |= R_REVERSE;                  // R_REVERSE PWM operation
  P6SEL1 &= ~R_REVERSE;                 // R_REVERSE PWM operation
  P6DIR |= R_REVERSE;                   // Set R_REVERSE direction to output

// PIN 3
  P6SEL0 |= L_REVERSE;                  // L_REVERSE PWM operation
  P6SEL1 &= ~L_REVERSE;                 // L_REVERSE PWM operation
  P6DIR |= L_REVERSE;                   // Set L_REVERSE direction to output

// PIN 4
  P6SEL0 &= ~LCD_BACKLITE;              // LCD_BACKLITE GPIO operation
  P6SEL1 &= ~LCD_BACKLITE;              // LCD_BACKLITE GPIO operation
  P6DIR |= LCD_BACKLITE;                // Set LCD_BACKLITE direction to output
  P6OUT |= LCD_BACKLITE;                // Set LCD_BACKLITE On [High]

// PIN 5
  P6SEL0 &= ~P6_5;                      // P6_5 GPIO operation
  P6SEL1 &= ~P6_5;                      // P6_5 GPIO operation
  P6DIR &= ~P6_5;                       // Direction = input

// PIN 6
  P6SEL0 &= ~GRN_LED;                   // GRN_LED GPIO operation
  P6SEL1 &= ~GRN_LED;                   // GRN_LED GPIO operation
  P6DIR |= GRN_LED;                     // Set GRN_LED direction to output
  P6OUT &= ~GRN_LED;                    // Set GRN_LED Off [Low]
//------------------------------------------------------------------------------
}



