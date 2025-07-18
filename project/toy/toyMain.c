//Alternate LEDs from Off, Green, and Red
#include <msp430.h>
#include "toyMain.h"
#include "libTimer.h"
#include "led.h"
#include "switches.h"
#include "buzzer.h"

volatile State currState = STATE_OFF;

int main(void) {
  led_init();
  switch_init();
  buzzer_init();
  configureClocks();/* setup master oscillator, CPU & peripheral clocks */
  enableWDTInterrupts();/* enable periodic interrupt */

  or_sr(0x18);/* CPU off, GIE on */
}
