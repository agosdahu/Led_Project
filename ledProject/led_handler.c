#include "led_handler.h"
#include "Arduino.h"



void Led_Init(void)
{
    pinMode(LED0, OUTPUT);
    pinMode(LED1, OUTPUT);
    pinMode(LED2, OUTPUT);
    pinMode(LED3, OUTPUT);
    pinMode(LED4, OUTPUT);
    pinMode(LED5, OUTPUT);

    Led_Reset();
}

void   Led_ON(uint8_t pin)
{
    digitalWrite(pin, HIGH);
}

void   Led_OFF(uint8_t pin)
{
    digitalWrite(pin, LOW);
}

int GetLedState(uint8_t pin)
{
    return digitalRead(pin);
}

void Led_Reset()
{
    digitalWrite(LED0, LOW);
    digitalWrite(LED1, LOW);
    digitalWrite(LED2, LOW);
    digitalWrite(LED3, LOW);
    digitalWrite(LED4, LOW);
    digitalWrite(LED5, LOW);
}
