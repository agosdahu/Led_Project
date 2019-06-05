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
    int32_t actualTime = millis();
    
    SW_STATUS_t ret =
    {
        {                   // sw0
            RELEASED,       // state
            0,              // lastPressed
            0,              // lastReleased
            0,              // pressedDuration
            0,              // releasedDuration
        },
        {                   // sw1
            RELEASED,       // state
            0,              // lastPressed
            0,              // lastReleased
            0,              // pressedDuration
            0,              // releasedDuration
        }
    };
    
    sw0_old = sw0State;
    sw1_old = sw1State;

    sw0State = digitalRead(SWITCH0);
    sw1State = digitalRead(SWITCH1);

    if (sw0_old && !sw0State)       // sw0 : 1 -> 0
    {
        ret.sw0.state       = PRESSED;
        ret.sw0.lastPressed = actualTime;    // TODO: replace with low level function
    }
    
    if (sw1_old && !sw1State)       // sw1 : 1 -> 0
    {
        ret.sw1.state       = PRESSED;
        ret.sw1.lastPressed = actualTime;    // TODO: replace with low level function
    }

    if (!sw0_old && sw0State)       // sw0 : 0 --> 1
    {
        ret.sw0.state        = RELEASED;
        ret.sw0.lastReleased = actualTime;    // TODO: replace with low level function
    }

    if (!sw1_old && sw1State)       // sw0 : 0 --> 1
    {
        ret.sw1.state        = RELEASED;
        ret.sw1.lastReleased = actualTime;    // TODO: replace with low level function
    }

    if (sw0State == PRESSED)
    {
        ret.sw0.pressedDuration = actualTime - ret.sw0.lastPressed;
    }
    else
    {
        ret.sw0.releasedDuration = actualTime - ret.sw0.lastReleased;
    }
    if (sw1State == PRESSED)
    {
        ret.sw1.pressedDuration = actualTime - ret.sw1.lastPressed;
    }
    else
    {
        ret.sw1.releasedDuration = actualTime - ret.sw1.lastReleased;
    }
    
    return ret;
}

