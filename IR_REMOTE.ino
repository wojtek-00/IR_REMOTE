#include <Wire.h>
#include "IR_remote_global_var.h"
#include "IR_Functions.h"



void setup() {
  Wire.begin();
  setup_fun(IR_RECEIVE_PIN);
  Serial.begin(9600);
  pinMode(PIR_PIN, INPUT);
  pinMode(LDR_PIN, INPUT);
  lastTriggerSignalTime = 3000;

}

void loop() {
  int remoteCommand;
  remoteCommand = loop_fun(IR_RECEIVE_PIN);
  if (remoteCommand != 0) {
    Serial.print("Command: ");
    Serial.println(remoteCommand);
    Serial.println();
    Wire.beginTransmission(slave_LED);
    Wire.write(remoteCommand);
    Wire.endTransmission();
  }
 
  //motionDetected = digitalRead(PIR_PIN);  // Read the PIR sensor
  motionDetected = 0; //  <- PIR broken now, we dont use
  //Serial.println(motionDetected);

  LDRValue = analogRead(LDR_PIN);
  

  if (millis() - lastTriggerSignalTime >= delayInterval) {
    //Serial.println("Millis ok");

    if (LDRValue < lvlYellowLight) {
      if (motionDetected == HIGH) {
        Serial.println("Number 56");
        Wire.beginTransmission(slave_LED);
        Wire.write(56);   // White Light
        Wire.endTransmission();
        turnOffMotion = true;
        lastTriggerSignalTime = millis();
      }
    } else if (LDRValue < lvlWhiteLight) {
      if (motionDetected == HIGH) {
        Serial.println("Number 55");
        Wire.beginTransmission(slave_LED);
        Wire.write(55);   // Yellow Light
        Wire.endTransmission();
        turnOffMotion = true;
        lastTriggerSignalTime = millis();
      }
    }
    if (turnOffMotion == true) {
      //Serial.println("motion true");

      if (millis() - lastTriggerSignalTime >= delayOffInterval) {
        Serial.println("Number 57");
        Wire.beginTransmission(slave_LED);
        Wire.write(57);     // Turn off
        Wire.endTransmission();
        turnOffMotion = false;
      }
    }
  }

  

}
