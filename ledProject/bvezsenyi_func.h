#ifndef _BVEZSENYI_FUNC_H_
#define _BVEZSENYI_FUNC_H_

#define SHORT_BLINK  250
#define LONG_BLINK  500

#define NUM_OF_LEDS 3

typedef enum stages_e
{
    FIRST_STAGE = 0,
    SECOND_STAGE,
    THIRD_STAGE
}STAGES_E;

int main_cnt = 0;
int btn_state = 1;
int start_button = 2;
int stop_button = 3;


int btn_array_1[ NUM_OF_LEDS ] = { LED0 , LED2, LED4 };
int btn_array_2[ NUM_OF_LEDS ] = { LED1 , LED3, LED5 };

void best_led_show_in_the_history_of_mankind( void );
void handle_main_cnt( int cnt , int next_state );
void state_func( int t );

#endif /* _BVEZSENYI_FUNC_H_ */