#ifndef LED_HANDLER_H
#define LED_HANDLER_H

#include "driver.h"

// global functions
void   LedInit(void);
void   SetLed(uint8_t pin);
void   ClearLed(uint8_t pin);
int8_t GetLedState(uint8_t pin);
void   SetLedState(uint8_t pin, uint8_t state);
void   SwitchLedState(uint8_t pin);



#endif //LED_HANDLER_H