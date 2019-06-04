extern "C"{
   #include "led_handler.h"
   #include "switch_handler.h"
   #include "sos_led.h"
   #include "binary_counter.h"
   #include "chasingLights.h"
   #include "LightRace.h"
   #include "railBarrier.h"
   #include "kurdbohu.h"
}

 SW_STATUS_t sw = {RELEASED, RELEASED};
  
void setup() {
  
  LedInit();
  SwitchInit();
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

    runProgram();

  //sos_ledBlink();
//
  //kurdbohu_loop();
//
  //LightRace( 20000 );
//
  //binary_counter();
//
  //ChasingLights();
//
  //railBarrier();

  }
}
