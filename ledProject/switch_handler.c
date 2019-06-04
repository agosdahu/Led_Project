#include "switch_handler.h"
#include "Arduino.h"

static int sw0State = 1;
static int sw0_old = 1;

static int sw1State = 1;
static int sw1_old = 1;

void SwitchInit(void)
{
    pinMode(SWITCH0, INPUT_PULLUP);
    pinMode(SWITCH1, INPUT_PULLUP);
}

SW_STATUS_t ReadSwitchStatus(void)
{
    SW_STATUS_t ret = {RELEASED, RELEASED};
    
    sw0_old = sw0State;
    sw1_old = sw1State;

    sw0State = digitalRead(SWITCH0);
    sw1State = digitalRead(SWITCH1);

    if(sw0_old && !sw0State)
    {
        ret.sw0 = PRESSED;
    }
    
    if(sw1_old && !sw1State)
    {
        ret.sw1 = PRESSED;
    }
    
    return ret;
}