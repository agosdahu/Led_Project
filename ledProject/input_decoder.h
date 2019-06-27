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

typedef struct  PATTERN{
    bInput_t chara;
    int charaCnt;
    int isDuplicate;
    int isInvalid;
    ulong_t lastPressed;
} pattern_t;

/*
1 - A           AGOSDAHU
2 - A -> A      DANIGEHU
3 - AB          KISSKAHU
4 - B           KURDBOHU
5 - B -> B      NAGYARHU
6 - A (2sec)    NAGYKAHU
7 - B (2sec)    VEZSEBAHU
OFF -> AB (2sec)
*/

decodeRet_t DecodeInput(void);

#endif // INPUT_DECODER_H