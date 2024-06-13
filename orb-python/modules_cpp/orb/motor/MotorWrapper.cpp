#include "MotorWrapperStruct.h"

// Define the struct for the C wrapper
struct MotorWrapper {
	//have a pointer to the orb Motor class here
    MotorWrapperStruct* instance;
};

// Function to create an instance of MotorWrapper
extern "C" struct MotorWrapper* createMotorWrapper(int MotorId) {
    struct MotorWrapper* wrapper = new MotorWrapper;
    wrapper->instance = new MotorWrapperStruct(MotorId);
    return wrapper;
}

// Function to destroy an instance of MotorWrapper
extern "C" void motorFree(struct MotorWrapper* wrapper) {
    wrapper->instance->free();
}
// Function to destroy an instance of MotorWrapper
extern "C" void motorBrake(struct MotorWrapper* wrapper) {
    wrapper->instance->brake();
}

extern "C" void motorDc(struct MotorWrapper* wrapper, int speed) {
    wrapper->instance->dc(speed);
}
// Function to destroy an instance of MotorWrapper
extern "C" void destroyMotorWrapper(struct MotorWrapper* wrapper) {
    delete wrapper->instance;
    delete wrapper;
}
