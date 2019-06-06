extern "C"{
   #include "driver.h"
   #include "organise.h"
}

 SW_STATUS_t sw = {{RELEASED, 0, 0, 0, 0}, {RELEASED, 0, 0, 0, 0}};
  
void setup() {
  
  Led_Init();
  SwitchInit();
  SetCallback(0); //Idle
}

void loop() {
  
  static int EN = 0;
  
  
  sw = ReadSwitchStatus();

  if(sw.sw0.state == PRESSED)
  {
    EN = 1;
  }

  if(sw.sw1.state == PRESSED)
  {
    EN = 0;
  }

  if(EN)
  {
    RunProgram();
  }
}

// --------------------------------------------------------------- //

bool detect_1(void)    // button 1 & 2 are pressed at the same time
{
    return (sw.sw0.state == PRESSED && sw.sw1.state == PRESSED);
}

bool detect_2(void)   // button 1 is pressed for 2 seconds
{
    return (sw.sw0.pressedDuration > 2000);
}

bool detect_3(void)   // button 2 is pressed for 2 seconds
{
    return (sw.sw1.pressedDuration > 2000);
}

bool detect_4(void)   // button 1 is pressed 2x within 500 ms (pressing a button needs to last for at least 200 ms)
{
    enum MY_STATES
    {
        ST_NONE,
        ST_INIT,
        ST_FIRST_PRESSED, 
        ST_FIRST_RELEASED, 
        ST_SECOND_PRESSED,
        ST_MAX
    };

    static MY_STATES myState = ST_NONE;
    int    targetAchieved    = false;

    switch(myState)
    {
        case ST_NONE:
            myState = ST_INIT;
            // no break;
        case ST_INIT:
            if (sw.sw0.state == PRESSED)
                myState = ST_FIRST_PRESSED;
            break;
        case ST_FIRST_PRESSED:
            if (sw.sw0.state == RELEASED)
                myState = (sw.sw0.pressedDuration > 200 ? ST_FIRST_RELEASED : ST_NONE);
            break;
        case ST_FIRST_RELEASED:
            if (sw.sw0.state == PRESSED)
                myState = (sw.sw0.releasedDuration < 500 ? ST_SECOND_PRESSED : ST_NONE);
            break;
        case ST_SECOND_PRESSED:
            if (sw.sw0.state == RELEASED)
                myState = ST_NONE;
            if (sw.sw0.pressedDuration > 200)
                targetAchieved = true;
            break;
        default:
            myState = ST_NONE;
            break;
    }

    return (targetAchieved);
}

