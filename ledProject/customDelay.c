#include "customDelay.h"

//from Arduino documentation of millis():
//"Number of milliseconds passed since the program started.
// Data type: unsigned long.
// This number will overflow (go back to zero), after approximately 50 days"
static unsigned long   actual_time      = 0;
static unsigned long   start_time       = 0;

/*##################################################*/
/* TIMER VARS */
static ulong_t prevTime   = 0;
static ulong_t actTime    = 0;
static int timerVal       = 0;
/*##################################################*/

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

void SetTimer(int time)
{
  timerVal = time;
  prevTime = GetSysTimeMsec();
}

int CheckIfTimerWentOff(void)
{
  int ret = 0;
  actTime = GetSysTimeMsec();
  
  if((actTime-prevTime) >= timerVal){
    ret = 1;
  }
  else{
    ret = 0;
  }

  return ret;
}
