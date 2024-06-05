#if ORB_FIRMWARE == 1
// Forward declaration of the struct
struct LedWrapper;

// Function to create an instance of LedWrapper
struct LedWrapper* createLedWrapper(int value);

// Function to print the value of LedWrapper
int getValueLedWrapper(struct LedWrapper* wrapper);

int setValueLedWrapper(struct LedWrapper* wrapper, int value);

// Function to destroy an instance of LedWrapper
void destroyLedWrapper(struct LedWrapper* wrapper);
#endif
