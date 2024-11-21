#include "IR_remote_global_var.h"
#include "IR_Functions.h"

void setup() {
  setup_fun(IR_RECEIVE_PIN);

}

void loop() {
  int remodeCommand;
  remodeCommand = loop_fun(IR_RECEIVE_PIN);
  if (remodeCommand != 0) {
    Serial.print("Here: ");
    Serial.println(remodeCommand);
    Serial.println();
  }
}