//here i do the adding functions to led stuff
#if ORB_FIRMWARE == 1 && EMB_SYS_LIB == 1
    #include "lib.h"
    #include "MotorTask.h"
    #include "orb/port/portenums.h"
    #include "Properties.h"

    extern MotorTask mTask[];
    extern DigitalIndicator pwrIndicator;
#endif

class MotorWrapperStruct {
public:
    MotorWrapperStruct(int MotorId){
        #if ORB_FIRMWARE == 1 && EMB_SYS_LIB == 1
            switch(MotorId){
            case PORT_M1:
            case PORT_M2:
            case PORT_M3:
            case PORT_M4:
                taskSelf = &mTask[MotorId];
                (*taskSelf).config(10,10,10,10);
            default:
                return;
                break;
            }
        #endif
    }

    void run(int speed){
    #if ORB_FIRMWARE == 1 && EMB_SYS_LIB == 1
        if(taskSelf != NULL)
            (*taskSelf).set(cPropToORB::Data::Motor::SPEED_MODE,speed,0);
    #endif // ORB_FIRMWARE
    }

    void brake(){
    #if ORB_FIRMWARE == 1 && EMB_SYS_LIB == 1
        if(taskSelf != NULL)
            (*taskSelf).set(cPropToORB::Data::Motor::BRAKE_MODE,0,0);
    #endif // ORB_FIRMWARE
    }

private:
    #if ORB_FIRMWARE == 1 && EMB_SYS_LIB == 1
    MotorTask* taskSelf;
    #endif
};
