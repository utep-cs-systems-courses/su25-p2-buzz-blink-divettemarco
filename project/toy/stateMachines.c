#include <msp430.h>
#include "stateMachines.h"
#include "led.h"
#include "buzzer.h"

/* State 2 variables */
int greenCount = 0;
int greenLimit = 4;
int redCount = 0;
int redLimit = 8;

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

/* State 2: toggle red and green led at different speeds */

void dim_to_bright_update(){
  greenCount++;
  redCount++;

  if (greenCount >= greenLimit) {
    greenCount = 0;
    green_on();
  } else{
    green_off();
  }

  if(redCount >= redLimit) {
    redCount = 0;
    red_on();
  }else{
    red_off();
  }
}

void dim_to_bright_limit_update(){
  greenLimit--;
  redLimit--;

  if( greenLimit <= 0)
    greenLimit = 8;

  if (redLimit <= 0)
    redLimit = 8;
}

/* State 3: toggle */
void wild_green_led_and_buzz_update() {

}

void wild_red_led_update() {

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
