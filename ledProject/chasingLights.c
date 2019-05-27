#include "chasingLights.h"

#define pinOflastLed ledArray[ledSum - 1]

extern SW_STATUS_t sw;

static const int ledSum = 6;
static const int ledArray[] = { LED0, LED1, LED2, LED3, LED4, LED5 };

static int noOfChangedLed = 1;
static int noOfLed = 0;

void ChasingLights_OneByOne( )
{
    digitalWrite( ledArray[noOfLed], HIGH );
    delay( 200 );
    digitalWrite( ledArray[noOfLed], LOW );

	if (ledArray[noOfLed] == pinOflastLed)
	{
		noOfChangedLed = 2;
	}
}

void ChasingLights_TwoByTwo( )
{
    digitalWrite( ledArray[noOfLed], HIGH );
    if (ledArray[noOfLed] != pinOflastLed)
    {
        digitalWrite( ledArray[noOfLed + 1], HIGH );
	}
    else
    {
        digitalWrite( ledArray[0], HIGH );
    }
    delay( 200 );

    digitalWrite( ledArray[noOfLed], LOW );
    if (ledArray[noOfLed] != pinOflastLed)
    {
        digitalWrite( ledArray[noOfLed + 1], LOW );
    }
    else
    {
        digitalWrite( ledArray[0], LOW );
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
		}while(digitalRead( SWITCH1 ) != HIGH);
  
		for (int noOfLed = 0; noOfLed < ledSum; noOfLed++)
		{
			digitalWrite( ledArray[noOfLed], LOW );
		}
	
		noOfChangedLed = 1;
		noOfLed = 0;
	}
}
