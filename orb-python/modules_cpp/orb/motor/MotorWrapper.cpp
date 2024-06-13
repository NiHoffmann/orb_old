#include "MotorWrapperStruct.h"
extern "C"{
    #include "py/gc.h"
    #include "py/obj.h"
    #include "py/runtime.h"
    #include "py/mphal.h"
}

// Define the struct for the C wrapper
typedef struct {
	//have a pointer to the orb Motor class here
    MotorWrapperStruct* instance;
} MotorWrapper;

// Function to create an instance of MotorWrapper
extern "C" MotorWrapper* createMotorWrapper(int MotorId) {
    MotorWrapper* wrapper =(MotorWrapper*) gc_alloc(sizeof(MotorWrapper), false);
    if (wrapper == NULL) {
        // Handle allocation failure
        return NULL;
    }

    wrapper->instance = (MotorWrapperStruct*) gc_alloc(sizeof(MotorWrapperStruct), false);
    if (wrapper->instance == NULL) {
        // Handle allocation failure
        gc_free(wrapper); // Free previously allocated memory for wrapper
    }

    wrapper->instance = new MotorWrapperStruct(MotorId);
    return wrapper;
}

// Function to destroy an instance of MotorWrapper
extern "C" void motorBrake(MotorWrapper* wrapper) {
    (*wrapper).instance->brake();
}

extern "C" void motorRun(MotorWrapper* wrapper, int speed) {
    (*wrapper).instance->run(speed);
}
