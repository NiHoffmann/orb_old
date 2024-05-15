#include <iostream>
#include "lib.h"
#include "UserInterface.h"

extern DigitalIndicator pwrIndicator;

template <typename T>
class SimpleTemplate {
public:
    SimpleTemplate(const T& value) : data(value) {}

    void print() const {
        pwrIndicator.setBrightness(100); pwrIndicator.blink( 200, 50);
        std::cout << "Value: " << data << std::endl;
    }

private:
    T data;
};
