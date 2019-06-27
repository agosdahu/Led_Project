/*
 * stub_led_handler.c
 *
 *  Created on: 2019. jún. 18.
 *      Author: agosdahu
 */
#include "stub_driver.h"

static myLED_t ledArr[MAX_LED_NUM];
static int timerSetVal = 0;
static int TimerGoOffFlag = 0;

int GetLedStatus(int ledNum)
{
	return ledArr[ledNum].status;
}

int GetLedMode(int ledNum)
{
	return ledArr[ledNum].mode;
}

void pinMode(int ledNum, int dir)
{
	ledArr[ledNum-2].mode = dir;
}

void digitalWrite(int ledNum, int state)
{
	ledArr[ledNum-2].status = state;
}

int digitalRead(int ledNum)
{
	return ledArr[ledNum-2].status;
}



int GetTimerSetVal(void)
{
	return timerSetVal;
}

void SetTimerGoOffFlag(int flag)
{
	TimerGoOffFlag = flag;
}

/*void Led_ON(uint8_t pin)
{
	digitalWrite(pin, HIGH);
}

void Led_OFF(uint8_t pin)
{
	digitalWrite(pin, LOW);
}*/

unsigned long millis( void )
{
	return 1;
}

void delay( unsigned int millis)
{
	
}