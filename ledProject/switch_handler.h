#ifndef SWITCH_HANDLER_H
#define SWITCH_HANDLER_H

#include <stdint.h>

#define SWITCH0     8u
#define SWITCH1     9u

typedef enum SW_STATE{
    PRESSED = 0,
    RELEASED = 1
} SW_STATE_t;

typedef struct SW_INFO{
    SW_STATE_t state;
    uint32_t lastPressed;           // timestamp of last pressing
    uint32_t lastReleased;          // timestamp of last releasing
    uint32_t pressedDuration;       // measure PRESSED state duration in ms
    uint32_t releasedDuration;      // measure RELEASED state duration in ms
} SW_INFO_t;

typedef struct SW_STATUS{
    SW_INFO_t sw0;
    SW_INFO_t sw1;
} SW_STATUS_t;

void SwitchInit(void);
SW_STATUS_t ReadSwitchStatus(void);

#endif //SWITCH_HANDLER_H
