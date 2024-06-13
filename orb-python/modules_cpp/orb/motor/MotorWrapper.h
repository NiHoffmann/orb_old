#if ORB_FIRMWARE == 1
// Forward declaration of the struct
struct MotorWrapper;

// Function to create an instance of MotorWrapper
struct MotorWrapper* createMotorWrapper(int MotorId);

void motorFree(struct MotorWrapper* wrapper);
void motorBrake(struct MotorWrapper* wrapper);

// Function to destroy an instance of MotorWrapper
void destroyMotorWrapper(struct MotorWrapper* wrapper);
#endif
