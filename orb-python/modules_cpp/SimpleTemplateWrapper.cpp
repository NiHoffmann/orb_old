// SimpleTemplateWrapper.cpp

#include "SimpleTemplate.h"

// Define the struct for the C wrapper
struct SimpleTemplateWrapper {
    SimpleTemplate<int>* instance;
};

// Function to create an instance of SimpleTemplateWrapper
extern "C" struct SimpleTemplateWrapper* createSimpleTemplateWrapper(int value) {
    struct SimpleTemplateWrapper* wrapper = new SimpleTemplateWrapper;
    wrapper->instance = new SimpleTemplate<int>(value);
    return wrapper;
}

// Function to print the value of SimpleTemplateWrapper
extern "C" void printSimpleTemplateWrapper(struct SimpleTemplateWrapper* wrapper) {
    wrapper->instance->print();
}

// Function to destroy an instance of SimpleTemplateWrapper
extern "C" void destroySimpleTemplateWrapper(struct SimpleTemplateWrapper* wrapper) {
    delete wrapper->instance;
    delete wrapper;
}