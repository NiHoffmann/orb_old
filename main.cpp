
/* This file is part of the MicroPython project, http://micropython.org/
 * The MIT License (MIT)
 * Copyright (c) 2022-2023 Damien P. George
 */
#include <iostream>
#include <fstream>

extern "C"{
    #include <port/micropython_embed.h>
    #include "c_hello/modc_hello.h"
}

// This is example 2 script, which will be compiled and executed.
static const char *example =
    "import c_hello\n"
    "print(c_hello.hello())\n"
    "print(c_hello.hello2())\n"
    ;

// This array is the MicroPython GC heap.
static char heap[8 * 1024];

int main() {
    std::cout << "hi" << std::endl;
    // Initialise MicroPython.
    //
    // Note: &stack_top below should be good enough for many cases.
    // However, depending on environment, there might be more appropriate
    // ways to get the stack top value.
    // eg. pthread_get_stackaddr_np, pthread_getattr_np,
    // __builtin_frame_address/__builtin_stack_address, etc.
    int stack_top;
    mp_embed_init(&heap[0], sizeof(heap), &stack_top);

    std::ifstream file("test.mpy", std::ios::binary);
    if (!file.is_open()) {
        std::cerr << "Failed to open file." << std::endl;
        return 1;
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
    mp_embed_exec_mpy(byteArray, fileSize);
    delete[] byteArray;

    // Run the example scripts (they will be compiled first).
    //mp_embed_exec_str(example);

    // Deinitialise MicroPython.
    mp_embed_deinit();
    return 0;
}
