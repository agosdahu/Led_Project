extern "C"{
   #include "driver.h"
   #include "organise.h"
}

 SW_STATUS_t sw = {RELEASED, RELEASED};
  
void setup() {
  
  LedInit();
  SwitchInit();
  SetCallback(0); //Idle
}

void loop() {
  
  static int EN = 0;
  
  
  sw = ReadSwitchStatus();

  if(sw.sw0 == PRESSED)
  {
    EN = 1;
  }

  if(sw.sw1 == PRESSED)
  {
    EN = 0;
  }

  if(EN)
  {
    RunProgram();
  }
}
