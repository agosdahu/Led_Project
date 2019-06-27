#include "organise.h"
#include <stddef.h> //NULL definition here

void Idle();

static void (*RunFuncArr[MAX_INDEX])(void) = {
    Idle,
    sos_ledBlink,
    LightRace,
    railBarrier,
    kurdbohu_loop,
    ChasingLights,
    binary_counter,
    Idle,       //vezsebahu
};

static void (*RunFunc)(void) = NULL;

void Idle()
{
    Led_Reset();
}

void RunProgram()
{
    (*RunFunc)();
}

void SetCallback(int index)
{
    RunFunc = (*RunFuncArr[index]);
}