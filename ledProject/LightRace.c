#include "LightRace.h"
#include "driver.h"
#include <stdbool.h>

typedef struct 
{
   int pinNumber;
   int onTime;
   int offTime;
   int onTime2;
   int offTime2;
} led;

led ledArray[6];

int now = 0;
const int flashTime = 200;
const int numberOfLeds = 6;
bool isOn;

int programEndTime;

void HandleProgramEnd( void );
void TurnOffAllLed( void );
void ResetAllLed( void );
void handleOnAndOffTimes( int timeIndicator );
void SetStartAndStopTimesForACycleForSlowerCar( int baseTime, int delayTime );
void SetStartAndStopTimesForACycleForFasterCar( int baseTime, int delayTime );

void LightRace( void )
{
  int runTime = 2000;
  ResetAllLed();
  runTime = runTime + GetDiffTime();

  while(true)
  {

    now = GetDiffTime();
  
    if ( 1 == GetLedState(SWITCH0) )
    {
      isOn = true;
    }
    if ( 1 == GetLedState(SWITCH1) )
    {
      isOn = false;
    }
    
    if ( isOn )
    {
      handleOnAndOffTimes( now );
      if ( programEndTime < now )
      {
        SetStartAndStopTimesForACycleForSlowerCar( now, 1000 );
        SetStartAndStopTimesForACycleForFasterCar( now, 800 );
      }  
    }
    else
    {
      HandleProgramEnd();
    }

    if ( runTime < now )
    {
       HandleProgramEnd();
    }
  }
}

void HandleProgramEnd()
{
  handleOnAndOffTimes( now );
  ResetAllLed();
  TurnOffAllLed();
}

void TurnOffAllLed()
{
  Led_OFF( ledArray[0].pinNumber );
  Led_OFF( ledArray[1].pinNumber );
  Led_OFF( ledArray[2].pinNumber );
  Led_OFF( ledArray[3].pinNumber );
  Led_OFF( ledArray[4].pinNumber );
  Led_OFF( ledArray[5].pinNumber );
}

void ResetAllLed()
{
  /*ledArray[0] = {2, 0, 0, 0, 0};
  ledArray[1] = {3, 0, 0, 0, 0};
  ledArray[2] = {4, 0, 0, 0, 0};
  ledArray[3] = {5, 0, 0, 0, 0};
  ledArray[4] = {6, 0, 0, 0, 0};
  ledArray[5] = {7, 0, 0, 0, 0};*/

  for ( int n = 0; n < numberOfLeds; n++ )
  {
    ledArray[n].pinNumber = n+2;
    ledArray[n].onTime    = 0;
    ledArray[n].offTime   = 0;
    ledArray[n].onTime2   = 0;
    ledArray[n].offTime2  = 0;
  }
}

void handleOnAndOffTimes( int timeIndicator )
{
  for ( int l = 0; l < numberOfLeds; l++ )
  {
    if ( timeIndicator == ledArray[l].onTime ) { Led_ON( ledArray[l].pinNumber); }
    if ( timeIndicator == ledArray[l].offTime ) { Led_OFF( ledArray[l].pinNumber); }
    if ( timeIndicator == ledArray[l].onTime2 ) { Led_ON( ledArray[l].pinNumber ); }
    if ( timeIndicator == ledArray[l].offTime2 ) { Led_OFF( ledArray[l].pinNumber ); }
  }
}

void SetStartAndStopTimesForACycleForSlowerCar( int baseTime, int delayTime )
{
  ledArray[0].onTime  = baseTime + 1;
  ledArray[0].offTime = ledArray[0].onTime + flashTime;
  
  
  for( int k = 1; k < numberOfLeds; k++)
  {
    ledArray[k].onTime  = (ledArray[k-1].offTime + delayTime - flashTime) + 1;
    ledArray[k].offTime = ledArray[k].onTime + flashTime;
    programEndTime = ledArray[k].offTime;
  }
}

void SetStartAndStopTimesForACycleForFasterCar( int baseTime, int delayTime )
{
  ledArray[0].onTime2  = baseTime + 1;
  ledArray[0].offTime2 = ledArray[0].onTime2 + flashTime;
  
  
  for( int k = 1; k < numberOfLeds; k++)
  {
    ledArray[k].onTime2  = (ledArray[k-1].offTime2 + delayTime - flashTime) + 1;
    ledArray[k].offTime2 = ledArray[k].onTime2 + flashTime;
    programEndTime = ledArray[k].offTime;
  }
}
