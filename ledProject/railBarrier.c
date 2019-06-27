#include "railBarrier.h"
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
    buttonOnState = GetLedState( SWITCH0 );
    buttonOffState = GetLedState( SWITCH1 );

    if (buttonOnState == 1) {
        isOnPressed = true;
    }
    if (buttonOffState == 1) {
        isOnPressed = false;
        whiteLedsOff( );
        redLedsOff( );
        counter = 0;
        whiteBlink = true;
    }
 
    if (whiteBlink && isOnPressed)
    {
        whiteLedsOff( );
        DelayMillis( 500 );
        whiteLedsOn( );
        DelayMillis( 500 );
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
        DelayMillis( 500 );    
        redLedsOn( );
        DelayMillis( 500 );    
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
    Led_ON( LED1 );
    Led_ON( LED2 );
    Led_ON( LED3 );
    Led_ON( LED4 );
}

static void whiteLedsOff( )
{
    Led_OFF( LED1 );
    Led_OFF( LED2 );
    Led_OFF( LED3 );
    Led_OFF( LED4 );
}

static void redLedsOn( )
{
    Led_ON( LED5 );
    Led_ON( LED0 );
}

static void redLedsOff( )
{
    Led_OFF( LED5 );
    Led_OFF( LED0 );
}
