#include <Arduino.h>
#include "IR_remote_global_var.h"


const int CommandsTable_size = 24;




Command commands[CommandsTable_size] = {
  {0x0,  0xFF00EF00, 35},
  {0x1, 0xFE01EF00, 36},
  {0x2, 0xFD02EF00, 3},
  {0x3, 0xFC03EF00, 1},
  {0x4, 0xFB04EF00, 2},
  {0x5, 0xFA05EF00, 3},
  {0x6, 0xF906EF00, 4},
  {0x7, 0xF807EF00, 5},
  {0x8, 0xF708EF00, 6},
  {0x9, 0xF609EF00, 7},
  {0xA, 0xF50AEF00, 8},
  {0xB, 0xF40BEF00, 0},
  {0xC, 0xF30CEF00, 0},
  {0xD, 0xF20DEF00, 0},
  {0xE, 0xF10EEF00, 0},
  {0xF, 0xF00FEF00, 0},
  {0x10, 0xEF10EF00, 15},
  {0x11, 0xEE11EF00, 16},
  {0x12, 0xED12EF00, 17},
  {0x13, 0xEC13EF00, 18},
  {0x14, 0xEB14EF00, 20},
  {0x15, 0xEA15EF00, 27},
  {0x16, 0xE916EF00, 28},
  {0x17, 0xE817EF00, 21},
};



//######################### PIR COMMANDS #############################

int motionDetected;

unsigned long lastTriggerSignalTime;

const unsigned long delayInterval = 6000; //30000;     // 5 min

const unsigned long delayOffInterval = 15000; //60000;  // 10 min
//######################### PhotoRes COMMANDS #############################

int LDRValue;

int lvlWhiteLight = 350;
int lvlYellowLight = 100;

bool turnOffMotion = false;
