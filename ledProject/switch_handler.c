#include "switch_handler.h"
#include "Arduino.h"

static int sw0State = 1;
static int sw0_old = 1;
static uint32_t sw0_lastPressed = 0;

static int sw1State = 1;
static int sw1_old = 1;
static uint32_t sw1_lastPressed = 0;

void SwitchInit(void)
{
    pinMode(SWITCH0, INPUT_PULLUP);
    pinMode(SWITCH1, INPUT_PULLUP);
}

SW_STATUS_t ReadSwitchStatus(void)
{
    uint32_t sw0_lastPressed_old;
    uint32_t sw1_lastPressed_old;
    
    SW_STATUS_t ret =
    {
        {                   // sw0
            RELEASED,       // state
            0,              // lastPressed
            0               // pressedDuration
        },
        {                   // sw1
            RELEASED,       // state
            0,              // lastPressed
            0               // pressedDuration
        }
    };
    
    sw0_old = sw0State;
    sw1_old = sw1State;
    sw0_lastPressed_old = sw0_lastPressed;
    sw1_lastPressed_old = sw1_lastPressed;    

    sw0State = digitalRead(SWITCH0);
    sw1State = digitalRead(SWITCH1);

    if(sw0_old && !sw0State)        // sw0 : 1 -> 0
    {
        ret.sw0.state           = PRESSED;
        ret.sw0.lastPressed     = millis();    // TODO: replace with low level function
    }
    
    if(sw1_old && !sw1State)        // sw1 : 1 -> 0
    {
        ret.sw1.state           = PRESSED;
        ret.sw1.lastPressed     = millis();    // TODO: replace with low level function
    }
    
    ret.sw0.pressedDuration = millis() - ret.sw0.lastPressed;
    ret.sw1.pressedDuration = millis() - ret.sw1.lastPressed;
    
    return ret;
}
