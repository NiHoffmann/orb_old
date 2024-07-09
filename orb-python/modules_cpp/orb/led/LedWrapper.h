#if ORB_FIRMWARE == 1
// Forward declaration of the struct
struct LedWrapper;

// Function to create an instance of LedWrapper
struct LedWrapper* getLedWrapper(int ledId);

// Function to print the value of LedWrapper
int getLedValue(struct LedWrapper* wrapper);

void setLedValue(struct LedWrapper* wrapper, int value);

void blinkLed(struct LedWrapper* wrapper, int interval, int duration);

#endif
