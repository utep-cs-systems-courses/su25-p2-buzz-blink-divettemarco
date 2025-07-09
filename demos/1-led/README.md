## Description

This program turns on the red led

Be sure to understand the manipulation of P1OUT and P1DIR.

## Suggested Activities

* Modify so that different combinations of LEDs are illuminated.

  * original combo: turn on red led

  * modified combos: turn off green and red leds, turn on green and red leds


* Determine the impact of not setting one of the LED bits in P1DIR (and why).

  * not setting one of the LED bits in P1DIR makes it so when the program is
    executed, any instructions trying to modify the LED light will have no
    effect. this is because setting on bits in P1DIR sets them to "output" mode and
    not setting any bits in P1DIR means none will be in "output" mode
