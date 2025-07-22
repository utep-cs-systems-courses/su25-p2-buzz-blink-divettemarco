#ifndef stateMachine_included
#define stateMachine_included

/* state 0 */
void turn_off_update();

/* state 1 */
void led_toggle_update();

extern int toggleState;

/* state 2 */
void dim_to_bright_update();
void dim_to_bright_limit_update();

extern int greenLimit, greenCount, redLimit, redCount;

/* state 3 */
void wild_update();

/* state 4 */
void update_buzz();

#endif // included
