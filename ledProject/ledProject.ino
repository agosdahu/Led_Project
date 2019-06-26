extern "C"{
   #include "driver.h"
   #include "organise.h"
   #include "input_decoder.h"
}

static decodeRet_t userSelection = {IDLE, UPDATE_NO};

void setup() {
  
  Led_Init();
  SwitchInit();
  SetCallback(AGOSDAHU); //Idle
}

void loop() {
  
    userSelection = DecodeInput();

    if(userSelection.fUpdate == UPDATE_YES){
        SetCallback(userSelection.fIndex);
        userSelection.fUpdate = UPDATE_NO;
    }

    RunProgram();
}