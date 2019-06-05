extern "C"{
   #include "driver.h"
   #include "organise.h"
}

 SW_STATUS_t sw = {{RELEASED, 0, 0}, {RELEASED, 0,0}};
  
void setup() {
  
  LedInit();
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
