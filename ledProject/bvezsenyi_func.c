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

  static STATE_HANDLER_STRUCT state_handler = { FIRST_STAGE , 0 };

  switch( state_handler.state )
  {
    case FIRST_STAGE:
      if( MY_TRUE == state_func( SHORT_BLINK , state_handler.main_cnt ) )
      {
        main_state_handler( 2 , &state_handler, SECOND_STAGE );
      }
      //'else' branch is void
      break;
      
    case SECOND_STAGE: 
      if( MY_TRUE == state_func( LONG_BLINK , state_handler.main_cnt ) ) 
      {
        main_state_handler( 4 , &state_handler, THIRD_STAGE );
      }
      //'else' branch is void
      break;
      
    case THIRD_STAGE:
      if( MY_TRUE == state_func( SHORT_BLINK , state_handler.main_cnt ) ) 
      {
        main_state_handler( 2 , &state_handler, FIRST_STAGE );
      }
      //'else' branch is void
      break;
      
    default:    
        /* Do nothing ... */
      break;
  } 
  
}

void main_state_handler( int cnt , STATE_HANDLER_STRUCT *state_handler_p , STAGES_E next_state )
{
    if( ( 2 * cnt ) == state_handler_p->main_cnt )
    {
      state_handler_p->main_cnt = 0;
      state_handler_p->state = next_state; 
    }
    else
    {
      state_handler_p->main_cnt++;
    }
}

char state_func( int t , char main_state_cnt )
{
  char return_value = MY_FALSE;
  static int inner_cnt = 0;

  DelayMillis( 1 );

  if( t == inner_cnt )
  {
    inner_cnt = 0;
    if( main_state_cnt % 2 )
    {
      turn_on_leds_1( );
    }
    else
    {
      turn_on_leds_2( );
    }
    return_value = MY_TRUE;

  }
  else
  {
    inner_cnt++;
  } 

  return return_value;
  
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
