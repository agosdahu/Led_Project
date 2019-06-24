#include "driver.h"
#include "input_decoder.h"

#define myEOF_LIMIT   3u
#define HOLD_LIMIT  8u

static const int samplePeriod = 250;

static const bInput_t buttonMatrix[MAX_SWSTATES][MAX_SWSTATES] =
    {   
        {AB_SHORT,  B_SHORT},
        {A_SHORT,   AB_NOP}
    };

static uint8_t TriggerSampling(void);
static decodeRet_t StateMachine(SW_STATUS_t swState);
fsm_sw_t TellMyNextState(fsm_sw_t prevState, bInput_t action);
decodeRet_t TakeTheNextStep(fsm_sw_t doIt);
bInput_t easyBRead(SW_STATUS_t readVal);

/* Sets the function pointer according to StateMachine, returns enable level and func Index */
decodeRet_t DecodeInput(void) 
{
    SW_STATUS_t mySwitch = {RELEASED, RELEASED};
    decodeRet_t ret = {IDLE, UPDATE_NO};
    uint8_t sampleTick = 0;

    sampleTick = TriggerSampling();

    if(sampleTick)
    {
        mySwitch = ReadSwitchStatus();
        ret = StateMachine(mySwitch);
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
    static fsm_sw_t decodeState     = BUTTON_IDLE;
    decodeRet_t ret                 = {IDLE, 0};
    bInput_t actInput               = AB_NOP;

    actInput = easyBRead(swState);

    /* TEST */
    if(actInput == A_SHORT)
        Led_ON(LED2);
    if(actInput == B_SHORT)
        Led_OFF(LED2);

    if(actInput == AB_SHORT)
        Led_ON(LED3);
    if(actInput == AB_NOP)
        Led_OFF(LED3);
    /*       */

    decodeState = TellMyNextState(decodeState, actInput);
    ret = TakeTheNextStep(decodeState);
    if(decodeState == ERR){
        decodeState == BUTTON_IDLE;
    }
    
    return ret;    
}

/* next state based on previous state and button push */
fsm_sw_t TellMyNextState(fsm_sw_t prevState, bInput_t action)
{
    fsm_sw_t ret = ERR;
    static int myEOFTimer  = 0;
    static int holdTimer = 0;   // samplePeriod = 250 -> 2sec needs 8 of these

    switch(action)
    {
        case A_SHORT:
            if(prevState == BUTTON_IDLE){
                ret = A;
            }
            if(prevState == APAUSE){
                ret = AA;
            }
        break;

        case A_LONG:
            if(prevState == A || prevState == A_2){
                ret = A_2;
                holdTimer++;

                if(holdTimer >= HOLD_LIMIT){
                    ret = UPDATE;
                    holdTimer = 0;
                }
            }
        break;
        
        case AB_SHORT:
            if(prevState == BUTTON_IDLE){
                ret = AB;
            }
        break;

        case B_SHORT:
            if(prevState == BUTTON_IDLE){
                ret = B;
            }
            if(prevState == BPAUSE){
                ret = BB;
            }
        break;
        
        case B_LONG:
            if(prevState == B || prevState == B_2){
                ret = B_2;
                holdTimer++;

                if(holdTimer >= HOLD_LIMIT){
                    ret = UPDATE;
                    holdTimer = 0;
                }
            }
        break;
        
        case AB_NOP:
            if(prevState == A){
                ret = APAUSE;
            }
            if(prevState == B){
                ret = BPAUSE;
            }

            if( prevState == AA     || 
                prevState == BB     ||
                prevState == AB     ||
                prevState == APAUSE ||
                prevState == BPAUSE ||
                prevState == myEOF        )
            {
                ret = myEOF;
                myEOFTimer++;

                if(myEOFTimer >= myEOF_LIMIT){
                    ret = UPDATE;
                    myEOFTimer = 0;
                }
            }

            if(prevState == BUTTON_IDLE){
                ret = BUTTON_IDLE;
            }

        break;

        if(prevState == ERR || prevState == UPDATE){
            ret = BUTTON_IDLE;
        }

        default:
            ret = ERR;
        break;
    }

    return ret;
}

/* act on the current state */
decodeRet_t TakeTheNextStep(fsm_sw_t doIt)
{
    static decodeRet_t ret = {IDLE, 0}; 

    switch(doIt){
        case A:
            ret.fIndex = AGOSDAHU;
        break;

        case AA:
            ret.fIndex = DANIGEHU;
        break;

        case AB:
            ret.fIndex = KISSKAHU;
        break;

        case B:
            ret.fIndex = KURDBOHU;
        break;

        case BB:
            ret.fIndex = NAGYARHU;
        break;

        case A_2:
            ret.fIndex = NAGYKAHU;
        break;

        case B_2:
            ret.fIndex = VEZSEBAHU;
        break;

        case APAUSE:
        break;

        case BPAUSE:
        break;

        case ERR:
            ret.fIndex = IDLE;
            ret.fUpdate = 1;
        break;

        case myEOF:
        break;

        case UPDATE:
            ret.fUpdate = 1;
        break;

        case BUTTON_IDLE:
            ret.fUpdate = 0;

        break;

        default:
            ret.fIndex = IDLE;
            ret.fUpdate = 1;
        break;
    }   
}

/* Interprets the switch states and returns a predefined value */
bInput_t easyBRead(SW_STATUS_t readVal)
{
    bInput_t ret = AB_NOP;
    
    ret = buttonMatrix[readVal.sw0][readVal.sw1];

    return ret;
}