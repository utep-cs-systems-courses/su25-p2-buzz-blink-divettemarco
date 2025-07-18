#ifndef buzzer_included
#define buzzer_included

#define BUZZER BIT6

void buzzer_init();
void buzzer_set_period(short cycles);
void buzzer_off();

#endif // included
