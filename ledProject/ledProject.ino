extern "C"{
   #include "led_handler.h"
   #include "switch_handler.h"
   #include "sos_led.h"
   #include "chasingLights.h"
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
#ifdef VEZSBAHU

#ifdef KURDBOHU

#ifdef DANIGEHU

#ifdef NAGYKAHU

#ifdef NAGYANHU

#ifdef KISSKAHU

#endif
  }
}
