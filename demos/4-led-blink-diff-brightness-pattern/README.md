## Description

This program implements mutliple state machines where every second, both the red
LED and green LED's limit is adjusted (0 =< n =< 8). both red and green LEDs
go from dim to bright. they are on different cycles, are independent of each
other, and reach peak brightness at different moments.

* one to blink the leds with some duty cycle

* one to modify the blink duty cycles once each second

* one to cause an event every second
