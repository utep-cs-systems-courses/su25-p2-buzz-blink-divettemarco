#include <msp430.h>
#include "led.h"
#include "switches.h"

/* turn on red led */
void red_on()
{
  P1OUT |= LED_RED; 
}

/* turn on green led */
void green_on()
{
  P1OUT |= LED_GREEN;
}

/* turn off red led */
void red_off() {
  P1OUT &= ~LED_RED;
}

/* turn off green led */
void green_off() {
  P1OUT &= ~LED_GREEN;
}

/* toggle red led */
void red_toggle(){
  P1OUT ^= LED_RED;
}

/* toggle green led */
void green_toggle(){
  P1OUT ^= LED_GREEN;
}

/* set up leds */
void led_init()
{
  P1DIR |= LEDS; // bits attached to leds are output
}
