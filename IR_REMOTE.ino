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

  // #################################### IR REMOTE ###########################################
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

  // ###################################### SWITCH ###########################################
  int buttonState = digitalRead(SWITCH_PIN);

  // Reading from the physical switch
  if (buttonState == LOW && !buttonPressed) {
    buttonPressed = true;
    pressStartTime = millis(); 
  }


  // if holding button longer than 1s -> dimm function
  if (buttonState == LOW && buttonPressed && (millis() - pressStartTime >= 1000)) {   
    Serial.println("Number 61");
    Wire.beginTransmission(slave_LED);
    Wire.write(61);   
    Wire.endTransmission();
    pressCnt = -1;
    //Serial.println("dimm the LED");
  } else if (buttonState == HIGH && buttonPressed){   // pressed and released -> turn on / off
    buttonPressed = false;
    allowSwitch = true;
    pressCnt += 1;
  }

  // if pressed 2 times -> turn off / on reading from all sensors
  if ((millis() - pressStartTime >= 500) && allowSwitch == true){ 
    if (pressCnt == 2) {                         
      if (readingSensor == false) {
        readingSensor = true;
        Serial.println("Reading sensors On.");
        //Serial.println("Number 60");
        Wire.beginTransmission(slave_LED);
        Wire.write(70);   
        Wire.endTransmission();
      } else if (readingSensor == true) {
        readingSensor = false;
        Serial.println("Reading sensors Off.");
        //Serial.println("Number 60");
        Wire.beginTransmission(slave_LED);
        Wire.write(71);   
        Wire.endTransmission();   
      }
      pressCnt = 0;
      allowSwitch = false;
    } else if (pressCnt == 1) {                 // just turn on / off
      Serial.println("Number 60");
      Wire.beginTransmission(slave_LED);
      Wire.write(60);   
      Wire.endTransmission();
      pressCnt = 0;      
      allowSwitch = false;
    } else {
      allowSwitch = false;
      pressCnt = 0;
    }
  }


// #################################### SENSORS: PIR & LDR ###########################################
  if (readingSensor == true) {

    //motionDetected = digitalRead(PIR_PIN);  // Read the PIR sensor
    motionDetected = 0; //  <- PIR broken now, we dont use
    //Serial.println(motionDetected);

    LDRValue = analogRead(LDR_PIN);
    

    if (millis() - lastTriggerSignalTime >= delayInterval) {

      if (LDRValue < lvlYellowLight) {
        if (motionDetected == HIGH) {
          Serial.println("Number 56");
          Wire.beginTransmission(slave_LED);
          Wire.write(56);                       // White Light
          Wire.endTransmission();
          turnOffMotion = true;
          lastTriggerSignalTime = millis();
        }
      } else if (LDRValue < lvlWhiteLight) {
        if (motionDetected == HIGH) {
          Serial.println("Number 55");
          Wire.beginTransmission(slave_LED);
          Wire.write(55);                     // Yellow Light
          Wire.endTransmission();
          turnOffMotion = true;
          lastTriggerSignalTime = millis();
        }
      }
      if (turnOffMotion == true) {
        if (millis() - lastTriggerSignalTime >= delayOffInterval) {
          Serial.println("Number 57");
          Wire.beginTransmission(slave_LED);
          Wire.write(57);                     // Turn off
          Wire.endTransmission();
          turnOffMotion = false;
        }
      }
    }
  }
}
