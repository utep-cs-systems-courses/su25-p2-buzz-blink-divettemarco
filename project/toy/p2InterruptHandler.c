#include <msp430.h>
#include "switches.h"
#include "toyMain.h"

/* interrupt for port 2 (switches) */

void
__interrupt_vec(PORT2_VECTOR) Port_2(){
  // state 1 
  if (P2IFG & SW1){
    currState = STATE_TOGGLE;
  }
  // state 2
  else if (P2IFG & SW2){
    currState = STATE_DIM_TO_BRIGHT;
  }
  // state 3
  else if (P2IFG & SW3){
    currState = STATE_WILD;
  }
  // state 4
  else if (P2IFG & SW4){
    currState = STATE_BUZZ;
  }
  
  P2IFG &= ~SWITCHES;      /* clear pending sw interrupts */

}
