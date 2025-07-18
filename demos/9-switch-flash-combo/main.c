#include <msp430.h>
#include "libTimer.h"

#define LED_RED BIT0               // P1.0
#define LED_GREEN BIT6             // P1.6
#define LEDS (LED_RED | LED_GREEN)

#define SW1 BIT3		/* switch1 is p2.3 */
#define SWITCHES SW1		/* only 1 switch on this board */

void switch_init() {
  P2REN |= SWITCHES;		/* enables resistors for switches */
  P2IE |= SWITCHES;		/* enable interrupts from switches */
  P2OUT |= SWITCHES;		/* pull-ups for switches */
  P2DIR &= ~SWITCHES;		/* set switches' bits for input */
}

void led_init() {
  P1DIR |= LEDS;
  P1OUT &= ~LEDS;		/* leds initially off */
}

void wdt_init() {
  configureClocks();		/* setup master oscillator, CPU & peripheral clocks */
  enableWDTInterrupts();	/* enable periodic interrupt */
}

void main(void) 
{  
  switch_init();
  led_init();
  wdt_init();
    
  or_sr(0x18);  // CPU off, GIE on
} 

static int buttonDown;

void
switch_interrupt_handler()
{
  char p2val = P2IN;		/* switch is in P2 */

  /* update switch interrupt sense to detect changes from current buttons */
  P2IES |= (p2val & SWITCHES);	/* if switch up, sense down */
  P2IES &= (p2val | ~SWITCHES);	/* if switch down, sense up */

  if (p2val & SW1) {		/* button up */
    P1OUT &= ~LED_GREEN;
    buttonDown = 0;
  } else {			/* button down */
    P1OUT |= LED_GREEN;
    buttonDown = 1;
  }
}


/* Switch on P1 (S2) */
void
__interrupt_vec(PORT2_VECTOR) Port_2(){
  /* if the button is down, process the interrupt */
  if (P2IFG & SWITCHES) {	      /* did a button cause this interrupt? */
    P2IFG &= ~SWITCHES;		      /* clear pending sw interrupts */
    switch_interrupt_handler();	/* single handler for all switches */
  }
}

void
__interrupt_vec(WDT_VECTOR) WDT()	/* 250 interrupts/sec */
{
  static int blink_count = 0;
  switch (blink_count) { 
  /* red by default will be dimmer */
  case 6: 
    blink_count = 0;
    P1OUT |= LED_RED;
    break;
  /* if button is pressed down, red will be brighter */
  default:
    blink_count ++;
    if (!buttonDown) P1OUT &= ~LED_RED; /* don't blink off if button is down */
  }
} 
