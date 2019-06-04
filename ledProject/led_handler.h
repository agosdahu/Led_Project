#ifndef LED_HANDLER_H
#define LED_HANDLER_H

#define LED0        2u
#define LED1        3u
#define LED2        4u
#define LED3        5u
#define LED4        6u
#define LED5        7u

// global functions
void   Led_Init(void);
void   Led_ON(uint8_t pin);
void   Led_OFF(uint8_t pin);
int    GetLedState(uint8_t pin);
void Led_Reset();

#endif //LED_HANDLER_H