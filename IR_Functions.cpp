#include <IRremote.hpp>
#include <Arduino.h>
#include "IR_remote_global_var.h"

void setup_fun(int pin){
  Serial.begin(9600);
  IrReceiver.begin(IR_RECEIVE_PIN, ENABLE_LED_FEEDBACK);
}


void loop_fun(int pin){
   if(IrReceiver.decode()){
    // Wyświetlanie raw data w formacie HEX
    Serial.print("Raw Data: ");
    Serial.println(IrReceiver.decodedIRData.decodedRawData, HEX);
    
    // Wyodrębnianie adresu i komendy (w zależności od protokołu)
    Serial.print("Address: ");
    Serial.println(IrReceiver.decodedIRData.address, HEX);  // Wyświetla adres IR w HEX
    
    Serial.print("Command: ");
    Serial.println(IrReceiver.decodedIRData.command, HEX);  // Wyświetla komendę IR w HEX
    
    // Krótkie podsumowanie wyniku IR
    Serial.print("IR Short Result: ");
    IrReceiver.printIRResultShort(&Serial);
    Serial.println();
    
    IrReceiver.resume();  // Przygotowanie do odbioru następnego sygnału
  }
}