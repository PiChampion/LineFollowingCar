//------------------------------------------------------------------------------
//
//  Description: This file contains port interrupt configurations
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

extern unsigned volatile int ADC_update_1;
extern unsigned volatile int ADC_update_2;
extern unsigned volatile int ADC_update_3;
extern unsigned volatile int ADC_update_1_en;
extern unsigned volatile int ADC_update_2_en;
extern unsigned volatile int ADC_update_3_en;
unsigned volatile int SW1_pressed;
unsigned volatile int debouncing_SW1;
unsigned volatile int SW2_pressed;
unsigned volatile int debouncing_SW2;
unsigned volatile int debounce_count;
unsigned volatile int ADC_Channel;
unsigned volatile int ADC_Left_Detect;
unsigned volatile int ADC_Right_Detect;
unsigned volatile int ADC_Thumb;
extern volatile char test_command_UCA0[SMALL_RING_SIZE];
extern volatile char test_command_UCA1[SMALL_RING_SIZE];
unsigned int transmit_UCA0 = RESET_STATE;
unsigned int transmit_UCA1 = RESET_STATE;
extern char UCA0_transmit_message[32];
extern char UCA1_transmit_message[32];
extern unsigned int menu;

// Port 4 interrupt. Triggered by pressing switch 1.
#pragma vector=PORT4_VECTOR
__interrupt void switch1_interrupt (void) {
//------------------------------------------------------------------------------
// Switch 1 Interrupt handler
//      Clears any interrupt flags for this interrupt and enables the timer 
//      interrupt which controls the debouncing state machine responsible for 
//      debouncing the switch. Also sends command to the IOT module to receive
//      connection information.
// Uses global variables SW1_pressed, debouncing_SW1, debounce_count,
//                       UCA0_transmit_message, and transmit_UCA0.
//------------------------------------------------------------------------------
  if (P4IFG & SW1) {
    P4IFG &= ~SW1;                      // IFG SW1 cleared
    P4IE &= ~SW1;                       // Disable the Switch Interrupt.
    SW1_pressed = YES;
    debouncing_SW1 = YES;
    debounce_count = RESET_STATE;       // Reset the count required of the debounce.
    TB0CCTL1 |= CCIE;                   // CCR1 enable interrupt
    TB0CCTL2 |= CCIE;                   // CCR2 enable interrupt
   
    strcpy(UCA0_transmit_message, "AT+NSTAT=?");
    transmit_UCA0 = YES;
  }
}

//------------------------------------------------------------------------------

// Port 2 interrupt. Triggered by pressing switch 2.
#pragma vector=PORT2_VECTOR
__interrupt void switch2_interrupt (void) {
//------------------------------------------------------------------------------
// Switch 2 Interrupt handler
//      Clears any interrupt flags for this interrupt and enables the timer 
//      interrupt which controls the debouncing state machine responsible for 
//      debouncing the switch. Also changes the state of the IR LED.
// Uses global variables SW2_pressed, debouncing_SW2, debounce_count.
//------------------------------------------------------------------------------
  if (P2IFG & SW2) {
    P2IFG &= ~SW2;                      // IFG SW2 cleared
    P2IE &= ~SW2;                       // Disable the Switch Interrupt.
    SW2_pressed = YES;
    debouncing_SW2 = YES;
    debounce_count = RESET_STATE;       // Reset the count required of the debounce.
    TB0CCTL1 |= CCIE;                   // CCR1 enable interrupt

    if(P3OUT & IR_LED) {
      P3OUT &= ~IR_LED;                 // Set IR_LED Off [Low]
      set_display_line("IR_LED OFF", LINE_ONE);
    }
    else {
      P3OUT |= IR_LED;                  // Set IR_LED On [High]
      set_display_line("IR_LED ON ", LINE_ONE);
    }
  }
}

//------------------------------------------------------------------------------

#pragma vector=ADC_VECTOR
__interrupt void ADC_ISR(void){
//------------------------------------------------------------------------------
// ADC Interrupt handler
//------------------------------------------------------------------------------
  switch(__even_in_range(ADCIV,ADCIV_ADCIFG)){
    case ADCIV_NONE:
      break;
    case ADCIV_ADCOVIFG:        // When a conversion result is written to the ADCMEM0
                                // before its previous conversion result was read.
      break;
    case ADCIV_ADCTOVIFG:       // ADC conversion-time overflow
      break;
    case ADCIV_ADCHIIFG:        // Window comparator interrupt flags
      break;
    case ADCIV_ADCLOIFG:        // Window comparator interrupt flag
      break;
    case ADCIV_ADCINIFG:        // Window comparator interrupt flag
      break;
    case ADCIV_ADCIFG:          // ADCMEM0 memory register with the conversion result
      ADCCTL0 &= ~ADCENC;       // Disable ENC bit.
      switch (ADC_Channel++){
        case A2:                                                // Channel A2 Interrupt
          ADCMCTL0 &= ~ADCINCH_2;                               // Disable Last channel A2
          ADCMCTL0 |= ADCINCH_3;                                // Enable Next channel A3
          ADC_Left_Detect = ADCMEM0;                            // Move result into Global
          ADC_Left_Detect = ADC_Left_Detect >> DIVIDE_4;        // Divide the result by 4
       //   ADC_update_1_en = YES;
          break;
        case A3:                                                // Channel A3 Interrupt
          ADCMCTL0 &= ~ADCINCH_3;                               // Disable Last channel A3
          ADCMCTL0 |= ADCINCH_5;                                // Enable Next channel A5
          ADC_Right_Detect = ADCMEM0;                           // Move result into Global
          ADC_Right_Detect = ADC_Right_Detect >> DIVIDE_4;      // Divide the result by 4
       //   ADC_update_2_en = YES;
          break;
        case A5:                                                // Channel A5 Interrupt
          ADCMCTL0 &= ~ADCINCH_5;                               // Disable Last channel A5
          ADCMCTL0 |= ADCINCH_2;                                // Enable Next channel A3
          ADC_Thumb = ADCMEM0;                                  // Move result into Global
          ADC_Thumb = ADC_Thumb >> DIVIDE_4;                    // Divide the result by 4
       //   ADC_update_3_en = YES;
          ADC_Channel = RESET_STATE;                            // Reset State Machine
          break;
        default:
          break;
      }
      ADCCTL0 |= ADCENC;                                        // Enable Conversions
      ADCCTL0 |= ADCSC;                                         // Start next sample
      break;
    default:
      break;
  }  
}
//------------------------------------------------------------------------------

