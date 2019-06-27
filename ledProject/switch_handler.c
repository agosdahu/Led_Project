#include "switch_handler.h"


static int sw0State = RELEASED;
static int sw1State = RELEASED;

static SW_STATE_t EvalState (int actState);

void SwitchInit(void)
{
    pinMode(SWITCH0, INPUT_PULLUP);
    pinMode(SWITCH1, INPUT_PULLUP);
}

SW_STATUS_t ReadSwitchStatus(void)
{
    SW_STATUS_t ret;
    
    sw0State = digitalRead(SWITCH0);
    sw1State = digitalRead(SWITCH1);

    ret.sw0 = EvalState(sw0State);
    ret.sw1 = EvalState(sw1State);

    return ret;
}

SW_STATE_t EvalState (int actState)
{
    SW_STATE_t ret = RELEASED;

    if(actState == RELEASED){
        ret = RELEASED;
    }
    
    else{
        ret = PRESSED;
    }

    return ret;
}