from orb.devices import led
l1 = led(led.LED_POWER)
l1.blink(1000,90)
l2 = led(led.LED_1)
l2.blink(2000,30)
l3 = led(led.LED_2)
l3.value(1)
