#include <iostream>
#include <fstream>
#include "py/obj.h"
#include "py/mphal.h"
#include "py/runtime.h"

extern "C"{
    #include <port/micropython_embed.h>
}

// This array is the MicroPython GC heap.
static char heap[8 * 1024];

void run();

uint8_t* loadProgram();

void stopProgram();

// This is example 2 script, which will be compiled and executed.
static const char *example =
    "from orb.devices import led\n"
    "l1 = led(led.LED_POWER)\n"
    "l1.blink(1000,90)\n"
    "l2 = led(led.LED_1)\n"
    "l2.blink(2000,30)\n"
    "l3 = led(led.LED_2)\n"
    "l3.value(1)\n"
    "print(led)"
    ;

//TODO make this whole thing a rtos task that can be registered and executed accordingly
