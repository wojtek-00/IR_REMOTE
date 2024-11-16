#include <IRremote.hpp>
#include <Arduino.h>
#include "IR_remote_global_var.h"

void setup_fun(int pin){
  Serial.begin(9600);
  IrReceiver.begin(IR_RECEIVE_PIN, ENABLE_LED_FEEDBACK);
}


void loop_fun(int pin){
   if(IrReceiver.decode()){
    Serial.println(IrReceiver.decodedIRData.decodedRawData, HEX);
    IrReceiver.printIRResultShort(&Serial);
    Serial.println();
    IrReceiver.resume();
  }
}