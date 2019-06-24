#ifndef INPUT_DECODER_H
#define INPUT_DECODER_H

#include "organise.h"

#define UPDATE_YES      1u
#define UPDATE_NO       0u

typedef unsigned long ulong_t;

typedef struct MY_TIMING {
    ulong_t actTime;
    ulong_t lastSample;

} timing_t;

typedef struct DECRET {
    func_index_t fIndex;
    int fUpdate;
} decodeRet_t;

typedef enum INPUT_OPTS {
    A_SHORT,        //0
    AB_SHORT,       //1
    B_SHORT,        //2
    AB_NOP,         //3
    MAX_BINPUTS     //4
} bInput_t;

/*
1 - A
2 - A -> A
3 - AB
4 - B
5 - B -> B
6 - A (2sec)
7 - B (2sec)
OFF -> AB (2sec)
*/

typedef enum FSM_SW {
    A,
    AA,
    AB,
    B,
    BB,
    A_2,
    B_2,
    APAUSE,
    BPAUSE,
    ERR,
    myEOF,
    UPDATE,
    BUTTON_IDLE,
    ST_MAX
} fsm_sw_t;

decodeRet_t DecodeInput(void);

#endif // INPUT_DECODER_H