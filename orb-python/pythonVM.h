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
    "from orb.motors import ev3_motor\n"
    "print(ev3_motor)"
    ;

//TODO make this whole thing a rtos task that can be registered and executed accordingly