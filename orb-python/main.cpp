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


void run(){
    // Initialise MicroPython.
    //
    // Note: &stack_top below should be good enough for many cases.
    // However, depending on environment, there might be more appropriate
    // ways to get the stack top value.
    // eg. pthread_get_stackaddr_np, pthread_getattr_np,
    // __builtin_frame_address/__builtin_stack_address, etc.
    int stack_top;
    mp_embed_init(&heap[0], sizeof(heap), &stack_top);

    uint8_t* byteArray = loadProgram();
    //mp_embed_exec_mpy(byteArray, fileSize);
    delete byteArray;

    mp_embed_exec_str(example);
    // Deinitialise MicroPython.
    mp_embed_deinit();
}

//TODO this is supposed to read the program length and program from flash
uint8_t* loadProgram(){
    std::ifstream file("test.mpy", std::ios::binary);
    if (!file.is_open()) {
        std::cerr << "Failed to open file." << std::endl;
        return new uint8_t[0];
    }

    file.seekg(0, std::ios::end);
    std::streampos fileSize = file.tellg();
    file.seekg(0, std::ios::beg);

    // Allocate memory for the byte array
    uint8_t* byteArray = new uint8_t[fileSize];
     // Read the file into the byte array
    file.read(reinterpret_cast<char*>(byteArray), fileSize);

    // Close the file
    file.close();

    return byteArray;
}

void stopProgram(){
    static mp_obj_exception_t system_exit;
    system_exit.base.type = &mp_type_SystemExit;
    system_exit.traceback_alloc = 0;
    system_exit.traceback_data = NULL;
    system_exit.args = (mp_obj_tuple_t *)&mp_const_empty_tuple_obj;

    MP_STATE_MAIN_THREAD(mp_pending_exception) = &system_exit;
}

int main() {
    run();
    return 0;
}
