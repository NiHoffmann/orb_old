//here i do the adding functions to led stuff
#if ORB_FIRMWARE == 1 && EMB_SYS_LIB == 1
#include "lib.h"
#include "orb/led/ledenums.h"
extern Digital ledUsr1;
extern Digital ledUsr2;
extern Digital ledPwr;

extern DigitalIndicator      indUsr1;
extern DigitalIndicator      indUsr2;
extern DigitalIndicator pwrIndicator;
#endif

class LedWrapperStruct {
public:
    LedWrapperStruct(int ledId){
        #if ORB_FIRMWARE == 1 && EMB_SYS_LIB == 1
            switch(ledId){
            case LED_POWER:
                taskSelf = &pwrIndicator;
                self = &ledPwr;
                break;
            case LED_1:
                taskSelf = &indUsr1;
                self = &ledUsr1;
                break;
            case LED_2:
                taskSelf = &indUsr2;
                self = &ledUsr2;
                break;
            default:
                return;
                break;
            }
        #endif
    }

    int getValue() const {
        #if ORB_FIRMWARE == 1 && EMB_SYS_LIB == 1
            (*self).get();
        #endif
        return 0;
    }

    void setValue(int v) {
        #if ORB_FIRMWARE == 1 && EMB_SYS_LIB == 1
            (*taskSelf).setBrightness( 20 * (v > 0) );
            (*taskSelf).blink(1000, 1000);
        #endif
    }

    void blink(int interval, int duration){
        #if ORB_FIRMWARE == 1 && EMB_SYS_LIB == 1
            (*taskSelf).setBrightness( 20 );
            if(taskSelf != NULL){
                (*taskSelf).blink(interval, duration);
            }
        #endif
    }

private:
    #if ORB_FIRMWARE == 1 && EMB_SYS_LIB == 1
    Digital* self;
    DigitalIndicator* taskSelf;
    #endif
};
