//Alternate LEDs from Off, Green, and Red
#include <msp430.h>
#include "libTimer.h"
#include "led.h"

int main(void) {
  /* set led bits to output */
  P1DIR |= LEDS;

  /* turn off green led, turn on red led */
  P1OUT &= ~LED_GREEN;
  P1OUT |= LED_RED;

  configureClocks();		/* setup master oscillator, CPU & peripheral clocks */
  enableWDTInterrupts();	/* enable periodic interrupt */
  
  or_sr(0x18);		/* CPU off, GIE on */
}

char ledState = 0;

void
__interrupt_vec(WDT_VECTOR) WDT()	/* 250 interrupts/sec */
{
  switch (ledState) {
  case 0: P1OUT |= LED_GREEN; ledState = 1; break; /* turn on green led */
  case 1: P1OUT &= ~LED_GREEN; ledState = 2; break; /* turn off green led */
  case 2: ledState = 0; /* reset to state 0 */
  }
} 

