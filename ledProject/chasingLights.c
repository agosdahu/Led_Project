#include "chasingLights.h"

#define pinOflastLed ledPinArray[ledSum - 1]

SW_STATUS_t sw;

static const int ledSum = 6;
static const int ledPinArray[] = { LED0, LED1, LED2, LED3, LED4, LED5 };

static int noOfChangedLed = 1;
static int noOfLed = 0;

void ChasingLights_OneByOne( )
{
    Led_ON( ledPinArray[noOfLed] );
    DelayMillis( 200 );
    Led_OFF( ledPinArray[noOfLed] );
	
    if (ledPinArray[noOfLed] == pinOflastLed)
    {
        noOfChangedLed = 2;
    }
}

void ChasingLights_TwoByTwo( )
{
    Led_ON( ledPinArray[noOfLed] );
    if (ledPinArray[noOfLed] != pinOflastLed)
    {
        Led_ON( ledPinArray[noOfLed + 1] );
    }
    else
    {
        Led_ON( ledPinArray[0] );
    }
    DelayMillis( 200 );

    Led_OFF( ledPinArray[noOfLed] );
    if (ledPinArray[noOfLed] != pinOflastLed)
    {
        Led_OFF( ledPinArray[noOfLed + 1] );
    }
    else
    {
        Led_OFF( ledPinArray[0] );
	noOfChangedLed = 1;
    }
}

void ChasingLights( )
{
	if(sw.sw0 != 1)
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
		}while(ReadSwitchStatus().sw1 == 1);
  
		for (int noOfLed = 0; noOfLed < ledSum; noOfLed++)
		{
			Led_OFF( ledPinArray[noOfLed] );
		}
	
		noOfChangedLed = 1;
		noOfLed = 0;
	}
}
