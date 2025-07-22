#include <msp430.h>
#include "libTimer.h"
#include "buzzer.h"

/* set up buzzer */
void buzzer_init()
{
  /* 
       Direct timer A output "TA0.1" to P2.6.  
        According to table 21 from data sheet:
          P2SEL2.6, P2SEL2.7, anmd P2SEL.7 must be zero
          P2SEL.6 must be 1
        Also: P2.6 direction must be output
  */
  timerAUpmode();/* used to drive speaker */
  P2SEL2 &= ~(BUZZER | BIT7);
  P2SEL &= ~BIT7;
  P2SEL |= BUZZER;
  P2DIR = BUZZER;/* enable output to speaker (P2.6) */
}

/* update buzzer period */
void buzzer_set_period(short cycles) /* buzzer clock = 2MHz.  (period of 1k results in 2kHz tone) */
{
  CCR0 = cycles;
  CCR1 = cycles >> 1;/* one half cycle */
}

/* turn off buzzer */
void buzzer_off(){
  CCR0 = 0;
  CCR1 = 0;
}




