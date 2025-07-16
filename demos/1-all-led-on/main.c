//Alternate LEDs from Off, Green, and Red
#include <msp430.h>
#include "libTimer.h"
#include "led.h"

int main(void) {
  /* set led bits to output */
  P1DIR |= LEDS;

  /* turn on red and green led */
  P1OUT |= LED_GREEN;
  P1OUT |= LED_RED;
  
  or_sr(0x18);		/* CPU off, GIE on */
}
