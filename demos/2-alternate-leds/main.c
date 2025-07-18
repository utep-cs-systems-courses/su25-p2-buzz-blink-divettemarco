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

char secCount = 0;

void oncePerSec()
{
  /* turn on and off red led and green led every second */
  static char redState = 0;
  static char greenState = 1;
  switch (redState) {
  case 0:
    redState = 1; P1OUT |= LED_RED; break;
  case 1:
    redState = 0; P1OUT &= ~LED_RED; break;
  }
  switch (greenState){
  case 0:
    greenState = 1; P1OUT |= LED_GREEN; break;
  case 1:
    greenState = 0; P1OUT &= ~LED_GREEN; break;
  }
}

char ledState = 0;

void
__interrupt_vec(WDT_VECTOR) WDT()/* 250 interrupts/sec */
{
  secCount ++;
  if (secCount == 250) {
    secCount = 0;
    oncePerSec();
  }
}
