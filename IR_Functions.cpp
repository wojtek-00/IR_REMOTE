#include <IRremote.hpp>
#include <Arduino.h>
#include "IR_remote_global_var.h"

void setup_fun(int pin){
  Serial.begin(9600);
  IrReceiver.begin(IR_RECEIVE_PIN, ENABLE_LED_FEEDBACK);
}


int loop_fun(int pin){
   if(IrReceiver.decode()){
   
    IrReceiver.resume();  // Przygotowanie do odbioru następnego sygnału

    if (IrReceiver.decodedIRData.address == RemoteAdress) {
      for (int i = 0; i < CommandsTable_size; i++){
        if (commands[i].IRcommand == IrReceiver.decodedIRData.command){
          if ((commands[i].ProgramCommand == 35) || (commands[i].ProgramCommand == 36)) {
            return (commands[i].ProgramCommand);
          } else if (IrReceiver.decodedIRData.decodedRawData != 0) {
            return (commands[i].ProgramCommand);
          }
        }
      }
    }
    
  } else {
    return 0;
  }

  
  

}