#ifndef SOS_LED_H
#define SOS_LED_H

typedef enum FSM{
    S,
    O,
    P
  } FSM_t;

typedef enum BLINKMATRIX{
  BLINK_ON,
  BLINK_OFF,
  BLINK_WAIT,
  BLINK_FINISHED
} BLINK_t;

void sos_ledBlink( void );

#endif