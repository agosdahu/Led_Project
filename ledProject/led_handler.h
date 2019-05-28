#ifndef LED_HANDLER_H
#define LED_HANDLER_H

#include "Arduino.h"
#include "globdefs.h"

void LedInit(void);
void SetLed(uint8_t pin);
void ClearLed(uint8_t pin);
void SwitchLedState(uint8_t pin);

#endif //LED_HANDLER_H
