#ifndef _BVEZSENYI_FUNC_H_
#define _BVEZSENYI_FUNC_H_

#include "driver.h"
#include "Arduino.h"

#define SHORT_BLINK  250    // in milisec
#define LONG_BLINK  500     // in milisec 
#define MY_TRUE 1
#define MY_FALSE 0
#define NUM_OF_STATES 3
#define NOT_INITED  0
#define INITED  1
#define INNER_CNT_INIT_VALUE 0


typedef struct main_conatiner
{
  int main_counter;
  int main_state;
  
}MAIN_CONTAINER;
  

typedef struct state_container
{  
  char how_many_times;
  char how_many_times_cnt;
  int how_long;

}STATE_CONTAINER;


void best_led_show_in_the_history_of_mankind( void );
void main_state_handler( STATE_CONTAINER* );
char switch_main_state( STATE_CONTAINER* )
char state_func( STATE_CONTAINER* );
void bvezsenyi_led_handler( STATE_CONTAINER* );
void turn_on_leds_1( void );
void turn_on_leds_2( void );
#endif /* _BVEZSENYI_FUNC_H_ */
