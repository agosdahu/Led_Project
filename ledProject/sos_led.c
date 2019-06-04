#include "sos_led.h"
#include "driver.h"
#include <Arduino.h>

#define SHORT 250u
#define LONG  500u
#define PAUSE 15000u

void MorseBlink(int time);

static FSM_t FSM_SOS        = S;

static int repetition_cnt   = 0;
static int S_cnt            = 0;
static int P_cnt            = 0;
static int iteration_cnt    = 3;
static int delay_cnt        = 0;

void sos_ledBlink(void)
{
    static int delayLimit = 0;

    switch(FSM_SOS){
      case S:
        MorseBlink(SHORT);
        iteration_cnt--;
        if(iteration_cnt == 0)
        {
          S_cnt++;
          S_cnt %= 3;   //S_cnt either 0, 1 or 2
          if(S_cnt >= 2)
          {
              FSM_SOS = P;
              S_cnt = 0;
          }
          else
          {
              FSM_SOS = O;
          }

          iteration_cnt = 3;
        }
      break;

      case O:
        MorseBlink(LONG);
        iteration_cnt--;
        if(iteration_cnt == 0)
        {
          FSM_SOS = S;
          iteration_cnt = 3;
        }
      break;

      case P:
        DelayMillis(1);
        delay_cnt++;

        if(!P_cnt)
            delayLimit = 299;
        else // P_cnt = 1
            delayLimit = 14999;

        if(delay_cnt >= delayLimit)
        {
            P_cnt++;
            P_cnt %= 2; // P_cnt either 0 or 1
            FSM_SOS = S;
            delay_cnt = 0;
        }
      break;
    }
}

void MorseBlink(int time)
{
  Led_ON(LED0);
  Led_ON(LED1);
  Led_ON(LED4);
  Led_ON(LED5);
  DelayMillis(time);
  Led_OFF(LED0);
  Led_OFF(LED1);
  Led_OFF(LED4);
  Led_OFF(LED5);
  DelayMillis(SHORT);
}
