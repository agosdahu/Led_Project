/*
    author  : kurdbohu
    date    : 2019-05-26
*/

// --------------------------------------------------------- //
// extern includes

#include "Arduino.h"
#include "globdefs.h"

// --------------------------------------------------------- //
// local definitions

#define LED_ARRAY_SIZE     6u
#define LED_HIGH_TIME      200u
#define LED_LOW_TIME_MIN   200u
#define LED_LOW_TIME_MAX   1000u
#define LED_LOW_TIME_STEP  50u

// --------------------------------------------------------- //
// static functions

static void switch_led_state(void);
static void reset_counter(void);

// --------------------------------------------------------- //
// static variables

static const uint16_t led_array[LED_ARRAY_SIZE] = {LED0, LED1, LED2, LED3, LED4, LED5};
static int32_t   actual_time      = 0;
static int32_t   start_time       = 0;
static int32_t   elapsed_time     = 0;
static int32_t   led_state        = LOW;
static uint16_t  led_low_time_act = LED_LOW_TIME_MAX;
static int16_t   direction        = 1;

// --------------------------------------------------------- //
// implementation

void kurdbohu_loop(void)
{
    actual_time  = millis();
    elapsed_time = actual_time - start_time;
    
    if (led_state   == HIGH  &&
        elapsed_time > LED_LOW_TIME_MAX)
    {
        switch_led_state();
    }

    if (led_state == LOW)
    {
        if (elapsed_time > led_low_time_act)
        {
            switch_led_state();
        }
        else
        {
            if (led_low_time_act > LED_LOW_TIME_MAX  ||
                led_low_time_act < LED_LOW_TIME_MIN)
            {
                direction *= (-1);
            }
            led_low_time_act += direction * LED_LOW_TIME_STEP;
        }
    }
    
    // Serial.println(led_state);
}

static void switch_led_state(void)
{
    unsigned int i;

    // switch state
    led_state = (led_state == LOW ? HIGH : LOW);
    
    // set LEDs' state (hardware)
    for(i=0; i<LED_ARRAY_SIZE; i++)
    {
        digitalWrite(led_array[i], led_state);
    }

    reset_counter();
}

static void reset_counter(void)
{
    start_time   = actual_time;
    elapsed_time = 0;
}
