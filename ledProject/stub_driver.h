/*
 * stub_led_handler.h
 *
 *  Created on: 2019. jún. 18.
 *      Author: agosdahu
 */

#ifndef TEST_STUB_SOS_LED_STUB_DRIVER_H_
#define TEST_STUB_SOS_LED_STUB_DRIVER_H_

#include <stdint.h>
#include <stdbool.h>

#define MAX_LED_NUM		6u
#define LED0			2u
#define LED1			3u
#define LED2			4u
#define LED3			5u
#define LED4			6u
#define LED5			7u

#define INPUT			0u
#define OUTPUT		1u
#define INPUT_PULLUP 		2u
#define LOW				0u
#define HIGH			1u

typedef struct myLED {
	int status;
	int mode;
} myLED_t;

unsigned long millis( void );
void delay( unsigned int millis);
int GetLedStatus(int ledNum);
int GetLedMode(int ledNum);

void pinMode(int ledNum, int dir);
void digitalWrite(int ledNum, int state);
int digitalRead(int ledNum);

int GetTimerSetVal(void);
void SetTimerGoOffFlag(int flag);

//void Led_ON(uint8_t pin);
//void Led_OFF(uint8_t pin);


#endif /* TEST_STUB_SOS_LED_STUB_DRIVER_H_ */
