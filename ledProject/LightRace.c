#include "LightRace.h"

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

int LightRace( int runTime )
{
  ResetAllLed();
  runTime = runTime + millis();

  while(true)
  {

    now = millis();
  
    if ( HIGH == digitalRead(SWITCH0) )
    {
      isOn = true;
    }
    if ( HIGH == digitalRead(SWITCH1) )
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
       return 0;
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
  digitalWrite( ledArray[0].pinNumber, LOW );
  digitalWrite( ledArray[1].pinNumber, LOW );
  digitalWrite( ledArray[2].pinNumber, LOW );
  digitalWrite( ledArray[3].pinNumber, LOW );
  digitalWrite( ledArray[4].pinNumber, LOW );
  digitalWrite( ledArray[5].pinNumber, LOW );
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
    if ( timeIndicator == ledArray[l].onTime ) { digitalWrite( ledArray[l].pinNumber, HIGH ); }
    if ( timeIndicator == ledArray[l].offTime ) { digitalWrite( ledArray[l].pinNumber, LOW ); }
    if ( timeIndicator == ledArray[l].onTime2 ) { digitalWrite( ledArray[l].pinNumber, HIGH ); }
    if ( timeIndicator == ledArray[l].offTime2 ) { digitalWrite( ledArray[l].pinNumber, LOW ); }
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
