
#include "bvezsenyi_func.h"

void best_led_show_in_the_history_of_mankind( void )
{

  switch( state )
  {
    case FIRST_STAGE:
      state_func( SHORT_BLINK );
      handle_main_cnt( 4 , SECOND_STAGE );        
      break;
      
    case SECOND_STAGE: 
      state_func( LONG_BLINK );
      handle_main_cnt( 2 , THIRD_STAGE );
      break;
      
    case THIRD_STAGE:
      state_func( SHORT_BLINK ); 
      handle_main_cnt( 4 , FIRST_STAGE );
      break;
      
    default:    
        /* Do nothing ... */
      break;
  } 
  
}

void handle_main_cnt( int cnt , STAGES_E next_state )
    
    if( cnt == main_cnt )
    {
      main_cnt = 0;
      state = next_state; 
    }
    else
    {
      main_cnt++;
    }
}

void state_func( int t )
{
 
  //TODO: use "HAL" button inspection
  if( btn_state )
  {
    //TODO: use "HAL" led handler functions
    //TODO: use "HAL" delay function
    /* Original code snippet:
    turn_on_off_led( btn_array_1 , NUM_OF_LEDS , HIGH);
    turn_on_off_led( btn_array_2 , NUM_OF_LEDS , LOW);    
    delay( t );
    */
  }  

  //TODO: use "HAL" button inspection
  if( btn_state )
  {
    
    //TODO: use "HAL" led handler functions
    //TODO: use "HAL" delay function

    /* Original code snippet: 
    turn_on_off_led( btn_array_1 , NUM_OF_LEDS , LOW);
    turn_on_off_led( btn_array_2 , NUM_OF_LEDS , HIGH);
    delay( t );
    */
  }
}
