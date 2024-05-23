#include <iostream>

template <typename T>
class SimpleTemplate {
public:
    SimpleTemplate(const T& value) : data(value) {}

    void print() const {
        std::cout << "Value: " << data << std::endl;
    }

private:
    T data;
};
