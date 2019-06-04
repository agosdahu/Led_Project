#include "organise.h"

static * (void) RunFunc(void);

void RunProgram()
{
    RunFunc();
}

void SetCallback( * (void)Func(void))
{
    RunFunc = Func;
}