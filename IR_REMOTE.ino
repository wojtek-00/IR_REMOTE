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
  pinMode(SWITCH_PIN, INPUT_PULLUP);

}

void loop() {
  int buttonState = digitalRead(SWITCH_PIN);
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
  //Serial.println(buttonState);

  // Reading from the physical switch
  if (buttonState == LOW && !buttonPressed) {
    buttonPressed = true;
    pressStartTime = millis(); 
  }


  if (buttonState == LOW && buttonPressed && (millis() - pressStartTime >= 1000)) {   // if holding button longer than 1s -> dimm function
    //dimm function
    pressCnt = -1;
    Serial.println("dimm the LED");
  } else if (buttonState == HIGH && buttonPressed){   // pressed and released -> turn on / off
    buttonPressed = false;
    allowSwitch = true;
    pressCnt += 1;
  }

  if ((millis() - pressStartTime >= 500) && allowSwitch == true){ 
    if (pressCnt == 2) {                          // if pressed 2 times -> turn off / on reading from all sensors
      //Turn on off all the extra functions
      Serial.println("Turn all");
      pressCnt = 0;
      allowSwitch = false;
    } else if (pressCnt == 1) {                 // just turn on / off
      Serial.println("Number 60");
      Wire.beginTransmission(slave_LED);
      Wire.write(60);   // White Light
      Wire.endTransmission();
      pressCnt = 0;      
      allowSwitch = false;
    } else {
      allowSwitch = false;
      pressCnt = 0;
    }
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
