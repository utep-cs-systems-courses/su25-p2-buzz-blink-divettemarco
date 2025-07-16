//Alternate LEDs from Off, Green, and Red
#include <msp430.h>
#include "libTimer.h"
#include "led.h"

int main(void) {
  P1DIR |= LEDS;
  /* green off, red on  */
  P1OUT &= ~LED_GREEN;
  P1OUT &= ~LED_RED;

  configureClocks();		/* setup master oscillator, CPU & peripheral clocks */
  enableWDTInterrupts();	/* enable periodic interrupt */
  
  or_sr(0x18);			/* CPU off, GIE on */
}

// global state vars that control blinking
int greenLimit = 4;  // duty cycle = 1/blinkLimit
int greenCount = 0;  // cycles 0...blinkLimit-1

int redLimit = 8;
int redCount = 0;

int secondCount = 0; // state var representing repeating time 0…1s

void
__interrupt_vec(WDT_VECTOR) WDT()	/* 250 interrupts/sec */
{
  // handle blinking 
  greenCount ++;
  redCount ++;

  /* turn on green LED every time the limit is hit */
  if (greenCount >= greenLimit) { // on for 1 interrupt period
    greenCount = 0;
    P1OUT |= LED_GREEN;
  } else		          // off for blinkLimit - 1 interrupt periods
    P1OUT &= ~LED_GREEN;

  /* turn on red LED every time the limit is hit */
  if (redCount >= redLimit) {
    redCount = 0;
    P1OUT |= LED_RED;
  }else
    P1OUT &= ~LED_RED;

  // measure a second
  secondCount ++;
  if (secondCount >= 250) {  // once each second
    secondCount = 0;
    /* adjust green LED duty cycle*/
    greenLimit --;	     // increase duty cycle
    if (greenLimit <= 0)    // but don't let duty cycle go over 1/7.
      greenLimit = 8;

    /* adjust red LED duty cycle*/
    redLimit --;
    if (redLimit <= 0) 
      redLimit = 8;
  }
} 

