#ifndef led_included
#define  led_included

#include <msp430.h>

#define LED_RED BIT0               // P1.0
#define LED_GREEN BIT6             // P1.6
#define LEDS (BIT0 | BIT6)

void led_init();/* initialize LEDs */
void led_update();/* update leds */

void red_on();
void green_on();
void red_off();
void green_off();
void red_toggle();
void green_toggle();

#endif
