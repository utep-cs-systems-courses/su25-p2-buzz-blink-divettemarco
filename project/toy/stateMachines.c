#include <msp430.h>
#include "stateMachines.h"
#include "led.h"
#include "buzzer.h"

/* State 2 variables */
int s2greenCount = 0;
int s2greenLimit = 4;
int s2redCount = 0;
int s2redLimit = 8;

/* State 3 variables */
int s3GreenToggleState = 0;
int s3buzzPeriod = 4000;
const int s3buzzLimit = 1000;


/* State 0: turn off leds and buzzer */
void turn_off_update(){
  green_off();
  red_off();
  buzzer_off();
}

/* State 1: toggle red and green led */
void led_toggle_update(){
  static int toggleState = 0;
  if (toggleState){
    red_on();
    green_off();
    toggleState = 0;
  }else{
    red_off();
    green_on();
    toggleState = 1;
  }
}

/* State 2: change red and green led from dim to bright */

void dim_to_bright_update(){
  s2greenCount++;
  s2redCount++;

  if (s2greenCount >= s2greenLimit) {
    s2greenCount = 0;
    green_on();
  } else{
    green_off();
  }

  if(s2redCount >= s2redLimit) {
    s2redCount = 0;
    red_on();
  }else{
    red_off();
  }
}

void dim_to_bright_limit_update(){
  s2greenLimit--;
  s2redLimit--;

  if(s2greenLimit <= 0)
    s2greenLimit = 8;

  if (s2redLimit <= 0)
    s2redLimit = 8;
}

/* State 3: blink leds at different speeds and change buzzer every second*/
void wild_update(){
  if (s3buzzPeriod <= s3buzzLimit) {
    s3buzzPeriod = 4000;
  } else {
    s3buzzPeriod -= 100;
  }
  buzzer_set_period(s3buzzPeriod);
  red_toggle();
  if (s3GreenToggleState) {
    s3GreenToggleState = 0;
    green_toggle();
  }else{
    s3GreenToggleState = 1;
  }
}


/* State 4: cycle between buzzer states */
void update_buzz(){
  static int buzzState = 0;
  switch(buzzState){
  case 0:
    buzzState++;
    buzzer_set_period(1000);
    break;
  case 1:
    buzzState++;
    buzzer_set_period(1500);
    break;
  case 2:
    buzzState++;
    buzzer_set_period(2000);
    break;
  case 3:
    buzzState++;
    buzzer_set_period(2500);
    break;
  case 4:
    buzzState = 0;
    buzzer_off();
    break;
  }
}
