#include "led_handler.h"

// --------------------------------------------------------- //
// local definitions

#define NUM_OF_LEDS  6

// --------------------------------------------------------- //
// local structured tyes

typedef struct led_state
{
    uint8_t pin;
    uint8_t state;
}LED_STATE;


// --------------------------------------------------------- //
// static functions

static int8_t  GetLedState(uint8_t pin);
static void    SetLedState(uint8_t pin, uint8_t state);
static int8_t  GetLedIndex(uint8_t pin);

static void HW_SetLed(uint8_t pin);
static void HW_ClearLed(uint8_t pin);
static void HW_SetPinInput(uint8_t pin);
static void HW_SetPinOutput(uint8_t pin);

// --------------------------------------------------------- //
// static variables

static LED_STATE LedStates[NUM_OF_LEDS] =
{
    {LED0, LOW},
    {LED1, LOW},
    {LED2, LOW},
    {LED3, LOW},
    {LED4, LOW},
    {LED5, LOW},
};


// --------------------------------------------------------- //
// implementation

void LedInit(void)
{
    HW_SetPinOutput(LED0);
    HW_SetPinOutput(LED1);
    HW_SetPinOutput(LED2);
    HW_SetPinOutput(LED3);
    HW_SetPinOutput(LED4);
    HW_SetPinOutput(LED5);

    ClearLed(LED0);
    ClearLed(LED1);
    ClearLed(LED2);
    ClearLed(LED3);
    ClearLed(LED4);
    ClearLed(LED5);
}

void SetLed(uint8_t pin)
{
    SetLedState(pin, HIGH);  
}

void ClearLed(uint8_t pin)
{
    SetLedState(pin, LOW);
}

void SwitchLedState(uint8_t pin)
{
    int8_t  LedIndex = -1;
    int8_t  LedState = -1;

    LedIndex = GetLedIndex(pin);

    if (LedIndex != -1)
    {
        LedState = LedStates[LedIndex].state;
        if (LedState == LOW)
        {
            SetLed(pin);
        }
        else
        {
            ClearLed(pin);
        }
    }
}

static int8_t GetLedState(uint8_t pin)
{
    int8_t  LedIndex = -1;
    int8_t  LedState = -1;

    LedIndex = GetLedIndex(pin);

    if (LedIndex != -1)
    {
        LedState = LedStates[LedIndex].state;
    }

    return (LedState);
}

static void SetLedState(uint8_t pin, uint8_t state)
{
    int8_t LedIndex = -1;

    LedIndex = GetLedIndex(pin);

    if (LedIndex != -1)
    {
        LedStates[LedIndex].state = state;

        if (state == LOW)
        {
            HW_ClearLed(pin);
        }
        else
        {
            HW_SetLed(pin);
        }
        
    }
}

static int8_t GetLedIndex(uint8_t pin)
{
    int8_t  LedIndex = -1;
    uint8_t i;
    
    for(i = 0; i < NUM_OF_LEDS; i++)
    {
        if (LedStates[i].pin == pin)
        {
            LedIndex = i;
            break;
        }
    }

    return(LedIndex);
}

// --------------------------------------------------------- //
// low level functions

static void HW_SetLed(uint8_t pin)
{
    digitalWrite(pin, HIGH);
}

static void HW_ClearLed(uint8_t pin)
{
    digitalWrite(pin, LOW);
}

static void HW_SetPinInput(uint8_t pin)
{
    pinMode(pin, INPUT);
}

static void HW_SetPinOutput(uint8_t pin)
{
    pinMode(pin, OUTPUT);
}

