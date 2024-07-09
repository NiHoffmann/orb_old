#include "LedWrapperStruct.h"

// Define the struct for the C wrapper
struct LedWrapper {
	//have a pointer to the orb led class here
    LedWrapperStruct* instance;
};

LedWrapperStruct leds[] = {
    LedWrapperStruct(LED_POWER),
    LedWrapperStruct(LED_1),
    LedWrapperStruct(LED_2)
};

extern "C" struct LedWrapper* getLedWrapper(int ledId) {
    struct LedWrapper* wrapper = new LedWrapper;
    wrapper->instance = &leds[ledId];
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

