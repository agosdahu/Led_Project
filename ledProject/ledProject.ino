extern "C"{
   #include "led_handler.h"
   #include "switch_handler.h"
   #include "sos_led.h"
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
#ifdef AGOSDAHU
    sos_ledBlink();
#elif VEZSBAHU

#elif KURDBOHU
    kurdbohu_loop();
#elif DANIGEHU

#elif NAGYKAHU

#elif NAGYANHU

#elif KISSKAHU

#endif
  }
}
