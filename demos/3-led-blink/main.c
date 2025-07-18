//Alternate LEDs from Off, Green, and Red
#include <msp430.h>
#include "libTimer.h"
#include "led.h"

int main(void) {
  P1DIR |= LEDS;
  P1OUT |= LED_GREEN;
  P1OUT |= LED_RED;

  configureClocks();		/* setup master oscillator, CPU & peripheral clocks */
  enableWDTInterrupts();	/* enable periodic interrupt */
  
  or_sr(0x18);			/* CPU off, GIE on */
}

// global state var to count time
int secCount = 0;
int twoSecCount = 0;

void
__interrupt_vec(WDT_VECTOR) WDT()	/* 250 interrupts/sec */
{
  secCount++;
  twoSecCount++;
  if (secCount >= 250) {        	/* once each sec... */
    secCount = 0;	     	/* reset count */
    P1OUT ^= LED_GREEN;          /* toggle green */
  }
  if (twoSecCount >= 500) {                /* once each sec... */
    twoSecCount = 0;
    P1OUT ^= LED_RED;
  }
} 

