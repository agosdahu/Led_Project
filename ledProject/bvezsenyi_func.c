#include "bvezsenyi_func.h"

/*
Brief:
  Within best_led_show_in_the_history_of_mankind() function there are 3 main states: 
  1.) Short blinking -> see definition of SHORT_BLINK
  2.) Long blinking -> see definition of LONG_BLINK 
  3.) Short blinking -> see definition of SHORT_BLINK

  state_func is responsible for timing in an almos non blocking way -> there is only 1 ms delay in it
  There is an inner counter which increments in every ms. If inner counter reach the 
  value of 't' ( first argument of state_func ), state_func returns with TRUE, and 
  main state expection is runs. First argument of main_state_handler determines the cycles 
  of the current state.  

*/

void best_led_show_in_the_history_of_mankind( void )
{
  static char state_cnt = 0;
  static char init_flag = NOT_INITED;

  static STATE_CONTAINER* state_array[ NUM_OF_STATES ] = {/* ... */};
  static STATE_CONTAINER first_st = { SHORT_BLINK , INNER_CNT_INIT_VALUE , 2 };
  static STATE_CONTAINER second_st = { LONG_BLINK , INNER_CNT_INIT_VALUE , 4 };

  if( NOT_INITED == init_flag )
  {
    state_array[ 0 ] = &first_st;
    state_array[ 1 ] = &second_st;
  }

  if( NUM_OF_STATES == state_cnt )
  {
    state_cnt == 0;
  }
  else
  {
    if( MY_TRUE == main_state_handler( state_array[ state_cnt ] ) )
    {
      state_cnt++;
    }
    else;  //Do nothing ...
  }
  

}

char main_state_handler( STATE_CONTAINER* actual_state_container_p )
{
  char return_value = MY_FALSE;

  if( MY_TRUE == state_func( actual_state_container_p ) )
  {
    return_value = switch_main_state( actual_state_container_p );
  }

  return return_value;
}

char switch_main_state( STATE_CONTAINER* actual_state_container_p )
{
  char return_value = MY_FALSE;
  static char tmp_cnt = 0;

  if( ( 2 * actual_state_container_p->how_many_times ) == actual_state_container_p->how_many_times_cnt )
  {
    actual_state_container_p->how_many_times_cnt = 0;
    return_value = MY_TRUE;
  }
  else
  {
    actual_state_container_p->how_many_times_cnt++;
  }

  return return_value;
}

char state_func( STATE_CONTAINER* actual_state_container_p )
{
  char return_value = MY_FALSE;
  static int inner_cnt = 0;

  if( actual_state_container_p->how_long == inner_cnt )
  {
    inner_cnt = 0;
    bvezsenyi_led_handler( actual_state_container_p );
  }
  else
  {
    inner_cnt++;
  }
  
  DelayMillis( 1 );

  return return_value;
  
}

void bvezsenyi_led_handler( STATE_CONTAINER* actual_state_container_p )
{
  if( actual_state_container_p->how_many_times_cnt % 2 )
  {
    turn_on_leds_1( );
  }
  else
  {
    turn_on_leds_2( );
  }
}

void turn_on_leds_1( void )
{
  Led_Reset();
  Led_ON( LED0 );
  Led_ON( LED2 );
  Led_ON( LED4 );   
}

void turn_on_leds_2( void )
{
  Led_Reset();
  Led_ON( LED1 );
  Led_ON( LED3 );
  Led_ON( LED5 );
}
