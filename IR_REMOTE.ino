#include "IR_remote_global_var.h"
#include "IR_Functions.h"

void setup() {
  setup_fun(IR_RECEIVE_PIN);

}

void loop() {
  loop_fun(IR_RECEIVE_PIN);
}