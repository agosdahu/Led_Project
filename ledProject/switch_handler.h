#ifndef SWITCH_HANDLER_H
#define SWITCH_HANDLER_H


#define SWITCH0     8u
#define SWITCH1     9u

typedef enum SW_STATE{
    PRESSED = 0,
    RELEASED = 1
} SW_STATE_t;

typedef struct SW_STATUS{
    SW_STATE_t sw0;
    SW_STATE_t sw1;
} SW_STATUS_t;

void SwitchInit(void);
SW_STATUS_t ReadSwitchStatus(void);

#endif //SWITCH_HANDLER_H