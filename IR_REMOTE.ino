#include <Wire.h>
#include "IR_remote_global_var.h"
#include "IR_Functions.h"



void setup() {
  Wire.begin();
  setup_fun(IR_RECEIVE_PIN);
  Serial.begin(9600);

}

void loop() {
  int remoteCommand;
  remoteCommand = loop_fun(IR_RECEIVE_PIN);
  if (remoteCommand != 0) {
    Serial.print("Here: ");
    Serial.println(remoteCommand);
    Serial.println();
    Wire.beginTransmission(slave_LED);
    Wire.write(remoteCommand);
    Wire.endTransmission();
  }
 

  //delay(10);

}
