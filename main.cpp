
/* This file is part of the MicroPython project, http://micropython.org/
 * The MIT License (MIT)
 * Copyright (c) 2022-2023 Damien P. George
 */
extern "C"{
    #include <port/micropython_embed.h>
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
    // Initialise MicroPython.
    //
    // Note: &stack_top below should be good enough for many cases.
    // However, depending on environment, there might be more appropriate
    // ways to get the stack top value.
    // eg. pthread_get_stackaddr_np, pthread_getattr_np,
    // __builtin_frame_address/__builtin_stack_address, etc.
    int stack_top;
    mp_embed_init(&heap[0], sizeof(heap), &stack_top);

    // Run the example scripts (they will be compiled first).
    mp_embed_exec_str(example);

    // Deinitialise MicroPython.
    mp_embed_deinit();

    return 0;
}

