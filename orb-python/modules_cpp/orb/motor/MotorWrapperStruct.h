//here i do the adding functions to led stuff
#if ORB_FIRMWARE == 1 && EMB_SYS_LIB == 1
    #include "lib.h"
    #include "orb/port/portenums.h"
    //extern MotorTask mTask[];
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
                //taskSelf = &mTask[MotorId];
            default:
                return;
                break;
            }
        #endif
    }

    void brake(){
    #if ORB_FIRMWARE == 1 && EMB_SYS_LIB == 1

    #endif // ORB_FIRMWARE
    }

    void free() {
    #if ORB_FIRMWARE == 1 && EMB_SYS_LIB == 1
        pwrIndicator.setBrightness( 20 );
        pwrIndicator.blink(1000, 1000);
    #endif // ORB_FIRMWARE
    }

private:
    #if ORB_FIRMWARE == 1 && EMB_SYS_LIB == 1
    //MotorTask* taskSelf;
    #endif
};
