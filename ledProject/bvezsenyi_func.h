#ifndef _BVEZSENYI_FUNC_H_
#define _BVEZSENYI_FUNC_H_

#include "driver.h"
#include "Arduino.h"

#define SHORT_BLINK  250    // in milisec
#define LONG_BLINK  500     // in milisec 
#define NUM_OF_LEDS 3
#define MY_TRUE 1
#define MY_FALSE 0

typedef enum stages_e
{
    FIRST_STAGE = 0,
    SECOND_STAGE,
    THIRD_STAGE
    
}STAGES_E;

typedef struct state_handler_struct
{
    char state;
    char main_cnt;
    
}STATE_HANDLER_STRUCT;

void best_led_show_in_the_history_of_mankind( void );
void main_state_handler( int , STATE_HANDLER_STRUCT* , STAGES_E );
char state_func( int , char );
void turn_on_leds_1( void );
void turn_on_leds_2( void );
#endif /* _BVEZSENYI_FUNC_H_ */
