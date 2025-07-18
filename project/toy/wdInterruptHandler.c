#include <msp430.h>
#include "stateMachines.h"
#include "switches.h"
#include "toyMain.h"

void
__interrupt_vec(WDT_VECTOR) WDT(){/* 250 interrupts/sec */
  static int secCount = 0;
  static int twoSecCount = 0;
  
  /* check case and switch if necessary */
  switch (currState)
  {
  /* start with buzzer and leds off*/
  case STATE_OFF:
    turn_off_update();
    break;

  /* toggle red and green on and off every sec; if green is on, red is off and vice versa  */
  case STATE_TOGGLE:
    if (secCount >= 250){
      led_toggle_update();
    }
    break;

  /* make leds go from bright to dim */
  case STATE_DIM_TO_BRIGHT:
    /* update leds and their counts */
    dim_to_bright_update();

    /* update led limit every second*/
    if (secCount >= 250) {
      dim_to_bright_limit_update();
    }
    break;

  /* update buzzer each second, leds on and off at different speeds */
  case STATE_WILD:
    /* update buzzer and green led every second */
    if (secCount >= 250) {
      wild_green_led_and_buzz_update();
      
      /* update red led every two seconds*/
      if (twoSecCount) {
	wild_red_led_update();
      }
    }
    break;

  /* buzzer metronome */
  case STATE_BUZZ:
    if (secCount >= 250) {
      update_buzz();
    }
    break;
  }
  /* update counts for secs */
  //secCount++;
  if (secCount >= 250) {
    secCount = 0;
    twoSecCount++;
    if (twoSecCount == 2) {
      twoSecCount = 0;
    }
  }
  secCount++;
}
