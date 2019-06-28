#ifndef ORGANISE_H
#define ORGANISE_H

#include "sos_led.h"
#include "binary_counter.h"
#include "chasingLights.h"
#include "LightRace.h"
#include "railBarrier.h"
#include "kurdbohu.h"
#include "bvezsenyi_func.h"

typedef enum FUNC_INDICE {
    IDLE,       //0
    AGOSDAHU,
    DANIGEHU,
    KISSKAHU,
    KURDBOHU,
    NAGYARHU,
    NAGYKAHU,
    VEZSEBAHU,

    MAX_INDEX   //8
} func_index_t;

void RunProgram();
void SetCallback(int index);

#endif //ORGANISE_H