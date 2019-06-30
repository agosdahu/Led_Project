#include "bvezsenyi_func.h"

void best_led_show_in_the_history_of_mankind( void )
{
  static char state_cnt = 0;
  static char init_flag = NOT_INITED;

  static STATE_CONTAINER* state_array[ NUM_OF_STATES ] = {/* ... */};
  static STATE_CONTAINER first_st = { 2 , 250 };
  static STATE_CONTAINER second_st = { 4 , 500 };

  if( NOT_INITED == init_flag )
  {
    state_array[ 0 ] = &first_st;
    state_array[ 1 ] = &second_st;
    init_flag = INITED;
  }

  if( NUM_OF_STATES == state_cnt )
  {
    state_cnt = 0;
  }

  if( MY_TRUE == main_state_handler( state_array[ state_cnt ] ) )
  {
    state_cnt++;
  }
  else;  //Do nothing ...
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

  if( ( 2 * actual_state_container_p->how_many_times ) == tmp_cnt )
  {
    tmp_cnt = 0;
    return_value = MY_TRUE;
  }
  else
  {
    tmp_cnt++;
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
    bvezsenyi_led_handler();
    return_value = MY_TRUE;
  }
  else
  {
    inner_cnt++;
  }
  
  DelayMillis( 1 );

  return return_value;
  
}

void bvezsenyi_led_handler( void )
{
  static char inner_led_state = 1;
  
  if( inner_led_state )
  {
    turn_on_leds_1( );
  }
  else
  {
    turn_on_leds_2( );
  }

  inner_led_state ^= 1;
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
