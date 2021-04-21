//------------------------------------------------------------------------------
//
//  Description: This file contains timer interrupt configuration
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

extern unsigned volatile int SW1_pressed;
extern unsigned volatile int debouncing_SW1;
extern unsigned volatile int SW2_pressed;
extern unsigned volatile int debouncing_SW2;
extern volatile int backlight_state;
extern volatile int backlight_state_1;
extern unsigned volatile int ADC_update_1;
extern unsigned volatile int ADC_update_2;
extern unsigned volatile int ADC_update_3;
extern unsigned volatile int ADC_update_1_en;
extern unsigned volatile int ADC_update_2_en;
extern unsigned volatile int ADC_update_3_en;
extern unsigned int change_IOT_reset;
extern unsigned volatile int debounce_count;
unsigned volatile int display_state = RESET_STATE;
volatile unsigned int Time_Sequence;
extern unsigned volatile int movement_state;
volatile unsigned int startup_counter = RESET_STATE;
extern volatile unsigned int transmit_every_second;
extern volatile unsigned int transmit_delay;
unsigned volatile int movement_time = RESET_STATE;


#pragma vector=TIMER0_B0_VECTOR
__interrupt void Timer0_B0_ISR(void) {
//------------------------------------------------------------------------------
// TimerB0 0 Interrupt handler
// Increments a backlight updating state machine at intervals of 5 ms.
//------------------------------------------------------------------------------
  backlight_state++;                            // Increment Backlight State
  display_state++;                              // Increment Display State
  Time_Sequence++;                              // Increment Time_Sequence
  ADC_update_1++;
  ADC_update_2++;
  ADC_update_3++;
  change_IOT_reset++;
  startup_counter++;
  transmit_delay++;
  transmit_every_second++;
  movement_time++;
  if(Time_Sequence > TIME_SEQ_MAX) Time_Sequence = RESET_STATE;
  TB0CCR0 += TB0CCR0_INTERVAL;                  // Add Offset to TBCCR0
//------------------------------------------------------------------------------
}

 #pragma vector=TIMER0_B1_VECTOR
 __interrupt void TIMER0_B1_ISR(void) {
 //------------------------------------------------------------------------------
 // TimerB0 1 2, Overflow Interrupt Vector (TBIV ) handler
 //------------------------------------------------------------------------------
   switch(__even_in_range(TB0IV,14)) {
     case CCR0_CASE: break; // No interrupt
//------------------------------------------------------------------------------
// TimerB0 1 Interrupt handler
// Increments a debouncing state machine at intervals of 100 ms.
//------------------------------------------------------------------------------
     case CCR1_CASE:
       debounce_count++;                        // Increment Debounce Count
       TB0CCR1 += TB0CCR1_INTERVAL;             // Add Offset to TBCCR1
       if(debounce_count > DEBOUNCE_TIME) {
          P4IFG &= ~SW1;                      // IFG SW1 cleared
          P2IFG &= ~SW2;                      // IFG SW2 cleared
          debouncing_SW1 = RESET_STATE;
          SW1_pressed = RESET_STATE;
          debouncing_SW2 = RESET_STATE;
          SW2_pressed = RESET_STATE;
          P4IE |= SW1;
          P2IE |= SW2;  
          //TB0CCTL0 |= CCIE;                     // CCR0 enable interrupt
          TB0CCTL1 &= ~CCIE;                    // CCR1 disable interrupt
          debounce_count = RESET_STATE;
        }
       break;
//------------------------------------------------------------------------------
// TimerB0 2 Interrupt handler
// Increments a display updating state machine at intervals of 100 ms.
//------------------------------------------------------------------------------
     case CCR2_CASE:
       movement_state++;                        // Increment Movement State
       TB0CCR2 += TB0CCR2_INTERVAL;             // Add Offset to TBCCR2
       break;
     case OVERFLOW_CASE: // overflow
       break;
     default: break;
 }
 //------------------------------------------------------------------------------
 }

#pragma vector=TIMER1_B0_VECTOR
__interrupt void Timer1_B0_ISR(void) {
//------------------------------------------------------------------------------
// TimerB1 0 Interrupt handler
//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
}

 #pragma vector=TIMER1_B1_VECTOR
 __interrupt void TIMER1_B1_ISR(void) {
 //------------------------------------------------------------------------------
 // TimerB1 1 2, Overflow Interrupt Vector (TBIV ) handler
 //------------------------------------------------------------------------------
   switch(__even_in_range(TB0IV,14)) {
     case CCR0_CASE: break; // No interrupt
//------------------------------------------------------------------------------
// TimerB0 1 Interrupt handler
//------------------------------------------------------------------------------
     case CCR1_CASE:
       
       break;
//------------------------------------------------------------------------------
// TimerB0 2 Interrupt handler
//------------------------------------------------------------------------------
     case CCR2_CASE:
       
       break;
     case OVERFLOW_CASE: // overflow
       break;
     default: break;
 }
 //------------------------------------------------------------------------------
 }