#include "LedWrapperStruct.h"

// Define the struct for the C wrapper
struct LedWrapper {
	//have a pointer to the orb led class here
    LedWrapperStruct* instance;
};

// Function to create an instance of LedWrapper
extern "C" struct LedWrapper* createLedWrapper(int ledId) {
    struct LedWrapper* wrapper = new LedWrapper;
    wrapper->instance = new LedWrapperStruct(ledId);
    return wrapper;
}

extern "C" void setLedValue(struct LedWrapper* wrapper, int value){
    wrapper->instance->setValue(value);
}

extern "C" int getLedValue(struct LedWrapper* wrapper) {
    return wrapper->instance->getValue();
}

extern "C" void blinkLed(struct LedWrapper* wrapper, int interval, int duration) {
    wrapper->instance->blink(interval, duration);
}

// Function to destroy an instance of LedWrapper
extern "C" void destroyLedWrapper(struct LedWrapper* wrapper) {
    delete wrapper->instance;
    delete wrapper;
}
