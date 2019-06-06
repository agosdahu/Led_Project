#include "railBarrier.h"
#include <Arduino.h>
#include "driver.h"

static int counter = 0;
static int whiteBlink = 1;
static int buttonOnState = 0;
static int buttonOffState = 0;
static int isOnPressed = 0;

/* Turn the white leds on */
static void whiteLedsOn( );
/* Turn the white leds off */
static void whiteLedsOff( );
/* Turn the red leds on */
static void redLedsOn( );
/* Turn the white leds off */
static void redLedsOff( );

void railBarrier( )
{
    buttonOnState = digitalRead( SWITCH0 );
    buttonOffState = digitalRead( SWITCH1 );

    if (buttonOnState == HIGH) {
        isOnPressed = true;
    }
    if (buttonOffState == HIGH) {
        isOnPressed = false;
        whiteLedsOff( );
        redLedsOff( );
        counter = 0;
        whiteBlink = true;
    }
 
    if (whiteBlink && isOnPressed)
    {
        whiteLedsOff( );
        delay( 500 );        // delay
        whiteLedsOn( );
        delay( 500 );        // delay  
        counter++;

        if (counter == 10)
        {
            whiteBlink = false;
            counter = 0;
        }
        whiteLedsOff( );
    }
    else if (isOnPressed)
    {
        redLedsOff( );
        delay( 500 );        // delay
        redLedsOn( );
        delay( 500 );        // delay  
        counter++;

        if (counter == 15)
        {
            whiteBlink = true;
            counter = 0;
        }
        redLedsOff( );
    }
}

static void whiteLedsOn( )
{
    digitalWrite( LED1, HIGH );
    digitalWrite( LED2, HIGH );
    digitalWrite( LED3, HIGH );
    digitalWrite( LED4, HIGH );
}

static void whiteLedsOff( )
{
    digitalWrite( LED1, LOW );
    digitalWrite( LED2, LOW );
    digitalWrite( LED3, LOW );
    digitalWrite( LED4, LOW );
}

static void redLedsOn( )
{
    digitalWrite( LED5, HIGH );
    digitalWrite( LED0, HIGH );
}

static void redLedsOff( )
{
    digitalWrite( LED5, LOW );
    digitalWrite( LED0, LOW );
}
