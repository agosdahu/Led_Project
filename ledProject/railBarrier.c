#include "kisskahu.h"
#include <Arduino.h>

static int counter = 0;
static int whiteBlink = 1;
static int buttonOnState = 0;
static int buttonOffState = 0;
static int isOnPressed = 0;

static int leds[] = { LED5, LED4, LED3, LED2, LED1, LED0 };

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
    buttonOnState = digitalRead( BUTTONON );
    buttonOffState = digitalRead( BUTTONOFF );

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
    digitalWrite( leds[1], HIGH );
    digitalWrite( leds[2], HIGH );
    digitalWrite( leds[3], HIGH );
    digitalWrite( leds[4], HIGH );
}

static void whiteLedsOff( )
{
    digitalWrite( leds[1], LOW );
    digitalWrite( leds[2], LOW );
    digitalWrite( leds[3], LOW );
    digitalWrite( leds[4], LOW );
}

static void redLedsOn( )
{
    digitalWrite( leds[0], HIGH );
    digitalWrite( leds[5], HIGH );
}

static void redLedsOff( )
{
    digitalWrite( leds[0], LOW );
    digitalWrite( leds[5], LOW );
}
