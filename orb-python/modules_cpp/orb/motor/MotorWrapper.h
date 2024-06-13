#if ORB_FIRMWARE == 1
// Forward declaration of the struct
struct MotorWrapper;

// Function to create an instance of MotorWrapper
struct MotorWrapper* createMotorWrapper(int MotorId);

void motorBrake(struct MotorWrapper* wrapper);
void motorRun(struct MotorWrapper* wrapper, int speed);

#endif
