//Alternate LEDs from Off, Green, and Red
#include <msp430.h>
#include "libTimer.h"
#include "led.h"

int main(void) {
  /* set led bits to output */
  P1DIR |= LEDS;

  /* original: turn on red light, turn off green light */
  //P1OUT &= ~LED_GREEN;
  //P1OUT |= LED_RED;

  /* combo 1: turn off red and green light */
  //P1OUT &= ~LED_GREEN;
  //P1OUT &= ~LED_RED;

  /* combo 2: turn on both red and green light */
  P1OUT |= LED_GREEN;
  P1OUT |= LED_RED;
  
  or_sr(0x18);		/* CPU off, GIE on */
}
