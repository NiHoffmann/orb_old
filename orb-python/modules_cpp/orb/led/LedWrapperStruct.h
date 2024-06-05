//here i do the adding functions to led stuff
#include "lib.h"

extern DigitalIndicator      indUsr1;
extern DigitalIndicator      indUsr2;
//extern Digital      btnUsr1;
//extern Digital      btnUsr2;
extern DigitalButton btn;
extern DigitalButton btnAlt;

extern DigitalIndicator pwrIndicator;

class LedWrapperStruct {
public:
    int getValue() const {
        return value;
    }

    int setValue(int v) {
        pwrIndicator.setBrightness( 20);
        pwrIndicator.blink(1000, 90);
        return value = v;
    }

private:
    int value;
};
