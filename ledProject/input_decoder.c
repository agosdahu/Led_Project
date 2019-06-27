#include "driver.h"
#include "input_decoder.h"

#define MAX_FIFO_SIZE   12u
#define SAMPLE2SEC      8u
#define TIMEOUT         2000u
#define HOLDSAMPLES     6u      //~1,5sec

static const int samplePeriod = 250;
static const bInput_t buttonMatrix[MAX_SWSTATES][MAX_SWSTATES] =
    {   
        {AB_SHORT,  B_SHORT},
        {A_SHORT,   AB_NOP}
    };

static uint8_t TriggerSampling(void);
static decodeRet_t StateMachine(SW_STATUS_t swState);
bInput_t EasyBRead(SW_STATUS_t readVal);

/* Sets the function pointer according to StateMachine, returns enable level and func Index */
decodeRet_t DecodeInput(void) 
{
    SW_STATUS_t mySwitch = {RELEASED, RELEASED};
    decodeRet_t ret = {IDLE, UPDATE_NO};
    uint8_t sampleTick = 0;

    sampleTick = TriggerSampling();

    if(sampleTick)      //runs every 250msec if samplePeriod is 250
    {
        mySwitch = ReadSwitchStatus();
        ret = StateMachine(mySwitch);       //MAGIC
    }

    return ret;
}

/* Returns one when it's time to sample the button states */
uint8_t TriggerSampling(void)
{
    static timing_t kronos ={0, 0};
    uint8_t ret = 0;
    kronos.actTime = GetSysTimeMsec();
    
    if((kronos.actTime - kronos.lastSample) >= samplePeriod){
        kronos.lastSample = kronos.actTime;
        ret = 1;
    }
    else{
        ret = 0; //redundant branch in statement
    }
    
    return ret;
}

decodeRet_t StateMachine(SW_STATUS_t swState)
{
    static pattern_t myPattern          = {AB_NOP, 0, 0, 1, 0};
    static bInput_t prevVal             = AB_NOP;
    static decodeRet_t ret              = {IDLE, 0};

    bInput_t actVal                     = AB_NOP;

    ulong_t actSysTime;

    /*###   proper logic starts here ###*/
    actVal = EasyBRead(swState);
    actSysTime = GetSysTimeMsec();

    if(actVal != AB_NOP && prevVal == AB_NOP)
    {
        if(CheckIfTimerWentOff())
        {
            SetTimer(TIMEOUT);
            myPattern.isInvalid = 0;
        }

        if((actSysTime - myPattern.lastPressed) >=  TIMEOUT)
        {
            myPattern.lastPressed = actSysTime;
        }
        else
        {
            if(myPattern.chara == actVal)
            {
                myPattern.isDuplicate = 1;
            }
            else
            {
                myPattern.isInvalid = 1;
            }
        }
        
        myPattern.chara = actVal;
    }
    else if(actVal == prevVal)
    {
        if(actVal != AB_NOP)
        {
            myPattern.charaCnt++;
        }
    }
        
    if(CheckIfTimerWentOff())
    {   
        if(myPattern.isInvalid == 0)
        {
            switch (myPattern.chara)
            {
            case A_SHORT:
                if(myPattern.charaCnt <= HOLDSAMPLES ) 
                {
                    if(myPattern.isDuplicate)   // A_SHORT x2 ormore
                    {
                        ret.fIndex = DANIGEHU;
                    }
                    else    //A_SHORT
                    {
                        ret.fIndex = AGOSDAHU;
                    }
                }
                else    //A_LONG
                {
                    ret.fIndex = NAGYKAHU;
                }
                break;

            case B_SHORT:
                if(myPattern.charaCnt <= HOLDSAMPLES )
                {
                    if(myPattern.isDuplicate)   // B_SHORT x2 ormore
                    {
                        ret.fIndex = NAGYARHU;
                    }
                    else    //B_SHORT
                    {
                        ret.fIndex = KURDBOHU;
                    }
                }
                else    //B_LONG
                {
                    ret.fIndex = VEZSEBAHU;
                }
                break;

            case AB_SHORT:
                if(myPattern.charaCnt <= HOLDSAMPLES ) // AB_SHORT
                {
                    ret.fIndex = KISSKAHU;
                }
                else // LONGPRESS -> OFF
                {
                    ret.fIndex = IDLE;
                }
                break;
            
            default:
                ret.fIndex = IDLE;
                break;
            }
            ret.fUpdate = UPDATE_YES;
        }
        else
        {
            ret.fUpdate = UPDATE_NO;
        }
        

        myPattern.chara         = AB_NOP;
        myPattern.charaCnt      = 0;
        myPattern.isDuplicate   = 0;
        myPattern.isInvalid     = 1;
        myPattern.lastPressed   = 0;
    }
    
    prevVal = actVal;
    
    return ret;    
}

/* Interprets the switch states and returns a predefined value */
bInput_t EasyBRead(SW_STATUS_t readVal)
{
    bInput_t ret = AB_NOP;
    
    ret = buttonMatrix[readVal.sw0][readVal.sw1];

    return ret;
}