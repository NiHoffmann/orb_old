#include "LedWrapperStruct.h"

// Define the struct for the C wrapper
struct LedWrapper {
	//have a pointer to the orb led class here
    LedWrapperStruct* instance;
};

// Function to create an instance of LedWrapper
extern "C" struct LedWrapper* createLedWrapper() {
    struct LedWrapper* wrapper = new LedWrapper;
    wrapper->instance = new LedWrapperStruct();
    return wrapper;
}

extern "C" int setValueLedWrapper(struct LedWrapper* wrapper, int value){
    return wrapper->instance->setValue(value);
}

extern "C" int getValueLedWrapper(struct LedWrapper* wrapper) {
    return wrapper->instance->getValue();
}

// Function to destroy an instance of LedWrapper
extern "C" void destroyLedWrapper(struct LedWrapper* wrapper) {
    delete wrapper->instance;
    delete wrapper;
}
