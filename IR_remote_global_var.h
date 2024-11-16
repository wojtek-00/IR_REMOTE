#ifndef IR_REMOTE_GLOBAL_VAR_H
#define IR_REMOTE_GLOBAL_VAR_H
#include <IRremote.hpp>

#define RemoteAdress    0xEF00

//######################### IR COMMANDS #############################
extern const int CommandsTable_size;

struct Command {
  uint8_t IRcommand;
  uint32_t RawData;
  int ProgramCommand;
};

extern Command commands[];

#endif