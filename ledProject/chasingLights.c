#include "chasingLights.h"

#define pinOflastLed ledPins[ledSum - 1]

extern SW_STATUS_t sw;

const int ledSum = 6;
const int ledPins[] = { 2, 3, 4, 5, 6, 7 };
const int startButton = 8;
const int stopButton = 9;

static int noOfChangedLed = 1;
static int noOfLed = 0;

void ChasingLights_OneByOne( )
{
    digitalWrite( ledPins[noOfLed], HIGH );
    delay( 200 );
    digitalWrite( ledPins[noOfLed], LOW );

	if (ledPins[noOfLed] == pinOflastLed)
	{
		noOfChangedLed = 2;
	}
}

void ChasingLights_TwoByTwo( )
{
    digitalWrite( ledPins[noOfLed], HIGH );
    if (ledPins[noOfLed] != pinOflastLed)
    {
        digitalWrite( ledPins[noOfLed + 1], HIGH );
	}
    else
    {
        digitalWrite( ledPins[0], HIGH );
    }
    delay( 200 );

    digitalWrite( ledPins[noOfLed], LOW );
    if (ledPins[noOfLed] != pinOflastLed)
    {
        digitalWrite( ledPins[noOfLed + 1], LOW );
    }
    else
    {
        digitalWrite( ledPins[0], LOW );
		noOfChangedLed = 1;
    }
}

void ChasingLights( )
{
	if(sw.sw0 == PRESSED)
	{
		do
		{
			if (noOfChangedLed == 1)
			{
				ChasingLights_OneByOne( );
			}
			else
			{
				ChasingLights_TwoByTwo( );
			}

			noOfLed++;
			if(noOfLed == ledSum)
			{
				noOfLed = 0;
			}
		}while(digitalRead( stopButton ) != HIGH);
  
		sw.sw1 = PRESSED;
  
		for (int noOfLed = 0; noOfLed < ledSum; noOfLed++)
		{
			digitalWrite( ledPins[noOfLed], LOW );
		}
	
		noOfChangedLed = 1;
		noOfLed = 0;
	}
}
