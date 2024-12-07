#ifndef IR_REMOTE_GLOBAL_VAR_H
#define IR_REMOTE_GLOBAL_VAR_H


#define RemoteAdress    0xEF00    //Adress of the Remote
#define IR_RECEIVE_PIN  7         // Pin where the IR is Connected
#define none            100       // value of none
#define slave_LED       8         // slave adress

//######################### IR COMMANDS #############################
extern const int CommandsTable_size;


struct Command {
  uint8_t IRcommand;
  uint32_t RawData;
  int ProgramCommand;
};

extern Command commands[];

//########################### SWITCH #################################
#define SWITCH_PIN 8

extern unsigned long pressStartTime;
extern unsigned long  pressDuration;
extern bool buttonPressed;
extern bool switchFlag;

//######################### PIR COMMANDS #############################
#define PIR_PIN 2

extern unsigned long lastTriggerSignalTime;

extern const unsigned long delayInterval;

extern const unsigned long delayOffInterval;

extern int motionDetected;

//######################### PhotoRes COMMANDS #############################
#define LDR_PIN A3

extern int LDRValue;

extern int lvlYellowLight;
extern int lvlWhiteLight;

extern bool turnOffMotion;


#endif