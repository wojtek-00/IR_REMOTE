#include <Wire.h>
#include "IR_remote_global_var.h"
#include "IR_Functions.h"



void setup() {
  Wire.begin();
  setup_fun(IR_RECEIVE_PIN);
  Serial.begin(9600);
  pinMode(PIR_PIN, INPUT);
  pinMode(LDR_PIN, INPUT);
  lastTriggerSignalTime = 300000;

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
 
  motionDetected = digitalRead(PIR_PIN);  // Odczyt stanu czujnika PIR

  LDRValue = analogRead(LDR_PIN);

  if (millis() - lastTriggerSignalTime >= delayInterval) {
    //Serial.println("Millis ok");

    if (LDRValue < lvlWhiteLight) {
      if (motionDetected == HIGH) {
        Serial.println("Number 55");
        Wire.beginTransmission(slave_LED);
        Wire.write(55);   // White Light
        Wire.endTransmission();
        lastTriggerSignalTime = millis();
      }
    } else if (LDRValue < lvlYellowLight) {
      if (motionDetected == HIGH) {
        Serial.println("Number 56");
        Wire.beginTransmission(slave_LED);
        Wire.write(56);   // Yellow Light
        Wire.endTransmission();
        lastTriggerSignalTime = millis();
      }
    }
  }

  if (millis() - lastTriggerSignalTime >= delayOffInterval) {
    Serial.println("Number 55");
    Wire.beginTransmission(slave_LED);
    Wire.write(57);     // Turn off
    Wire.endTransmission();

  }

}
