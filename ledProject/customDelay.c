#include "customDelay.h"
#include "Arduino.h"

//from Arduino documentation of millis():
//"Number of milliseconds passed since the program started.
// Data type: unsigned long.
// This number will overflow (go back to zero), after approximately 50 days"
static unsigned long   actual_time      = 0;
static unsigned long   start_time       = 0;

void DelayMillis(int millisec)
{
    delay(millisec);
}

int  GetDiffTime (void)
{
    int retElapsed = 0;
    unsigned long actual_time;

    actual_time  = millis();
    retElapsed = actual_time - start_time;
    start_time = actual_time;

    return retElapsed;   // elapsed time since last reading
}

ulong_t GetSysTimeMsec ()
{
    return millis();
}
